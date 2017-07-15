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
#include <stdio.h>
#include <common.h>
#include <ADXL345.h>
#include <BLEControl.h>

extern int bleConnected;
extern int notifyOn;

void convertSensorDataToArrays();


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    BlueLED_Write(LED_OFF);
    AdvLED_Write(LED_OFF);
    ConnectedLED_Write(LED_OFF);
    CyBle_Start(Stack_Handler);
    
    // Start components
    UART_Start();
    I2C_Start();
    
    printf("\r\n--- START ---\r\n");
    
    startAccConnection();

    for(;;)
    {
        /* Process all the generated events. */
        CyBle_ProcessEvents();
        
        getSensorData();
        
        if (bleConnected && notifyOn) 
        {   
            sendNotifications();                
        }
    }
}



/* [] END OF FILE */
