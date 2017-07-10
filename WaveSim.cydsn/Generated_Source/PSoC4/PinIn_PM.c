/*******************************************************************************
* File Name: PinIn.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "PinIn.h"

static PinIn_BACKUP_STRUCT  PinIn_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PinIn_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet PinIn_SUT.c usage_PinIn_Sleep_Wakeup
*******************************************************************************/
void PinIn_Sleep(void)
{
    #if defined(PinIn__PC)
        PinIn_backup.pcState = PinIn_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PinIn_backup.usbState = PinIn_CR1_REG;
            PinIn_USB_POWER_REG |= PinIn_USBIO_ENTER_SLEEP;
            PinIn_CR1_REG &= PinIn_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PinIn__SIO)
        PinIn_backup.sioState = PinIn_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PinIn_SIO_REG &= (uint32)(~PinIn_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PinIn_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to PinIn_Sleep() for an example usage.
*******************************************************************************/
void PinIn_Wakeup(void)
{
    #if defined(PinIn__PC)
        PinIn_PC = PinIn_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PinIn_USB_POWER_REG &= PinIn_USBIO_EXIT_SLEEP_PH1;
            PinIn_CR1_REG = PinIn_backup.usbState;
            PinIn_USB_POWER_REG &= PinIn_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PinIn__SIO)
        PinIn_SIO_REG = PinIn_backup.sioState;
    #endif
}


/* [] END OF FILE */
