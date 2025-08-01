/*******************************************************************************
* File Name: FrntESC.h  
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

#if !defined(CY_PINS_FrntESC_H) /* Pins FrntESC_H */
#define CY_PINS_FrntESC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FrntESC_aliases.h"


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
} FrntESC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   FrntESC_Read(void);
void    FrntESC_Write(uint8 value);
uint8   FrntESC_ReadDataReg(void);
#if defined(FrntESC__PC) || (CY_PSOC4_4200L) 
    void    FrntESC_SetDriveMode(uint8 mode);
#endif
void    FrntESC_SetInterruptMode(uint16 position, uint16 mode);
uint8   FrntESC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void FrntESC_Sleep(void); 
void FrntESC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(FrntESC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define FrntESC_DRIVE_MODE_BITS        (3)
    #define FrntESC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FrntESC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the FrntESC_SetDriveMode() function.
         *  @{
         */
        #define FrntESC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define FrntESC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define FrntESC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define FrntESC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define FrntESC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define FrntESC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define FrntESC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define FrntESC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define FrntESC_MASK               FrntESC__MASK
#define FrntESC_SHIFT              FrntESC__SHIFT
#define FrntESC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FrntESC_SetInterruptMode() function.
     *  @{
     */
        #define FrntESC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define FrntESC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define FrntESC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define FrntESC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(FrntESC__SIO)
    #define FrntESC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(FrntESC__PC) && (CY_PSOC4_4200L)
    #define FrntESC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define FrntESC_USBIO_DISABLE              ((uint32)(~FrntESC_USBIO_ENABLE))
    #define FrntESC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define FrntESC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define FrntESC_USBIO_ENTER_SLEEP          ((uint32)((1u << FrntESC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << FrntESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define FrntESC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << FrntESC_USBIO_SUSPEND_SHIFT)))
    #define FrntESC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << FrntESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define FrntESC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(FrntESC__PC)
    /* Port Configuration */
    #define FrntESC_PC                 (* (reg32 *) FrntESC__PC)
#endif
/* Pin State */
#define FrntESC_PS                     (* (reg32 *) FrntESC__PS)
/* Data Register */
#define FrntESC_DR                     (* (reg32 *) FrntESC__DR)
/* Input Buffer Disable Override */
#define FrntESC_INP_DIS                (* (reg32 *) FrntESC__PC2)

/* Interrupt configuration Registers */
#define FrntESC_INTCFG                 (* (reg32 *) FrntESC__INTCFG)
#define FrntESC_INTSTAT                (* (reg32 *) FrntESC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define FrntESC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(FrntESC__SIO)
    #define FrntESC_SIO_REG            (* (reg32 *) FrntESC__SIO)
#endif /* (FrntESC__SIO_CFG) */

/* USBIO registers */
#if !defined(FrntESC__PC) && (CY_PSOC4_4200L)
    #define FrntESC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define FrntESC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define FrntESC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define FrntESC_DRIVE_MODE_SHIFT       (0x00u)
#define FrntESC_DRIVE_MODE_MASK        (0x07u << FrntESC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins FrntESC_H */


/* [] END OF FILE */
