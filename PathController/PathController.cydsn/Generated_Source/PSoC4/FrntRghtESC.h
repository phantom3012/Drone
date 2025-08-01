/*******************************************************************************
* File Name: FrntRghtESC.h  
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

#if !defined(CY_PINS_FrntRghtESC_H) /* Pins FrntRghtESC_H */
#define CY_PINS_FrntRghtESC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FrntRghtESC_aliases.h"


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
} FrntRghtESC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   FrntRghtESC_Read(void);
void    FrntRghtESC_Write(uint8 value);
uint8   FrntRghtESC_ReadDataReg(void);
#if defined(FrntRghtESC__PC) || (CY_PSOC4_4200L) 
    void    FrntRghtESC_SetDriveMode(uint8 mode);
#endif
void    FrntRghtESC_SetInterruptMode(uint16 position, uint16 mode);
uint8   FrntRghtESC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void FrntRghtESC_Sleep(void); 
void FrntRghtESC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(FrntRghtESC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define FrntRghtESC_DRIVE_MODE_BITS        (3)
    #define FrntRghtESC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FrntRghtESC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the FrntRghtESC_SetDriveMode() function.
         *  @{
         */
        #define FrntRghtESC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define FrntRghtESC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define FrntRghtESC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define FrntRghtESC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define FrntRghtESC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define FrntRghtESC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define FrntRghtESC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define FrntRghtESC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define FrntRghtESC_MASK               FrntRghtESC__MASK
#define FrntRghtESC_SHIFT              FrntRghtESC__SHIFT
#define FrntRghtESC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FrntRghtESC_SetInterruptMode() function.
     *  @{
     */
        #define FrntRghtESC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define FrntRghtESC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define FrntRghtESC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define FrntRghtESC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(FrntRghtESC__SIO)
    #define FrntRghtESC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(FrntRghtESC__PC) && (CY_PSOC4_4200L)
    #define FrntRghtESC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define FrntRghtESC_USBIO_DISABLE              ((uint32)(~FrntRghtESC_USBIO_ENABLE))
    #define FrntRghtESC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define FrntRghtESC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define FrntRghtESC_USBIO_ENTER_SLEEP          ((uint32)((1u << FrntRghtESC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << FrntRghtESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define FrntRghtESC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << FrntRghtESC_USBIO_SUSPEND_SHIFT)))
    #define FrntRghtESC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << FrntRghtESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define FrntRghtESC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(FrntRghtESC__PC)
    /* Port Configuration */
    #define FrntRghtESC_PC                 (* (reg32 *) FrntRghtESC__PC)
#endif
/* Pin State */
#define FrntRghtESC_PS                     (* (reg32 *) FrntRghtESC__PS)
/* Data Register */
#define FrntRghtESC_DR                     (* (reg32 *) FrntRghtESC__DR)
/* Input Buffer Disable Override */
#define FrntRghtESC_INP_DIS                (* (reg32 *) FrntRghtESC__PC2)

/* Interrupt configuration Registers */
#define FrntRghtESC_INTCFG                 (* (reg32 *) FrntRghtESC__INTCFG)
#define FrntRghtESC_INTSTAT                (* (reg32 *) FrntRghtESC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define FrntRghtESC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(FrntRghtESC__SIO)
    #define FrntRghtESC_SIO_REG            (* (reg32 *) FrntRghtESC__SIO)
#endif /* (FrntRghtESC__SIO_CFG) */

/* USBIO registers */
#if !defined(FrntRghtESC__PC) && (CY_PSOC4_4200L)
    #define FrntRghtESC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define FrntRghtESC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define FrntRghtESC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define FrntRghtESC_DRIVE_MODE_SHIFT       (0x00u)
#define FrntRghtESC_DRIVE_MODE_MASK        (0x07u << FrntRghtESC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins FrntRghtESC_H */


/* [] END OF FILE */
