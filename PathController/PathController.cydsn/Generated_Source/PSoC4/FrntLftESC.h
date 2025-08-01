/*******************************************************************************
* File Name: FrntLftESC.h  
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

#if !defined(CY_PINS_FrntLftESC_H) /* Pins FrntLftESC_H */
#define CY_PINS_FrntLftESC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FrntLftESC_aliases.h"


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
} FrntLftESC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   FrntLftESC_Read(void);
void    FrntLftESC_Write(uint8 value);
uint8   FrntLftESC_ReadDataReg(void);
#if defined(FrntLftESC__PC) || (CY_PSOC4_4200L) 
    void    FrntLftESC_SetDriveMode(uint8 mode);
#endif
void    FrntLftESC_SetInterruptMode(uint16 position, uint16 mode);
uint8   FrntLftESC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void FrntLftESC_Sleep(void); 
void FrntLftESC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(FrntLftESC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define FrntLftESC_DRIVE_MODE_BITS        (3)
    #define FrntLftESC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FrntLftESC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the FrntLftESC_SetDriveMode() function.
         *  @{
         */
        #define FrntLftESC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define FrntLftESC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define FrntLftESC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define FrntLftESC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define FrntLftESC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define FrntLftESC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define FrntLftESC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define FrntLftESC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define FrntLftESC_MASK               FrntLftESC__MASK
#define FrntLftESC_SHIFT              FrntLftESC__SHIFT
#define FrntLftESC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FrntLftESC_SetInterruptMode() function.
     *  @{
     */
        #define FrntLftESC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define FrntLftESC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define FrntLftESC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define FrntLftESC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(FrntLftESC__SIO)
    #define FrntLftESC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(FrntLftESC__PC) && (CY_PSOC4_4200L)
    #define FrntLftESC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define FrntLftESC_USBIO_DISABLE              ((uint32)(~FrntLftESC_USBIO_ENABLE))
    #define FrntLftESC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define FrntLftESC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define FrntLftESC_USBIO_ENTER_SLEEP          ((uint32)((1u << FrntLftESC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << FrntLftESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define FrntLftESC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << FrntLftESC_USBIO_SUSPEND_SHIFT)))
    #define FrntLftESC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << FrntLftESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define FrntLftESC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(FrntLftESC__PC)
    /* Port Configuration */
    #define FrntLftESC_PC                 (* (reg32 *) FrntLftESC__PC)
#endif
/* Pin State */
#define FrntLftESC_PS                     (* (reg32 *) FrntLftESC__PS)
/* Data Register */
#define FrntLftESC_DR                     (* (reg32 *) FrntLftESC__DR)
/* Input Buffer Disable Override */
#define FrntLftESC_INP_DIS                (* (reg32 *) FrntLftESC__PC2)

/* Interrupt configuration Registers */
#define FrntLftESC_INTCFG                 (* (reg32 *) FrntLftESC__INTCFG)
#define FrntLftESC_INTSTAT                (* (reg32 *) FrntLftESC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define FrntLftESC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(FrntLftESC__SIO)
    #define FrntLftESC_SIO_REG            (* (reg32 *) FrntLftESC__SIO)
#endif /* (FrntLftESC__SIO_CFG) */

/* USBIO registers */
#if !defined(FrntLftESC__PC) && (CY_PSOC4_4200L)
    #define FrntLftESC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define FrntLftESC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define FrntLftESC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define FrntLftESC_DRIVE_MODE_SHIFT       (0x00u)
#define FrntLftESC_DRIVE_MODE_MASK        (0x07u << FrntLftESC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins FrntLftESC_H */


/* [] END OF FILE */
