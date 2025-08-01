/*******************************************************************************
* File Name: Ana.h  
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

#if !defined(CY_PINS_Ana_H) /* Pins Ana_H */
#define CY_PINS_Ana_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Ana_aliases.h"


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
} Ana_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Ana_Read(void);
void    Ana_Write(uint8 value);
uint8   Ana_ReadDataReg(void);
#if defined(Ana__PC) || (CY_PSOC4_4200L) 
    void    Ana_SetDriveMode(uint8 mode);
#endif
void    Ana_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ana_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Ana_Sleep(void); 
void Ana_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Ana__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Ana_DRIVE_MODE_BITS        (3)
    #define Ana_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Ana_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Ana_SetDriveMode() function.
         *  @{
         */
        #define Ana_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Ana_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Ana_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Ana_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Ana_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Ana_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Ana_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Ana_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Ana_MASK               Ana__MASK
#define Ana_SHIFT              Ana__SHIFT
#define Ana_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ana_SetInterruptMode() function.
     *  @{
     */
        #define Ana_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Ana_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Ana_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Ana_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Ana__SIO)
    #define Ana_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Ana__PC) && (CY_PSOC4_4200L)
    #define Ana_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Ana_USBIO_DISABLE              ((uint32)(~Ana_USBIO_ENABLE))
    #define Ana_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Ana_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Ana_USBIO_ENTER_SLEEP          ((uint32)((1u << Ana_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Ana_USBIO_SUSPEND_DEL_SHIFT)))
    #define Ana_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Ana_USBIO_SUSPEND_SHIFT)))
    #define Ana_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Ana_USBIO_SUSPEND_DEL_SHIFT)))
    #define Ana_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Ana__PC)
    /* Port Configuration */
    #define Ana_PC                 (* (reg32 *) Ana__PC)
#endif
/* Pin State */
#define Ana_PS                     (* (reg32 *) Ana__PS)
/* Data Register */
#define Ana_DR                     (* (reg32 *) Ana__DR)
/* Input Buffer Disable Override */
#define Ana_INP_DIS                (* (reg32 *) Ana__PC2)

/* Interrupt configuration Registers */
#define Ana_INTCFG                 (* (reg32 *) Ana__INTCFG)
#define Ana_INTSTAT                (* (reg32 *) Ana__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Ana_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Ana__SIO)
    #define Ana_SIO_REG            (* (reg32 *) Ana__SIO)
#endif /* (Ana__SIO_CFG) */

/* USBIO registers */
#if !defined(Ana__PC) && (CY_PSOC4_4200L)
    #define Ana_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Ana_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Ana_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Ana_DRIVE_MODE_SHIFT       (0x00u)
#define Ana_DRIVE_MODE_MASK        (0x07u << Ana_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Ana_H */


/* [] END OF FILE */
