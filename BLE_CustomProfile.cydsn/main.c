/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

int capsenseNotify;
int bleConnected = 0;

CYBLE_CONN_HANDLE_T connectionHandle;

void Stack_Handler( uint32 eventCode, void *eventParam )
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReq;
    
    switch ( eventCode )
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST );
            UART_UartPutString("Adv started");
            bleConnected = 1;
            break;
            
        case CYBLE_EVT_GATT_CONNECT_IND:
            //connectionHandle = *(CYBLE_CONN_HANDLE_T *) eventParam;
            UART_UartPutString("Device connected");
            break;
            
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            bleConnected = 0;
            UART_UartPutString("Device disconnected");
            break;
            
        case CYBLE_EVT_GATTS_WRITE_REQ:
            UART_UartPutString("Write request");
            wrReq = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            if ( wrReq->handleValPair.attrHandle == CYBLE_CAPSENSE_SLIDER_SLIDERCCCD_DESC_HANDLE )
            {
                UART_UartPutString("Requested slider desc value");
                CyBle_GattsWriteAttributeValue( &wrReq->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                capsenseNotify = wrReq->handleValPair.value.val[0];
            }
            CyBle_GattsWriteRsp( cyBle_connHandle );
            break;
           
            default:
            break;
            
    }
}

int main()
{
    CyGlobalIntEnable; 
    
    CapSense_Start();
    CapSense_InitializeAllBaselines();
    CapSense_ScanEnabledWidgets();
    
    UART_Start();
    
    CyBle_Start( Stack_Handler );
    
    for(;;)
    {
        CyBle_ProcessEvents();
        
        if (!CapSense_IsBusy() && bleConnected)
        {
            uint8 pos = (uint8) CapSense_GetCentroidPos( CapSense_LINEARSLIDER0__LS );
            
            CapSense_UpdateEnabledBaselines();
            CapSense_ScanEnabledWidgets();
            
            if (pos!=0xFF)
            {
                CYBLE_GATTS_HANDLE_VALUE_NTF_T capsenseHandle;
                capsenseHandle.attrHandle = CYBLE_CAPSENSE_SLIDER_CHAR_HANDLE;
                capsenseHandle.value.len = 1;
                capsenseHandle.value.val = &pos;
                
                UART_UartPutChar(&pos);
                
                CyBle_GattsWriteAttributeValue( &capsenseHandle, 0, &cyBle_connHandle, 0);
                
                if (capsenseNotify)
                    CyBle_GattsNotification( cyBle_connHandle, &capsenseHandle );
            }
            
        }
    }
}

/* [] END OF FILE */
