/*******************************************************************************
* File Name: VBatt.h  
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

#if !defined(CY_PINS_VBatt_H) /* Pins VBatt_H */
#define CY_PINS_VBatt_H

#include "cytypes.h"
#include "cyfitter.h"
#include "VBatt_aliases.h"


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
} VBatt_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   VBatt_Read(void);
void    VBatt_Write(uint8 value);
uint8   VBatt_ReadDataReg(void);
#if defined(VBatt__PC) || (CY_PSOC4_4200L) 
    void    VBatt_SetDriveMode(uint8 mode);
#endif
void    VBatt_SetInterruptMode(uint16 position, uint16 mode);
uint8   VBatt_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void VBatt_Sleep(void); 
void VBatt_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(VBatt__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define VBatt_DRIVE_MODE_BITS        (3)
    #define VBatt_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - VBatt_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the VBatt_SetDriveMode() function.
         *  @{
         */
        #define VBatt_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define VBatt_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define VBatt_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define VBatt_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define VBatt_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define VBatt_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define VBatt_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define VBatt_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define VBatt_MASK               VBatt__MASK
#define VBatt_SHIFT              VBatt__SHIFT
#define VBatt_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in VBatt_SetInterruptMode() function.
     *  @{
     */
        #define VBatt_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define VBatt_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define VBatt_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define VBatt_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(VBatt__SIO)
    #define VBatt_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(VBatt__PC) && (CY_PSOC4_4200L)
    #define VBatt_USBIO_ENABLE               ((uint32)0x80000000u)
    #define VBatt_USBIO_DISABLE              ((uint32)(~VBatt_USBIO_ENABLE))
    #define VBatt_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define VBatt_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define VBatt_USBIO_ENTER_SLEEP          ((uint32)((1u << VBatt_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << VBatt_USBIO_SUSPEND_DEL_SHIFT)))
    #define VBatt_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << VBatt_USBIO_SUSPEND_SHIFT)))
    #define VBatt_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << VBatt_USBIO_SUSPEND_DEL_SHIFT)))
    #define VBatt_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(VBatt__PC)
    /* Port Configuration */
    #define VBatt_PC                 (* (reg32 *) VBatt__PC)
#endif
/* Pin State */
#define VBatt_PS                     (* (reg32 *) VBatt__PS)
/* Data Register */
#define VBatt_DR                     (* (reg32 *) VBatt__DR)
/* Input Buffer Disable Override */
#define VBatt_INP_DIS                (* (reg32 *) VBatt__PC2)

/* Interrupt configuration Registers */
#define VBatt_INTCFG                 (* (reg32 *) VBatt__INTCFG)
#define VBatt_INTSTAT                (* (reg32 *) VBatt__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define VBatt_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(VBatt__SIO)
    #define VBatt_SIO_REG            (* (reg32 *) VBatt__SIO)
#endif /* (VBatt__SIO_CFG) */

/* USBIO registers */
#if !defined(VBatt__PC) && (CY_PSOC4_4200L)
    #define VBatt_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define VBatt_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define VBatt_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define VBatt_DRIVE_MODE_SHIFT       (0x00u)
#define VBatt_DRIVE_MODE_MASK        (0x07u << VBatt_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins VBatt_H */


/* [] END OF FILE */
