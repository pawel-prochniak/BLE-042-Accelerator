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

void debug(char msg[])
{
    UART_UartPutString(msg);
    UART_UartPutString("\r\n");
}

void debugInt(int integer)
{
    char string[16];
    sprintf(string, "%d", integer);
    debug(string);
}

void debugFloat(float f) 
{
    char string[16];
    sprintf(string, "%f", f);
    debug(string);
}

void debugHex(int hex)
{
    char string[16];
    sprintf(string, "%x", hex);
    debug(string);
}


/* [] END OF FILE */
