/*******************************************************************************
* File Name: AdvLED.h  
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

#if !defined(CY_PINS_AdvLED_H) /* Pins AdvLED_H */
#define CY_PINS_AdvLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "AdvLED_aliases.h"


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
} AdvLED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   AdvLED_Read(void);
void    AdvLED_Write(uint8 value);
uint8   AdvLED_ReadDataReg(void);
#if defined(AdvLED__PC) || (CY_PSOC4_4200L) 
    void    AdvLED_SetDriveMode(uint8 mode);
#endif
void    AdvLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   AdvLED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void AdvLED_Sleep(void); 
void AdvLED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(AdvLED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define AdvLED_DRIVE_MODE_BITS        (3)
    #define AdvLED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - AdvLED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the AdvLED_SetDriveMode() function.
         *  @{
         */
        #define AdvLED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define AdvLED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define AdvLED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define AdvLED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define AdvLED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define AdvLED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define AdvLED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define AdvLED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define AdvLED_MASK               AdvLED__MASK
#define AdvLED_SHIFT              AdvLED__SHIFT
#define AdvLED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AdvLED_SetInterruptMode() function.
     *  @{
     */
        #define AdvLED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define AdvLED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define AdvLED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define AdvLED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(AdvLED__SIO)
    #define AdvLED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(AdvLED__PC) && (CY_PSOC4_4200L)
    #define AdvLED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define AdvLED_USBIO_DISABLE              ((uint32)(~AdvLED_USBIO_ENABLE))
    #define AdvLED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define AdvLED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define AdvLED_USBIO_ENTER_SLEEP          ((uint32)((1u << AdvLED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << AdvLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define AdvLED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << AdvLED_USBIO_SUSPEND_SHIFT)))
    #define AdvLED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << AdvLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define AdvLED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(AdvLED__PC)
    /* Port Configuration */
    #define AdvLED_PC                 (* (reg32 *) AdvLED__PC)
#endif
/* Pin State */
#define AdvLED_PS                     (* (reg32 *) AdvLED__PS)
/* Data Register */
#define AdvLED_DR                     (* (reg32 *) AdvLED__DR)
/* Input Buffer Disable Override */
#define AdvLED_INP_DIS                (* (reg32 *) AdvLED__PC2)

/* Interrupt configuration Registers */
#define AdvLED_INTCFG                 (* (reg32 *) AdvLED__INTCFG)
#define AdvLED_INTSTAT                (* (reg32 *) AdvLED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define AdvLED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(AdvLED__SIO)
    #define AdvLED_SIO_REG            (* (reg32 *) AdvLED__SIO)
#endif /* (AdvLED__SIO_CFG) */

/* USBIO registers */
#if !defined(AdvLED__PC) && (CY_PSOC4_4200L)
    #define AdvLED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define AdvLED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define AdvLED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define AdvLED_DRIVE_MODE_SHIFT       (0x00u)
#define AdvLED_DRIVE_MODE_MASK        (0x07u << AdvLED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins AdvLED_H */


/* [] END OF FILE */
