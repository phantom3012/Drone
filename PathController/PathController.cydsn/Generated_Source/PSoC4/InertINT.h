/*******************************************************************************
* File Name: InertINT.h  
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

#if !defined(CY_PINS_InertINT_H) /* Pins InertINT_H */
#define CY_PINS_InertINT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "InertINT_aliases.h"


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
} InertINT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   InertINT_Read(void);
void    InertINT_Write(uint8 value);
uint8   InertINT_ReadDataReg(void);
#if defined(InertINT__PC) || (CY_PSOC4_4200L) 
    void    InertINT_SetDriveMode(uint8 mode);
#endif
void    InertINT_SetInterruptMode(uint16 position, uint16 mode);
uint8   InertINT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void InertINT_Sleep(void); 
void InertINT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(InertINT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define InertINT_DRIVE_MODE_BITS        (3)
    #define InertINT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - InertINT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the InertINT_SetDriveMode() function.
         *  @{
         */
        #define InertINT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define InertINT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define InertINT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define InertINT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define InertINT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define InertINT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define InertINT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define InertINT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define InertINT_MASK               InertINT__MASK
#define InertINT_SHIFT              InertINT__SHIFT
#define InertINT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in InertINT_SetInterruptMode() function.
     *  @{
     */
        #define InertINT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define InertINT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define InertINT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define InertINT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(InertINT__SIO)
    #define InertINT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(InertINT__PC) && (CY_PSOC4_4200L)
    #define InertINT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define InertINT_USBIO_DISABLE              ((uint32)(~InertINT_USBIO_ENABLE))
    #define InertINT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define InertINT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define InertINT_USBIO_ENTER_SLEEP          ((uint32)((1u << InertINT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << InertINT_USBIO_SUSPEND_DEL_SHIFT)))
    #define InertINT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << InertINT_USBIO_SUSPEND_SHIFT)))
    #define InertINT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << InertINT_USBIO_SUSPEND_DEL_SHIFT)))
    #define InertINT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(InertINT__PC)
    /* Port Configuration */
    #define InertINT_PC                 (* (reg32 *) InertINT__PC)
#endif
/* Pin State */
#define InertINT_PS                     (* (reg32 *) InertINT__PS)
/* Data Register */
#define InertINT_DR                     (* (reg32 *) InertINT__DR)
/* Input Buffer Disable Override */
#define InertINT_INP_DIS                (* (reg32 *) InertINT__PC2)

/* Interrupt configuration Registers */
#define InertINT_INTCFG                 (* (reg32 *) InertINT__INTCFG)
#define InertINT_INTSTAT                (* (reg32 *) InertINT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define InertINT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(InertINT__SIO)
    #define InertINT_SIO_REG            (* (reg32 *) InertINT__SIO)
#endif /* (InertINT__SIO_CFG) */

/* USBIO registers */
#if !defined(InertINT__PC) && (CY_PSOC4_4200L)
    #define InertINT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define InertINT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define InertINT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define InertINT_DRIVE_MODE_SHIFT       (0x00u)
#define InertINT_DRIVE_MODE_MASK        (0x07u << InertINT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins InertINT_H */


/* [] END OF FILE */
