/*******************************************************************************
* File Name: AltINT.h  
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

#if !defined(CY_PINS_AltINT_H) /* Pins AltINT_H */
#define CY_PINS_AltINT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "AltINT_aliases.h"


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
} AltINT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   AltINT_Read(void);
void    AltINT_Write(uint8 value);
uint8   AltINT_ReadDataReg(void);
#if defined(AltINT__PC) || (CY_PSOC4_4200L) 
    void    AltINT_SetDriveMode(uint8 mode);
#endif
void    AltINT_SetInterruptMode(uint16 position, uint16 mode);
uint8   AltINT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void AltINT_Sleep(void); 
void AltINT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(AltINT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define AltINT_DRIVE_MODE_BITS        (3)
    #define AltINT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - AltINT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the AltINT_SetDriveMode() function.
         *  @{
         */
        #define AltINT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define AltINT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define AltINT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define AltINT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define AltINT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define AltINT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define AltINT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define AltINT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define AltINT_MASK               AltINT__MASK
#define AltINT_SHIFT              AltINT__SHIFT
#define AltINT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AltINT_SetInterruptMode() function.
     *  @{
     */
        #define AltINT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define AltINT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define AltINT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define AltINT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(AltINT__SIO)
    #define AltINT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(AltINT__PC) && (CY_PSOC4_4200L)
    #define AltINT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define AltINT_USBIO_DISABLE              ((uint32)(~AltINT_USBIO_ENABLE))
    #define AltINT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define AltINT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define AltINT_USBIO_ENTER_SLEEP          ((uint32)((1u << AltINT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << AltINT_USBIO_SUSPEND_DEL_SHIFT)))
    #define AltINT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << AltINT_USBIO_SUSPEND_SHIFT)))
    #define AltINT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << AltINT_USBIO_SUSPEND_DEL_SHIFT)))
    #define AltINT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(AltINT__PC)
    /* Port Configuration */
    #define AltINT_PC                 (* (reg32 *) AltINT__PC)
#endif
/* Pin State */
#define AltINT_PS                     (* (reg32 *) AltINT__PS)
/* Data Register */
#define AltINT_DR                     (* (reg32 *) AltINT__DR)
/* Input Buffer Disable Override */
#define AltINT_INP_DIS                (* (reg32 *) AltINT__PC2)

/* Interrupt configuration Registers */
#define AltINT_INTCFG                 (* (reg32 *) AltINT__INTCFG)
#define AltINT_INTSTAT                (* (reg32 *) AltINT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define AltINT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(AltINT__SIO)
    #define AltINT_SIO_REG            (* (reg32 *) AltINT__SIO)
#endif /* (AltINT__SIO_CFG) */

/* USBIO registers */
#if !defined(AltINT__PC) && (CY_PSOC4_4200L)
    #define AltINT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define AltINT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define AltINT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define AltINT_DRIVE_MODE_SHIFT       (0x00u)
#define AltINT_DRIVE_MODE_MASK        (0x07u << AltINT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins AltINT_H */


/* [] END OF FILE */
