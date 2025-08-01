/*******************************************************************************
* File Name: BckLftESC.h  
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

#if !defined(CY_PINS_BckLftESC_H) /* Pins BckLftESC_H */
#define CY_PINS_BckLftESC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BckLftESC_aliases.h"


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
} BckLftESC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BckLftESC_Read(void);
void    BckLftESC_Write(uint8 value);
uint8   BckLftESC_ReadDataReg(void);
#if defined(BckLftESC__PC) || (CY_PSOC4_4200L) 
    void    BckLftESC_SetDriveMode(uint8 mode);
#endif
void    BckLftESC_SetInterruptMode(uint16 position, uint16 mode);
uint8   BckLftESC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BckLftESC_Sleep(void); 
void BckLftESC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BckLftESC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BckLftESC_DRIVE_MODE_BITS        (3)
    #define BckLftESC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BckLftESC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BckLftESC_SetDriveMode() function.
         *  @{
         */
        #define BckLftESC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BckLftESC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BckLftESC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BckLftESC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BckLftESC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BckLftESC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BckLftESC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BckLftESC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BckLftESC_MASK               BckLftESC__MASK
#define BckLftESC_SHIFT              BckLftESC__SHIFT
#define BckLftESC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BckLftESC_SetInterruptMode() function.
     *  @{
     */
        #define BckLftESC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BckLftESC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BckLftESC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BckLftESC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BckLftESC__SIO)
    #define BckLftESC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BckLftESC__PC) && (CY_PSOC4_4200L)
    #define BckLftESC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BckLftESC_USBIO_DISABLE              ((uint32)(~BckLftESC_USBIO_ENABLE))
    #define BckLftESC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BckLftESC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BckLftESC_USBIO_ENTER_SLEEP          ((uint32)((1u << BckLftESC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BckLftESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define BckLftESC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BckLftESC_USBIO_SUSPEND_SHIFT)))
    #define BckLftESC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BckLftESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define BckLftESC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BckLftESC__PC)
    /* Port Configuration */
    #define BckLftESC_PC                 (* (reg32 *) BckLftESC__PC)
#endif
/* Pin State */
#define BckLftESC_PS                     (* (reg32 *) BckLftESC__PS)
/* Data Register */
#define BckLftESC_DR                     (* (reg32 *) BckLftESC__DR)
/* Input Buffer Disable Override */
#define BckLftESC_INP_DIS                (* (reg32 *) BckLftESC__PC2)

/* Interrupt configuration Registers */
#define BckLftESC_INTCFG                 (* (reg32 *) BckLftESC__INTCFG)
#define BckLftESC_INTSTAT                (* (reg32 *) BckLftESC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BckLftESC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BckLftESC__SIO)
    #define BckLftESC_SIO_REG            (* (reg32 *) BckLftESC__SIO)
#endif /* (BckLftESC__SIO_CFG) */

/* USBIO registers */
#if !defined(BckLftESC__PC) && (CY_PSOC4_4200L)
    #define BckLftESC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BckLftESC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BckLftESC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BckLftESC_DRIVE_MODE_SHIFT       (0x00u)
#define BckLftESC_DRIVE_MODE_MASK        (0x07u << BckLftESC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BckLftESC_H */


/* [] END OF FILE */
