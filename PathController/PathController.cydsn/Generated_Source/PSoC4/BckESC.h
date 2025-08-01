/*******************************************************************************
* File Name: BckESC.h  
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

#if !defined(CY_PINS_BckESC_H) /* Pins BckESC_H */
#define CY_PINS_BckESC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "BckESC_aliases.h"


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
} BckESC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   BckESC_Read(void);
void    BckESC_Write(uint8 value);
uint8   BckESC_ReadDataReg(void);
#if defined(BckESC__PC) || (CY_PSOC4_4200L) 
    void    BckESC_SetDriveMode(uint8 mode);
#endif
void    BckESC_SetInterruptMode(uint16 position, uint16 mode);
uint8   BckESC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void BckESC_Sleep(void); 
void BckESC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(BckESC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define BckESC_DRIVE_MODE_BITS        (3)
    #define BckESC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - BckESC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the BckESC_SetDriveMode() function.
         *  @{
         */
        #define BckESC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define BckESC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define BckESC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define BckESC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define BckESC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define BckESC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define BckESC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define BckESC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define BckESC_MASK               BckESC__MASK
#define BckESC_SHIFT              BckESC__SHIFT
#define BckESC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in BckESC_SetInterruptMode() function.
     *  @{
     */
        #define BckESC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define BckESC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define BckESC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define BckESC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(BckESC__SIO)
    #define BckESC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(BckESC__PC) && (CY_PSOC4_4200L)
    #define BckESC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define BckESC_USBIO_DISABLE              ((uint32)(~BckESC_USBIO_ENABLE))
    #define BckESC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define BckESC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define BckESC_USBIO_ENTER_SLEEP          ((uint32)((1u << BckESC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << BckESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define BckESC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << BckESC_USBIO_SUSPEND_SHIFT)))
    #define BckESC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << BckESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define BckESC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(BckESC__PC)
    /* Port Configuration */
    #define BckESC_PC                 (* (reg32 *) BckESC__PC)
#endif
/* Pin State */
#define BckESC_PS                     (* (reg32 *) BckESC__PS)
/* Data Register */
#define BckESC_DR                     (* (reg32 *) BckESC__DR)
/* Input Buffer Disable Override */
#define BckESC_INP_DIS                (* (reg32 *) BckESC__PC2)

/* Interrupt configuration Registers */
#define BckESC_INTCFG                 (* (reg32 *) BckESC__INTCFG)
#define BckESC_INTSTAT                (* (reg32 *) BckESC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define BckESC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(BckESC__SIO)
    #define BckESC_SIO_REG            (* (reg32 *) BckESC__SIO)
#endif /* (BckESC__SIO_CFG) */

/* USBIO registers */
#if !defined(BckESC__PC) && (CY_PSOC4_4200L)
    #define BckESC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define BckESC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define BckESC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define BckESC_DRIVE_MODE_SHIFT       (0x00u)
#define BckESC_DRIVE_MODE_MASK        (0x07u << BckESC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins BckESC_H */


/* [] END OF FILE */
