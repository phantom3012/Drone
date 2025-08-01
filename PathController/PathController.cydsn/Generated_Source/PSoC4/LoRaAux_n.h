/*******************************************************************************
* File Name: LoRaAux_n.h  
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

#if !defined(CY_PINS_LoRaAux_n_H) /* Pins LoRaAux_n_H */
#define CY_PINS_LoRaAux_n_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LoRaAux_n_aliases.h"


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
} LoRaAux_n_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   LoRaAux_n_Read(void);
void    LoRaAux_n_Write(uint8 value);
uint8   LoRaAux_n_ReadDataReg(void);
#if defined(LoRaAux_n__PC) || (CY_PSOC4_4200L) 
    void    LoRaAux_n_SetDriveMode(uint8 mode);
#endif
void    LoRaAux_n_SetInterruptMode(uint16 position, uint16 mode);
uint8   LoRaAux_n_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void LoRaAux_n_Sleep(void); 
void LoRaAux_n_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(LoRaAux_n__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define LoRaAux_n_DRIVE_MODE_BITS        (3)
    #define LoRaAux_n_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LoRaAux_n_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the LoRaAux_n_SetDriveMode() function.
         *  @{
         */
        #define LoRaAux_n_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define LoRaAux_n_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define LoRaAux_n_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define LoRaAux_n_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define LoRaAux_n_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define LoRaAux_n_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define LoRaAux_n_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define LoRaAux_n_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define LoRaAux_n_MASK               LoRaAux_n__MASK
#define LoRaAux_n_SHIFT              LoRaAux_n__SHIFT
#define LoRaAux_n_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in LoRaAux_n_SetInterruptMode() function.
     *  @{
     */
        #define LoRaAux_n_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define LoRaAux_n_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define LoRaAux_n_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define LoRaAux_n_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(LoRaAux_n__SIO)
    #define LoRaAux_n_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(LoRaAux_n__PC) && (CY_PSOC4_4200L)
    #define LoRaAux_n_USBIO_ENABLE               ((uint32)0x80000000u)
    #define LoRaAux_n_USBIO_DISABLE              ((uint32)(~LoRaAux_n_USBIO_ENABLE))
    #define LoRaAux_n_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define LoRaAux_n_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define LoRaAux_n_USBIO_ENTER_SLEEP          ((uint32)((1u << LoRaAux_n_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << LoRaAux_n_USBIO_SUSPEND_DEL_SHIFT)))
    #define LoRaAux_n_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << LoRaAux_n_USBIO_SUSPEND_SHIFT)))
    #define LoRaAux_n_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << LoRaAux_n_USBIO_SUSPEND_DEL_SHIFT)))
    #define LoRaAux_n_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(LoRaAux_n__PC)
    /* Port Configuration */
    #define LoRaAux_n_PC                 (* (reg32 *) LoRaAux_n__PC)
#endif
/* Pin State */
#define LoRaAux_n_PS                     (* (reg32 *) LoRaAux_n__PS)
/* Data Register */
#define LoRaAux_n_DR                     (* (reg32 *) LoRaAux_n__DR)
/* Input Buffer Disable Override */
#define LoRaAux_n_INP_DIS                (* (reg32 *) LoRaAux_n__PC2)

/* Interrupt configuration Registers */
#define LoRaAux_n_INTCFG                 (* (reg32 *) LoRaAux_n__INTCFG)
#define LoRaAux_n_INTSTAT                (* (reg32 *) LoRaAux_n__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define LoRaAux_n_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(LoRaAux_n__SIO)
    #define LoRaAux_n_SIO_REG            (* (reg32 *) LoRaAux_n__SIO)
#endif /* (LoRaAux_n__SIO_CFG) */

/* USBIO registers */
#if !defined(LoRaAux_n__PC) && (CY_PSOC4_4200L)
    #define LoRaAux_n_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define LoRaAux_n_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define LoRaAux_n_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define LoRaAux_n_DRIVE_MODE_SHIFT       (0x00u)
#define LoRaAux_n_DRIVE_MODE_MASK        (0x07u << LoRaAux_n_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins LoRaAux_n_H */


/* [] END OF FILE */
