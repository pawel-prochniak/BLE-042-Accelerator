/*******************************************************************************
* File Name: PinIn.h  
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

#if !defined(CY_PINS_PinIn_H) /* Pins PinIn_H */
#define CY_PINS_PinIn_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PinIn_aliases.h"


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
} PinIn_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PinIn_Read(void);
void    PinIn_Write(uint8 value);
uint8   PinIn_ReadDataReg(void);
#if defined(PinIn__PC) || (CY_PSOC4_4200L) 
    void    PinIn_SetDriveMode(uint8 mode);
#endif
void    PinIn_SetInterruptMode(uint16 position, uint16 mode);
uint8   PinIn_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PinIn_Sleep(void); 
void PinIn_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PinIn__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PinIn_DRIVE_MODE_BITS        (3)
    #define PinIn_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PinIn_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PinIn_SetDriveMode() function.
         *  @{
         */
        #define PinIn_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PinIn_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PinIn_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PinIn_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PinIn_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PinIn_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PinIn_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PinIn_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PinIn_MASK               PinIn__MASK
#define PinIn_SHIFT              PinIn__SHIFT
#define PinIn_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PinIn_SetInterruptMode() function.
     *  @{
     */
        #define PinIn_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PinIn_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PinIn_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PinIn_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PinIn__SIO)
    #define PinIn_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PinIn__PC) && (CY_PSOC4_4200L)
    #define PinIn_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PinIn_USBIO_DISABLE              ((uint32)(~PinIn_USBIO_ENABLE))
    #define PinIn_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PinIn_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PinIn_USBIO_ENTER_SLEEP          ((uint32)((1u << PinIn_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PinIn_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinIn_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PinIn_USBIO_SUSPEND_SHIFT)))
    #define PinIn_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PinIn_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinIn_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PinIn__PC)
    /* Port Configuration */
    #define PinIn_PC                 (* (reg32 *) PinIn__PC)
#endif
/* Pin State */
#define PinIn_PS                     (* (reg32 *) PinIn__PS)
/* Data Register */
#define PinIn_DR                     (* (reg32 *) PinIn__DR)
/* Input Buffer Disable Override */
#define PinIn_INP_DIS                (* (reg32 *) PinIn__PC2)

/* Interrupt configuration Registers */
#define PinIn_INTCFG                 (* (reg32 *) PinIn__INTCFG)
#define PinIn_INTSTAT                (* (reg32 *) PinIn__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PinIn_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PinIn__SIO)
    #define PinIn_SIO_REG            (* (reg32 *) PinIn__SIO)
#endif /* (PinIn__SIO_CFG) */

/* USBIO registers */
#if !defined(PinIn__PC) && (CY_PSOC4_4200L)
    #define PinIn_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PinIn_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PinIn_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PinIn_DRIVE_MODE_SHIFT       (0x00u)
#define PinIn_DRIVE_MODE_MASK        (0x07u << PinIn_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PinIn_H */


/* [] END OF FILE */
