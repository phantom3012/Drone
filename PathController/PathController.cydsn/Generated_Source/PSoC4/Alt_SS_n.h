/*******************************************************************************
* File Name: Alt_SS_n.h  
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

#if !defined(CY_PINS_Alt_SS_n_H) /* Pins Alt_SS_n_H */
#define CY_PINS_Alt_SS_n_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Alt_SS_n_aliases.h"


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
} Alt_SS_n_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Alt_SS_n_Read(void);
void    Alt_SS_n_Write(uint8 value);
uint8   Alt_SS_n_ReadDataReg(void);
#if defined(Alt_SS_n__PC) || (CY_PSOC4_4200L) 
    void    Alt_SS_n_SetDriveMode(uint8 mode);
#endif
void    Alt_SS_n_SetInterruptMode(uint16 position, uint16 mode);
uint8   Alt_SS_n_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Alt_SS_n_Sleep(void); 
void Alt_SS_n_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Alt_SS_n__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Alt_SS_n_DRIVE_MODE_BITS        (3)
    #define Alt_SS_n_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Alt_SS_n_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Alt_SS_n_SetDriveMode() function.
         *  @{
         */
        #define Alt_SS_n_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Alt_SS_n_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Alt_SS_n_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Alt_SS_n_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Alt_SS_n_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Alt_SS_n_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Alt_SS_n_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Alt_SS_n_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Alt_SS_n_MASK               Alt_SS_n__MASK
#define Alt_SS_n_SHIFT              Alt_SS_n__SHIFT
#define Alt_SS_n_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Alt_SS_n_SetInterruptMode() function.
     *  @{
     */
        #define Alt_SS_n_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Alt_SS_n_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Alt_SS_n_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Alt_SS_n_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Alt_SS_n__SIO)
    #define Alt_SS_n_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Alt_SS_n__PC) && (CY_PSOC4_4200L)
    #define Alt_SS_n_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Alt_SS_n_USBIO_DISABLE              ((uint32)(~Alt_SS_n_USBIO_ENABLE))
    #define Alt_SS_n_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Alt_SS_n_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Alt_SS_n_USBIO_ENTER_SLEEP          ((uint32)((1u << Alt_SS_n_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Alt_SS_n_USBIO_SUSPEND_DEL_SHIFT)))
    #define Alt_SS_n_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Alt_SS_n_USBIO_SUSPEND_SHIFT)))
    #define Alt_SS_n_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Alt_SS_n_USBIO_SUSPEND_DEL_SHIFT)))
    #define Alt_SS_n_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Alt_SS_n__PC)
    /* Port Configuration */
    #define Alt_SS_n_PC                 (* (reg32 *) Alt_SS_n__PC)
#endif
/* Pin State */
#define Alt_SS_n_PS                     (* (reg32 *) Alt_SS_n__PS)
/* Data Register */
#define Alt_SS_n_DR                     (* (reg32 *) Alt_SS_n__DR)
/* Input Buffer Disable Override */
#define Alt_SS_n_INP_DIS                (* (reg32 *) Alt_SS_n__PC2)

/* Interrupt configuration Registers */
#define Alt_SS_n_INTCFG                 (* (reg32 *) Alt_SS_n__INTCFG)
#define Alt_SS_n_INTSTAT                (* (reg32 *) Alt_SS_n__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Alt_SS_n_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Alt_SS_n__SIO)
    #define Alt_SS_n_SIO_REG            (* (reg32 *) Alt_SS_n__SIO)
#endif /* (Alt_SS_n__SIO_CFG) */

/* USBIO registers */
#if !defined(Alt_SS_n__PC) && (CY_PSOC4_4200L)
    #define Alt_SS_n_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Alt_SS_n_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Alt_SS_n_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Alt_SS_n_DRIVE_MODE_SHIFT       (0x00u)
#define Alt_SS_n_DRIVE_MODE_MASK        (0x07u << Alt_SS_n_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Alt_SS_n_H */


/* [] END OF FILE */
