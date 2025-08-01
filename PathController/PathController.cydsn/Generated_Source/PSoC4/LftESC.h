/*******************************************************************************
* File Name: LftESC.h  
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

#if !defined(CY_PINS_LftESC_H) /* Pins LftESC_H */
#define CY_PINS_LftESC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LftESC_aliases.h"


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
} LftESC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   LftESC_Read(void);
void    LftESC_Write(uint8 value);
uint8   LftESC_ReadDataReg(void);
#if defined(LftESC__PC) || (CY_PSOC4_4200L) 
    void    LftESC_SetDriveMode(uint8 mode);
#endif
void    LftESC_SetInterruptMode(uint16 position, uint16 mode);
uint8   LftESC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void LftESC_Sleep(void); 
void LftESC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(LftESC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define LftESC_DRIVE_MODE_BITS        (3)
    #define LftESC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LftESC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the LftESC_SetDriveMode() function.
         *  @{
         */
        #define LftESC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define LftESC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define LftESC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define LftESC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define LftESC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define LftESC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define LftESC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define LftESC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define LftESC_MASK               LftESC__MASK
#define LftESC_SHIFT              LftESC__SHIFT
#define LftESC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LftESC_SetInterruptMode() function.
     *  @{
     */
        #define LftESC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define LftESC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define LftESC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define LftESC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(LftESC__SIO)
    #define LftESC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(LftESC__PC) && (CY_PSOC4_4200L)
    #define LftESC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define LftESC_USBIO_DISABLE              ((uint32)(~LftESC_USBIO_ENABLE))
    #define LftESC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define LftESC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define LftESC_USBIO_ENTER_SLEEP          ((uint32)((1u << LftESC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << LftESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define LftESC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << LftESC_USBIO_SUSPEND_SHIFT)))
    #define LftESC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << LftESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define LftESC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(LftESC__PC)
    /* Port Configuration */
    #define LftESC_PC                 (* (reg32 *) LftESC__PC)
#endif
/* Pin State */
#define LftESC_PS                     (* (reg32 *) LftESC__PS)
/* Data Register */
#define LftESC_DR                     (* (reg32 *) LftESC__DR)
/* Input Buffer Disable Override */
#define LftESC_INP_DIS                (* (reg32 *) LftESC__PC2)

/* Interrupt configuration Registers */
#define LftESC_INTCFG                 (* (reg32 *) LftESC__INTCFG)
#define LftESC_INTSTAT                (* (reg32 *) LftESC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define LftESC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(LftESC__SIO)
    #define LftESC_SIO_REG            (* (reg32 *) LftESC__SIO)
#endif /* (LftESC__SIO_CFG) */

/* USBIO registers */
#if !defined(LftESC__PC) && (CY_PSOC4_4200L)
    #define LftESC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define LftESC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define LftESC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define LftESC_DRIVE_MODE_SHIFT       (0x00u)
#define LftESC_DRIVE_MODE_MASK        (0x07u << LftESC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins LftESC_H */


/* [] END OF FILE */
