/*******************************************************************************
* File Name: MagSS_n.h  
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

#if !defined(CY_PINS_MagSS_n_H) /* Pins MagSS_n_H */
#define CY_PINS_MagSS_n_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MagSS_n_aliases.h"


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
} MagSS_n_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MagSS_n_Read(void);
void    MagSS_n_Write(uint8 value);
uint8   MagSS_n_ReadDataReg(void);
#if defined(MagSS_n__PC) || (CY_PSOC4_4200L) 
    void    MagSS_n_SetDriveMode(uint8 mode);
#endif
void    MagSS_n_SetInterruptMode(uint16 position, uint16 mode);
uint8   MagSS_n_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MagSS_n_Sleep(void); 
void MagSS_n_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MagSS_n__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MagSS_n_DRIVE_MODE_BITS        (3)
    #define MagSS_n_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MagSS_n_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MagSS_n_SetDriveMode() function.
         *  @{
         */
        #define MagSS_n_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MagSS_n_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MagSS_n_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MagSS_n_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MagSS_n_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MagSS_n_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MagSS_n_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MagSS_n_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MagSS_n_MASK               MagSS_n__MASK
#define MagSS_n_SHIFT              MagSS_n__SHIFT
#define MagSS_n_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MagSS_n_SetInterruptMode() function.
     *  @{
     */
        #define MagSS_n_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MagSS_n_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MagSS_n_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MagSS_n_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MagSS_n__SIO)
    #define MagSS_n_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MagSS_n__PC) && (CY_PSOC4_4200L)
    #define MagSS_n_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MagSS_n_USBIO_DISABLE              ((uint32)(~MagSS_n_USBIO_ENABLE))
    #define MagSS_n_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MagSS_n_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MagSS_n_USBIO_ENTER_SLEEP          ((uint32)((1u << MagSS_n_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MagSS_n_USBIO_SUSPEND_DEL_SHIFT)))
    #define MagSS_n_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MagSS_n_USBIO_SUSPEND_SHIFT)))
    #define MagSS_n_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MagSS_n_USBIO_SUSPEND_DEL_SHIFT)))
    #define MagSS_n_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MagSS_n__PC)
    /* Port Configuration */
    #define MagSS_n_PC                 (* (reg32 *) MagSS_n__PC)
#endif
/* Pin State */
#define MagSS_n_PS                     (* (reg32 *) MagSS_n__PS)
/* Data Register */
#define MagSS_n_DR                     (* (reg32 *) MagSS_n__DR)
/* Input Buffer Disable Override */
#define MagSS_n_INP_DIS                (* (reg32 *) MagSS_n__PC2)

/* Interrupt configuration Registers */
#define MagSS_n_INTCFG                 (* (reg32 *) MagSS_n__INTCFG)
#define MagSS_n_INTSTAT                (* (reg32 *) MagSS_n__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MagSS_n_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MagSS_n__SIO)
    #define MagSS_n_SIO_REG            (* (reg32 *) MagSS_n__SIO)
#endif /* (MagSS_n__SIO_CFG) */

/* USBIO registers */
#if !defined(MagSS_n__PC) && (CY_PSOC4_4200L)
    #define MagSS_n_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MagSS_n_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MagSS_n_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MagSS_n_DRIVE_MODE_SHIFT       (0x00u)
#define MagSS_n_DRIVE_MODE_MASK        (0x07u << MagSS_n_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MagSS_n_H */


/* [] END OF FILE */
