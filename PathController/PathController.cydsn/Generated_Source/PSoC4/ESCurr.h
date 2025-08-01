/*******************************************************************************
* File Name: ESCurr.h  
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

#if !defined(CY_PINS_ESCurr_H) /* Pins ESCurr_H */
#define CY_PINS_ESCurr_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ESCurr_aliases.h"


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
} ESCurr_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   ESCurr_Read(void);
void    ESCurr_Write(uint8 value);
uint8   ESCurr_ReadDataReg(void);
#if defined(ESCurr__PC) || (CY_PSOC4_4200L) 
    void    ESCurr_SetDriveMode(uint8 mode);
#endif
void    ESCurr_SetInterruptMode(uint16 position, uint16 mode);
uint8   ESCurr_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void ESCurr_Sleep(void); 
void ESCurr_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(ESCurr__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define ESCurr_DRIVE_MODE_BITS        (3)
    #define ESCurr_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ESCurr_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the ESCurr_SetDriveMode() function.
         *  @{
         */
        #define ESCurr_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define ESCurr_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define ESCurr_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define ESCurr_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define ESCurr_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define ESCurr_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define ESCurr_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define ESCurr_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define ESCurr_MASK               ESCurr__MASK
#define ESCurr_SHIFT              ESCurr__SHIFT
#define ESCurr_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ESCurr_SetInterruptMode() function.
     *  @{
     */
        #define ESCurr_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define ESCurr_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define ESCurr_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define ESCurr_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(ESCurr__SIO)
    #define ESCurr_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(ESCurr__PC) && (CY_PSOC4_4200L)
    #define ESCurr_USBIO_ENABLE               ((uint32)0x80000000u)
    #define ESCurr_USBIO_DISABLE              ((uint32)(~ESCurr_USBIO_ENABLE))
    #define ESCurr_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define ESCurr_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define ESCurr_USBIO_ENTER_SLEEP          ((uint32)((1u << ESCurr_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << ESCurr_USBIO_SUSPEND_DEL_SHIFT)))
    #define ESCurr_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << ESCurr_USBIO_SUSPEND_SHIFT)))
    #define ESCurr_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << ESCurr_USBIO_SUSPEND_DEL_SHIFT)))
    #define ESCurr_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(ESCurr__PC)
    /* Port Configuration */
    #define ESCurr_PC                 (* (reg32 *) ESCurr__PC)
#endif
/* Pin State */
#define ESCurr_PS                     (* (reg32 *) ESCurr__PS)
/* Data Register */
#define ESCurr_DR                     (* (reg32 *) ESCurr__DR)
/* Input Buffer Disable Override */
#define ESCurr_INP_DIS                (* (reg32 *) ESCurr__PC2)

/* Interrupt configuration Registers */
#define ESCurr_INTCFG                 (* (reg32 *) ESCurr__INTCFG)
#define ESCurr_INTSTAT                (* (reg32 *) ESCurr__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define ESCurr_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(ESCurr__SIO)
    #define ESCurr_SIO_REG            (* (reg32 *) ESCurr__SIO)
#endif /* (ESCurr__SIO_CFG) */

/* USBIO registers */
#if !defined(ESCurr__PC) && (CY_PSOC4_4200L)
    #define ESCurr_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define ESCurr_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define ESCurr_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define ESCurr_DRIVE_MODE_SHIFT       (0x00u)
#define ESCurr_DRIVE_MODE_MASK        (0x07u << ESCurr_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins ESCurr_H */


/* [] END OF FILE */
