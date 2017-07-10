/*******************************************************************************
* File Name: PinOut.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PinOut_H) /* Pins PinOut_H */
#define CY_PINS_PinOut_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PinOut_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} PinOut_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PinOut_Read(void);
void    PinOut_Write(uint8 value);
uint8   PinOut_ReadDataReg(void);
#if defined(PinOut__PC) || (CY_PSOC4_4200L) 
    void    PinOut_SetDriveMode(uint8 mode);
#endif
void    PinOut_SetInterruptMode(uint16 position, uint16 mode);
uint8   PinOut_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PinOut_Sleep(void); 
void PinOut_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PinOut__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PinOut_DRIVE_MODE_BITS        (3)
    #define PinOut_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PinOut_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PinOut_SetDriveMode() function.
         *  @{
         */
        #define PinOut_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PinOut_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PinOut_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PinOut_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PinOut_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PinOut_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PinOut_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PinOut_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PinOut_MASK               PinOut__MASK
#define PinOut_SHIFT              PinOut__SHIFT
#define PinOut_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PinOut_SetInterruptMode() function.
     *  @{
     */
        #define PinOut_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PinOut_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PinOut_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PinOut_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PinOut__SIO)
    #define PinOut_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PinOut__PC) && (CY_PSOC4_4200L)
    #define PinOut_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PinOut_USBIO_DISABLE              ((uint32)(~PinOut_USBIO_ENABLE))
    #define PinOut_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PinOut_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PinOut_USBIO_ENTER_SLEEP          ((uint32)((1u << PinOut_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PinOut_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinOut_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PinOut_USBIO_SUSPEND_SHIFT)))
    #define PinOut_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PinOut_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinOut_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PinOut__PC)
    /* Port Configuration */
    #define PinOut_PC                 (* (reg32 *) PinOut__PC)
#endif
/* Pin State */
#define PinOut_PS                     (* (reg32 *) PinOut__PS)
/* Data Register */
#define PinOut_DR                     (* (reg32 *) PinOut__DR)
/* Input Buffer Disable Override */
#define PinOut_INP_DIS                (* (reg32 *) PinOut__PC2)

/* Interrupt configuration Registers */
#define PinOut_INTCFG                 (* (reg32 *) PinOut__INTCFG)
#define PinOut_INTSTAT                (* (reg32 *) PinOut__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PinOut_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PinOut__SIO)
    #define PinOut_SIO_REG            (* (reg32 *) PinOut__SIO)
#endif /* (PinOut__SIO_CFG) */

/* USBIO registers */
#if !defined(PinOut__PC) && (CY_PSOC4_4200L)
    #define PinOut_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PinOut_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PinOut_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PinOut_DRIVE_MODE_SHIFT       (0x00u)
#define PinOut_DRIVE_MODE_MASK        (0x07u << PinOut_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PinOut_H */


/* [] END OF FILE */
