/*******************************************************************************
* File Name: PinOut.c  
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
#include "PinOut.h"

static PinOut_BACKUP_STRUCT  PinOut_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PinOut_Sleep
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
*  \snippet PinOut_SUT.c usage_PinOut_Sleep_Wakeup
*******************************************************************************/
void PinOut_Sleep(void)
{
    #if defined(PinOut__PC)
        PinOut_backup.pcState = PinOut_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PinOut_backup.usbState = PinOut_CR1_REG;
            PinOut_USB_POWER_REG |= PinOut_USBIO_ENTER_SLEEP;
            PinOut_CR1_REG &= PinOut_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PinOut__SIO)
        PinOut_backup.sioState = PinOut_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PinOut_SIO_REG &= (uint32)(~PinOut_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PinOut_Wakeup
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
*  Refer to PinOut_Sleep() for an example usage.
*******************************************************************************/
void PinOut_Wakeup(void)
{
    #if defined(PinOut__PC)
        PinOut_PC = PinOut_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PinOut_USB_POWER_REG &= PinOut_USBIO_EXIT_SLEEP_PH1;
            PinOut_CR1_REG = PinOut_backup.usbState;
            PinOut_USB_POWER_REG &= PinOut_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PinOut__SIO)
        PinOut_SIO_REG = PinOut_backup.sioState;
    #endif
}


/* [] END OF FILE */
