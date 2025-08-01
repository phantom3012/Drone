/*******************************************************************************
* File Name: BckLftSpdMon.h  
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

#if !defined(CY_PINS_BckLftSpdMon_H) /* Pins BckLftSpdMon_H */
#define CY_PINS_BckLftSpdMon_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BckLftSpdMon_aliases.h"


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
} BckLftSpdMon_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BckLftSpdMon_Read(void);
void    BckLftSpdMon_Write(uint8 value);
uint8   BckLftSpdMon_ReadDataReg(void);
#if defined(BckLftSpdMon__PC) || (CY_PSOC4_4200L) 
    void    BckLftSpdMon_SetDriveMode(uint8 mode);
#endif
void    BckLftSpdMon_SetInterruptMode(uint16 position, uint16 mode);
uint8   BckLftSpdMon_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BckLftSpdMon_Sleep(void); 
void BckLftSpdMon_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BckLftSpdMon__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BckLftSpdMon_DRIVE_MODE_BITS        (3)
    #define BckLftSpdMon_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BckLftSpdMon_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BckLftSpdMon_SetDriveMode() function.
         *  @{
         */
        #define BckLftSpdMon_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BckLftSpdMon_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BckLftSpdMon_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BckLftSpdMon_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BckLftSpdMon_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BckLftSpdMon_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BckLftSpdMon_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BckLftSpdMon_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BckLftSpdMon_MASK               BckLftSpdMon__MASK
#define BckLftSpdMon_SHIFT              BckLftSpdMon__SHIFT
#define BckLftSpdMon_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BckLftSpdMon_SetInterruptMode() function.
     *  @{
     */
        #define BckLftSpdMon_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BckLftSpdMon_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BckLftSpdMon_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BckLftSpdMon_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BckLftSpdMon__SIO)
    #define BckLftSpdMon_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BckLftSpdMon__PC) && (CY_PSOC4_4200L)
    #define BckLftSpdMon_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BckLftSpdMon_USBIO_DISABLE              ((uint32)(~BckLftSpdMon_USBIO_ENABLE))
    #define BckLftSpdMon_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BckLftSpdMon_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BckLftSpdMon_USBIO_ENTER_SLEEP          ((uint32)((1u << BckLftSpdMon_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BckLftSpdMon_USBIO_SUSPEND_DEL_SHIFT)))
    #define BckLftSpdMon_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BckLftSpdMon_USBIO_SUSPEND_SHIFT)))
    #define BckLftSpdMon_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BckLftSpdMon_USBIO_SUSPEND_DEL_SHIFT)))
    #define BckLftSpdMon_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BckLftSpdMon__PC)
    /* Port Configuration */
    #define BckLftSpdMon_PC                 (* (reg32 *) BckLftSpdMon__PC)
#endif
/* Pin State */
#define BckLftSpdMon_PS                     (* (reg32 *) BckLftSpdMon__PS)
/* Data Register */
#define BckLftSpdMon_DR                     (* (reg32 *) BckLftSpdMon__DR)
/* Input Buffer Disable Override */
#define BckLftSpdMon_INP_DIS                (* (reg32 *) BckLftSpdMon__PC2)

/* Interrupt configuration Registers */
#define BckLftSpdMon_INTCFG                 (* (reg32 *) BckLftSpdMon__INTCFG)
#define BckLftSpdMon_INTSTAT                (* (reg32 *) BckLftSpdMon__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BckLftSpdMon_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BckLftSpdMon__SIO)
    #define BckLftSpdMon_SIO_REG            (* (reg32 *) BckLftSpdMon__SIO)
#endif /* (BckLftSpdMon__SIO_CFG) */

/* USBIO registers */
#if !defined(BckLftSpdMon__PC) && (CY_PSOC4_4200L)
    #define BckLftSpdMon_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BckLftSpdMon_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BckLftSpdMon_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BckLftSpdMon_DRIVE_MODE_SHIFT       (0x00u)
#define BckLftSpdMon_DRIVE_MODE_MASK        (0x07u << BckLftSpdMon_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BckLftSpdMon_H */


/* [] END OF FILE */
