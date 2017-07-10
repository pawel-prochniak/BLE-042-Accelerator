/*******************************************************************************
* File Name: PinIn.h  
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

#if !defined(CY_PINS_PinIn_ALIASES_H) /* Pins PinIn_ALIASES_H */
#define CY_PINS_PinIn_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PinIn_0			(PinIn__0__PC)
#define PinIn_0_PS		(PinIn__0__PS)
#define PinIn_0_PC		(PinIn__0__PC)
#define PinIn_0_DR		(PinIn__0__DR)
#define PinIn_0_SHIFT	(PinIn__0__SHIFT)
#define PinIn_0_INTR	((uint16)((uint16)0x0003u << (PinIn__0__SHIFT*2u)))

#define PinIn_INTR_ALL	 ((uint16)(PinIn_0_INTR))


#endif /* End Pins PinIn_ALIASES_H */


/* [] END OF FILE */
