/* ========================================
 * File containting constants.
 *
 * Copyright Pawel Prochniak, 2017
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>

#ifndef COMMON_H
#define COMMON_H

/***************************************
*           API Constants
***************************************/
#define LED_ON                      (0u)
#define LED_OFF                     (1u)
#define TRUE                        (0x01)
#define FALSE                       (0x00);

#define DBG_PRINTF(...)          (printf(__VA_ARGS__))

int notifyOn;
int bleConnected;

union CharValue {
    float floatVal;
    uint8 uintVal[4];
 };

union CharValue xData, yData, zData;

#endif

/* [] END OF FILE */
