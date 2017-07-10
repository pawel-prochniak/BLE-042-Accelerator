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

void Stack_Handler ( uint32 eventCode, void *eventParams )
{
    switch( eventCode )
    {
        case CYBLE_EVT_STACK_ON:
        case CYBLE_EVT_GAP_DEVICE_DISCONNECTED:
            CyBle_GappStartAdvertisement(CYBLE_ADVERTISING_FAST);
            break;
        
    }
}

void Ias_Handler( uint32 eventCode, void *eventParam )
{
    CYBLE_IAS_CHAR_VALUE_T *param = (CYBLE_IAS_CHAR_VALUE_T *) eventParam;
    
    if ( *param->value->val == 0 )
        PWM_WriteCompare( 0 );
    else if ( *param->value->val == 1)
        PWM_WriteCompare( 500 );
    else PWM_WriteCompare( 1000 );
}

CY_ISR( Timer_ISR_Handler ) 
{
    CYBLE_GATT_HANDLE_VALUE_PAIR_T locHandleValuePair;
    uint8 bval;
    
    locHandleValuePair.attrHandle = cyBle_bass[0].batteryLevelHandle;
    locHandleValuePair.value.len = 1;
    locHandleValuePair.value.val = &bval;
    
    if ( CYBLE_GATT_ERR_NONE == CyBle_GattsReadAttributeValue( &locHandleValuePair, NULL, CYBLE_GATT_DB_LOCALLY_INITIATED ) )
    {
        if ( --bval == 0 )
            bval = 100;
        
        CyBle_GattsWriteAttributeValue( &locHandleValuePair, 0, NULL, CYBLE_GATT_DB_LOCALLY_INITIATED );
    }
    Timer_ClearInterrupt( Timer_INTR_MASK_TC );
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    CyBle_Start( Stack_Handler );
    CyBle_IasRegisterAttrCallback( Ias_Handler );
    
    PWM_Start();
    Timer_Start();
    Timer_ISR_StartEx( Timer_ISR_Handler );

    for(;;)
    {
        CyBle_ProcessEvents();
    }
}

/* [] END OF FILE */
