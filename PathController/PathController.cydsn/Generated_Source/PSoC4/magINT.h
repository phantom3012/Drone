/*******************************************************************************
* File Name: magINT.h  
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

#if !defined(CY_PINS_magINT_H) /* Pins magINT_H */
#define CY_PINS_magINT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "magINT_aliases.h"


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
} magINT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   magINT_Read(void);
void    magINT_Write(uint8 value);
uint8   magINT_ReadDataReg(void);
#if defined(magINT__PC) || (CY_PSOC4_4200L) 
    void    magINT_SetDriveMode(uint8 mode);
#endif
void    magINT_SetInterruptMode(uint16 position, uint16 mode);
uint8   magINT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void magINT_Sleep(void); 
void magINT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(magINT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define magINT_DRIVE_MODE_BITS        (3)
    #define magINT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - magINT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the magINT_SetDriveMode() function.
         *  @{
         */
        #define magINT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define magINT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define magINT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define magINT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define magINT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define magINT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define magINT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define magINT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define magINT_MASK               magINT__MASK
#define magINT_SHIFT              magINT__SHIFT
#define magINT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in magINT_SetInterruptMode() function.
     *  @{
     */
        #define magINT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define magINT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define magINT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define magINT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(magINT__SIO)
    #define magINT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(magINT__PC) && (CY_PSOC4_4200L)
    #define magINT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define magINT_USBIO_DISABLE              ((uint32)(~magINT_USBIO_ENABLE))
    #define magINT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define magINT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define magINT_USBIO_ENTER_SLEEP          ((uint32)((1u << magINT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << magINT_USBIO_SUSPEND_DEL_SHIFT)))
    #define magINT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << magINT_USBIO_SUSPEND_SHIFT)))
    #define magINT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << magINT_USBIO_SUSPEND_DEL_SHIFT)))
    #define magINT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(magINT__PC)
    /* Port Configuration */
    #define magINT_PC                 (* (reg32 *) magINT__PC)
#endif
/* Pin State */
#define magINT_PS                     (* (reg32 *) magINT__PS)
/* Data Register */
#define magINT_DR                     (* (reg32 *) magINT__DR)
/* Input Buffer Disable Override */
#define magINT_INP_DIS                (* (reg32 *) magINT__PC2)

/* Interrupt configuration Registers */
#define magINT_INTCFG                 (* (reg32 *) magINT__INTCFG)
#define magINT_INTSTAT                (* (reg32 *) magINT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define magINT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(magINT__SIO)
    #define magINT_SIO_REG            (* (reg32 *) magINT__SIO)
#endif /* (magINT__SIO_CFG) */

/* USBIO registers */
#if !defined(magINT__PC) && (CY_PSOC4_4200L)
    #define magINT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define magINT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define magINT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define magINT_DRIVE_MODE_SHIFT       (0x00u)
#define magINT_DRIVE_MODE_MASK        (0x07u << magINT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins magINT_H */


/* [] END OF FILE */
