/*******************************************************************************
* File Name: ConnectedLED.h  
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

#if !defined(CY_PINS_ConnectedLED_ALIASES_H) /* Pins ConnectedLED_ALIASES_H */
#define CY_PINS_ConnectedLED_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define ConnectedLED_0			(ConnectedLED__0__PC)
#define ConnectedLED_0_PS		(ConnectedLED__0__PS)
#define ConnectedLED_0_PC		(ConnectedLED__0__PC)
#define ConnectedLED_0_DR		(ConnectedLED__0__DR)
#define ConnectedLED_0_SHIFT	(ConnectedLED__0__SHIFT)
#define ConnectedLED_0_INTR	((uint16)((uint16)0x0003u << (ConnectedLED__0__SHIFT*2u)))

#define ConnectedLED_INTR_ALL	 ((uint16)(ConnectedLED_0_INTR))


#endif /* End Pins ConnectedLED_ALIASES_H */


/* [] END OF FILE */
