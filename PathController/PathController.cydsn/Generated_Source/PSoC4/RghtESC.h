/*******************************************************************************
* File Name: RghtESC.h  
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

#if !defined(CY_PINS_RghtESC_H) /* Pins RghtESC_H */
#define CY_PINS_RghtESC_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RghtESC_aliases.h"


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
} RghtESC_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   RghtESC_Read(void);
void    RghtESC_Write(uint8 value);
uint8   RghtESC_ReadDataReg(void);
#if defined(RghtESC__PC) || (CY_PSOC4_4200L) 
    void    RghtESC_SetDriveMode(uint8 mode);
#endif
void    RghtESC_SetInterruptMode(uint16 position, uint16 mode);
uint8   RghtESC_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void RghtESC_Sleep(void); 
void RghtESC_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(RghtESC__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define RghtESC_DRIVE_MODE_BITS        (3)
    #define RghtESC_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RghtESC_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the RghtESC_SetDriveMode() function.
         *  @{
         */
        #define RghtESC_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define RghtESC_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define RghtESC_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define RghtESC_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define RghtESC_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define RghtESC_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define RghtESC_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define RghtESC_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define RghtESC_MASK               RghtESC__MASK
#define RghtESC_SHIFT              RghtESC__SHIFT
#define RghtESC_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RghtESC_SetInterruptMode() function.
     *  @{
     */
        #define RghtESC_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define RghtESC_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define RghtESC_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define RghtESC_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(RghtESC__SIO)
    #define RghtESC_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(RghtESC__PC) && (CY_PSOC4_4200L)
    #define RghtESC_USBIO_ENABLE               ((uint32)0x80000000u)
    #define RghtESC_USBIO_DISABLE              ((uint32)(~RghtESC_USBIO_ENABLE))
    #define RghtESC_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define RghtESC_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define RghtESC_USBIO_ENTER_SLEEP          ((uint32)((1u << RghtESC_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << RghtESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define RghtESC_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << RghtESC_USBIO_SUSPEND_SHIFT)))
    #define RghtESC_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << RghtESC_USBIO_SUSPEND_DEL_SHIFT)))
    #define RghtESC_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(RghtESC__PC)
    /* Port Configuration */
    #define RghtESC_PC                 (* (reg32 *) RghtESC__PC)
#endif
/* Pin State */
#define RghtESC_PS                     (* (reg32 *) RghtESC__PS)
/* Data Register */
#define RghtESC_DR                     (* (reg32 *) RghtESC__DR)
/* Input Buffer Disable Override */
#define RghtESC_INP_DIS                (* (reg32 *) RghtESC__PC2)

/* Interrupt configuration Registers */
#define RghtESC_INTCFG                 (* (reg32 *) RghtESC__INTCFG)
#define RghtESC_INTSTAT                (* (reg32 *) RghtESC__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define RghtESC_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(RghtESC__SIO)
    #define RghtESC_SIO_REG            (* (reg32 *) RghtESC__SIO)
#endif /* (RghtESC__SIO_CFG) */

/* USBIO registers */
#if !defined(RghtESC__PC) && (CY_PSOC4_4200L)
    #define RghtESC_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define RghtESC_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define RghtESC_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define RghtESC_DRIVE_MODE_SHIFT       (0x00u)
#define RghtESC_DRIVE_MODE_MASK        (0x07u << RghtESC_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins RghtESC_H */


/* [] END OF FILE */
