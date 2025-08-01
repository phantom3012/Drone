/*******************************************************************************
* File Name: MaxLidar.h  
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

#if !defined(CY_PINS_MaxLidar_H) /* Pins MaxLidar_H */
#define CY_PINS_MaxLidar_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MaxLidar_aliases.h"


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
} MaxLidar_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MaxLidar_Read(void);
void    MaxLidar_Write(uint8 value);
uint8   MaxLidar_ReadDataReg(void);
#if defined(MaxLidar__PC) || (CY_PSOC4_4200L) 
    void    MaxLidar_SetDriveMode(uint8 mode);
#endif
void    MaxLidar_SetInterruptMode(uint16 position, uint16 mode);
uint8   MaxLidar_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MaxLidar_Sleep(void); 
void MaxLidar_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MaxLidar__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MaxLidar_DRIVE_MODE_BITS        (3)
    #define MaxLidar_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MaxLidar_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MaxLidar_SetDriveMode() function.
         *  @{
         */
        #define MaxLidar_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MaxLidar_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MaxLidar_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MaxLidar_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MaxLidar_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MaxLidar_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MaxLidar_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MaxLidar_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MaxLidar_MASK               MaxLidar__MASK
#define MaxLidar_SHIFT              MaxLidar__SHIFT
#define MaxLidar_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MaxLidar_SetInterruptMode() function.
     *  @{
     */
        #define MaxLidar_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MaxLidar_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MaxLidar_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MaxLidar_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MaxLidar__SIO)
    #define MaxLidar_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MaxLidar__PC) && (CY_PSOC4_4200L)
    #define MaxLidar_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MaxLidar_USBIO_DISABLE              ((uint32)(~MaxLidar_USBIO_ENABLE))
    #define MaxLidar_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MaxLidar_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MaxLidar_USBIO_ENTER_SLEEP          ((uint32)((1u << MaxLidar_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MaxLidar_USBIO_SUSPEND_DEL_SHIFT)))
    #define MaxLidar_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MaxLidar_USBIO_SUSPEND_SHIFT)))
    #define MaxLidar_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MaxLidar_USBIO_SUSPEND_DEL_SHIFT)))
    #define MaxLidar_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MaxLidar__PC)
    /* Port Configuration */
    #define MaxLidar_PC                 (* (reg32 *) MaxLidar__PC)
#endif
/* Pin State */
#define MaxLidar_PS                     (* (reg32 *) MaxLidar__PS)
/* Data Register */
#define MaxLidar_DR                     (* (reg32 *) MaxLidar__DR)
/* Input Buffer Disable Override */
#define MaxLidar_INP_DIS                (* (reg32 *) MaxLidar__PC2)

/* Interrupt configuration Registers */
#define MaxLidar_INTCFG                 (* (reg32 *) MaxLidar__INTCFG)
#define MaxLidar_INTSTAT                (* (reg32 *) MaxLidar__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MaxLidar_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MaxLidar__SIO)
    #define MaxLidar_SIO_REG            (* (reg32 *) MaxLidar__SIO)
#endif /* (MaxLidar__SIO_CFG) */

/* USBIO registers */
#if !defined(MaxLidar__PC) && (CY_PSOC4_4200L)
    #define MaxLidar_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MaxLidar_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MaxLidar_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MaxLidar_DRIVE_MODE_SHIFT       (0x00u)
#define MaxLidar_DRIVE_MODE_MASK        (0x07u << MaxLidar_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MaxLidar_H */


/* [] END OF FILE */
