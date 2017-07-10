/*******************************************************************************
* File Name: AdvLED.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_AdvLED_ALIASES_H) /* Pins AdvLED_ALIASES_H */
#define CY_PINS_AdvLED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AdvLED_0			(AdvLED__0__PC)
#define AdvLED_0_PS		(AdvLED__0__PS)
#define AdvLED_0_PC		(AdvLED__0__PC)
#define AdvLED_0_DR		(AdvLED__0__DR)
#define AdvLED_0_SHIFT	(AdvLED__0__SHIFT)
#define AdvLED_0_INTR	((uint16)((uint16)0x0003u << (AdvLED__0__SHIFT*2u)))

#define AdvLED_INTR_ALL	 ((uint16)(AdvLED_0_INTR))


#endif /* End Pins AdvLED_ALIASES_H */


/* [] END OF FILE */
