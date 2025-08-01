/*******************************************************************************
* File Name: InitHeading.h  
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

#if !defined(CY_PINS_InitHeading_H) /* Pins InitHeading_H */
#define CY_PINS_InitHeading_H

#include "cytypes.h"
#include "cyfitter.h"
#include "InitHeading_aliases.h"


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
} InitHeading_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   InitHeading_Read(void);
void    InitHeading_Write(uint8 value);
uint8   InitHeading_ReadDataReg(void);
#if defined(InitHeading__PC) || (CY_PSOC4_4200L) 
    void    InitHeading_SetDriveMode(uint8 mode);
#endif
void    InitHeading_SetInterruptMode(uint16 position, uint16 mode);
uint8   InitHeading_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void InitHeading_Sleep(void); 
void InitHeading_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(InitHeading__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define InitHeading_DRIVE_MODE_BITS        (3)
    #define InitHeading_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - InitHeading_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the InitHeading_SetDriveMode() function.
         *  @{
         */
        #define InitHeading_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define InitHeading_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define InitHeading_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define InitHeading_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define InitHeading_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define InitHeading_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define InitHeading_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define InitHeading_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define InitHeading_MASK               InitHeading__MASK
#define InitHeading_SHIFT              InitHeading__SHIFT
#define InitHeading_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in InitHeading_SetInterruptMode() function.
     *  @{
     */
        #define InitHeading_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define InitHeading_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define InitHeading_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define InitHeading_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(InitHeading__SIO)
    #define InitHeading_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(InitHeading__PC) && (CY_PSOC4_4200L)
    #define InitHeading_USBIO_ENABLE               ((uint32)0x80000000u)
    #define InitHeading_USBIO_DISABLE              ((uint32)(~InitHeading_USBIO_ENABLE))
    #define InitHeading_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define InitHeading_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define InitHeading_USBIO_ENTER_SLEEP          ((uint32)((1u << InitHeading_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << InitHeading_USBIO_SUSPEND_DEL_SHIFT)))
    #define InitHeading_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << InitHeading_USBIO_SUSPEND_SHIFT)))
    #define InitHeading_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << InitHeading_USBIO_SUSPEND_DEL_SHIFT)))
    #define InitHeading_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(InitHeading__PC)
    /* Port Configuration */
    #define InitHeading_PC                 (* (reg32 *) InitHeading__PC)
#endif
/* Pin State */
#define InitHeading_PS                     (* (reg32 *) InitHeading__PS)
/* Data Register */
#define InitHeading_DR                     (* (reg32 *) InitHeading__DR)
/* Input Buffer Disable Override */
#define InitHeading_INP_DIS                (* (reg32 *) InitHeading__PC2)

/* Interrupt configuration Registers */
#define InitHeading_INTCFG                 (* (reg32 *) InitHeading__INTCFG)
#define InitHeading_INTSTAT                (* (reg32 *) InitHeading__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define InitHeading_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(InitHeading__SIO)
    #define InitHeading_SIO_REG            (* (reg32 *) InitHeading__SIO)
#endif /* (InitHeading__SIO_CFG) */

/* USBIO registers */
#if !defined(InitHeading__PC) && (CY_PSOC4_4200L)
    #define InitHeading_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define InitHeading_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define InitHeading_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define InitHeading_DRIVE_MODE_SHIFT       (0x00u)
#define InitHeading_DRIVE_MODE_MASK        (0x07u << InitHeading_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins InitHeading_H */


/* [] END OF FILE */
