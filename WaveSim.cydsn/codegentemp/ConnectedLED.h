/*******************************************************************************
* File Name: ConnectedLED.h  
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

#if !defined(CY_PINS_ConnectedLED_H) /* Pins ConnectedLED_H */
#define CY_PINS_ConnectedLED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ConnectedLED_aliases.h"


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
} ConnectedLED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ConnectedLED_Read(void);
void    ConnectedLED_Write(uint8 value);
uint8   ConnectedLED_ReadDataReg(void);
#if defined(ConnectedLED__PC) || (CY_PSOC4_4200L) 
    void    ConnectedLED_SetDriveMode(uint8 mode);
#endif
void    ConnectedLED_SetInterruptMode(uint16 position, uint16 mode);
uint8   ConnectedLED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ConnectedLED_Sleep(void); 
void ConnectedLED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ConnectedLED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ConnectedLED_DRIVE_MODE_BITS        (3)
    #define ConnectedLED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ConnectedLED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ConnectedLED_SetDriveMode() function.
         *  @{
         */
        #define ConnectedLED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ConnectedLED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ConnectedLED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ConnectedLED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ConnectedLED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ConnectedLED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ConnectedLED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ConnectedLED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ConnectedLED_MASK               ConnectedLED__MASK
#define ConnectedLED_SHIFT              ConnectedLED__SHIFT
#define ConnectedLED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ConnectedLED_SetInterruptMode() function.
     *  @{
     */
        #define ConnectedLED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ConnectedLED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ConnectedLED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ConnectedLED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ConnectedLED__SIO)
    #define ConnectedLED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ConnectedLED__PC) && (CY_PSOC4_4200L)
    #define ConnectedLED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ConnectedLED_USBIO_DISABLE              ((uint32)(~ConnectedLED_USBIO_ENABLE))
    #define ConnectedLED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ConnectedLED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ConnectedLED_USBIO_ENTER_SLEEP          ((uint32)((1u << ConnectedLED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ConnectedLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define ConnectedLED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ConnectedLED_USBIO_SUSPEND_SHIFT)))
    #define ConnectedLED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ConnectedLED_USBIO_SUSPEND_DEL_SHIFT)))
    #define ConnectedLED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ConnectedLED__PC)
    /* Port Configuration */
    #define ConnectedLED_PC                 (* (reg32 *) ConnectedLED__PC)
#endif
/* Pin State */
#define ConnectedLED_PS                     (* (reg32 *) ConnectedLED__PS)
/* Data Register */
#define ConnectedLED_DR                     (* (reg32 *) ConnectedLED__DR)
/* Input Buffer Disable Override */
#define ConnectedLED_INP_DIS                (* (reg32 *) ConnectedLED__PC2)

/* Interrupt configuration Registers */
#define ConnectedLED_INTCFG                 (* (reg32 *) ConnectedLED__INTCFG)
#define ConnectedLED_INTSTAT                (* (reg32 *) ConnectedLED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ConnectedLED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ConnectedLED__SIO)
    #define ConnectedLED_SIO_REG            (* (reg32 *) ConnectedLED__SIO)
#endif /* (ConnectedLED__SIO_CFG) */

/* USBIO registers */
#if !defined(ConnectedLED__PC) && (CY_PSOC4_4200L)
    #define ConnectedLED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ConnectedLED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ConnectedLED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ConnectedLED_DRIVE_MODE_SHIFT       (0x00u)
#define ConnectedLED_DRIVE_MODE_MASK        (0x07u << ConnectedLED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ConnectedLED_H */


/* [] END OF FILE */
