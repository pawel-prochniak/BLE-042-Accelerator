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
#include <common.h>

extern union CharValue xData;
extern union CharValue yData;
extern union CharValue zData;

uint8 BLEStackStatus = FALSE;

void convertSensorDataToArrays();

void Stack_Handler( uint32 eventCode, void *eventParam )
{
    CYBLE_GATTS_WRITE_REQ_PARAM_T *wrReq;
    
    switch ( eventCode )
    {
        //** GAP **
        case CYBLE_EVT_STACK_ON:
            CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST );
            AdvLED_Write(LED_ON);
            break;
        case CYBLE_EVT_STACK_BUSY_STATUS: //This event is generated when the internal stack buffer is full and no more data can be accepted or the stack has buffer available and can accept data
            BLEStackStatus = *(uint8*)eventParam; //Extract the BLE stack status
            break;
        case CYBLE_EVT_GAPP_ADVERTISEMENT_START_STOP:
            if(CYBLE_STATE_DISCONNECTED == CyBle_GetState())
                AdvLED_Write(LED_ON);
            break;
        
        case CYBLE_EVT_GAP_DEVICE_CONNECTED:
            printf("\r\nConnected to device");
            bleConnected = 1;
            AdvLED_Write(LED_OFF);
            ConnectedLED_Write(LED_ON);
            break;
            
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            printf("\r\nDisconnected from device");
            bleConnected = 0;
            ConnectedLED_Write(LED_OFF);
            AdvLED_Write(LED_ON);
            CyBle_GappStartAdvertisement( CYBLE_ADVERTISING_FAST );
            break;
       
            
        //** GATT **
        case CYBLE_EVT_GATT_CONNECT_IND:
            break;
            
        case CYBLE_EVT_GATTS_WRITE_REQ:
            wrReq = (CYBLE_GATTS_WRITE_REQ_PARAM_T *) eventParam;
            if ( wrReq->handleValPair.attrHandle == CYBLE_SENSOR_X_SENSORCCCD_DESC_HANDLE )
            {
                printf("\r\nWriting to CYBLE_SENSOR_X_SENSORCCCD_DESC_HANDLE");
                CyBle_GattsWriteAttributeValue( &wrReq->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                notifyOn = wrReq->handleValPair.value.val[0];
            }
            if ( wrReq->handleValPair.attrHandle == CYBLE_SENSOR_Y_SENSORCCCD_DESC_HANDLE )
            {
                printf("\r\nWriting to CYBLE_SENSOR_Y_SENSORCCCD_DESC_HANDLE");
                CyBle_GattsWriteAttributeValue( &wrReq->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                notifyOn = wrReq->handleValPair.value.val[0];
            }
            if ( wrReq->handleValPair.attrHandle == CYBLE_SENSOR_Z_SENSORCCCD_DESC_HANDLE )
            {
                printf("\r\nWriting to CYBLE_SENSOR_Z_SENSORCCCD_DESC_HANDLE");
                CyBle_GattsWriteAttributeValue( &wrReq->handleValPair, 0, &cyBle_connHandle, CYBLE_GATT_DB_LOCALLY_INITIATED);
                notifyOn = wrReq->handleValPair.value.val[0];
            }
            CyBle_GattsWriteRsp( cyBle_connHandle );
            break;
           
        default:
            break;
           
            
    }
}

int counter = 0;

void sendNotifications()
{    
    // X data handle
    CYBLE_GATTS_HANDLE_VALUE_NTF_T xDataHandle;
    xDataHandle.attrHandle = CYBLE_SENSOR_X_CHAR_HANDLE;
    xDataHandle.value.len = sizeof(xData);
    xDataHandle.value.val = (uint8 *)&xData.uintVal;               
    CyBle_GattsWriteAttributeValue( &xDataHandle, 0u, &cyBle_connHandle, 0 );
    while (BLEStackStatus != CYBLE_STACK_STATE_FREE) {CyBle_ProcessEvents();}
    int notifResult = CyBle_GattsNotification( cyBle_connHandle, &xDataHandle );
    if (notifResult != 0) {
        printf("\r\nError sending X notif, error code: %d", notifResult);
    }
    if (counter < 10) 
    {
        printf("\r\nSending value %d: %f", counter, xData.floatVal);
        counter++;     
    }
    
    // Y data handle
    CYBLE_GATTS_HANDLE_VALUE_NTF_T yDataHandle;
    yDataHandle.attrHandle = CYBLE_SENSOR_Y_CHAR_HANDLE;
    yDataHandle.value.len = sizeof(yData);
    yDataHandle.value.val = (uint8 *)&yData.uintVal;               
    CyBle_GattsWriteAttributeValue( &yDataHandle, 0u, &cyBle_connHandle, 0 ); 
    while (BLEStackStatus != CYBLE_STACK_STATE_FREE) {CyBle_ProcessEvents();}
    notifResult = CyBle_GattsNotification( cyBle_connHandle, &yDataHandle );
    if (notifResult != 0) {
        printf("\r\nError sending Y notif, error code: %d", notifResult);
    }
    
    // Z data handle
    CYBLE_GATTS_HANDLE_VALUE_NTF_T zDataHandle;
    zDataHandle.attrHandle = CYBLE_SENSOR_Z_CHAR_HANDLE;;
    zDataHandle.value.len = sizeof(zData);
    zDataHandle.value.val = (uint8 *)&zData.uintVal;              
    CyBle_GattsWriteAttributeValue( &zDataHandle, 0u, &cyBle_connHandle, 0 );
    while (BLEStackStatus != CYBLE_STACK_STATE_FREE) {CyBle_ProcessEvents();}
    notifResult = CyBle_GattsNotification( cyBle_connHandle, &zDataHandle );
    if (notifResult != 0) {
        printf("\r\nError sending Z notif, error code: %d", notifResult);
    }
}


/* [] END OF FILE */
