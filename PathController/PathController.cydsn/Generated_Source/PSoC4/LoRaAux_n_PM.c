/*******************************************************************************
* File Name: LoRaAux_n.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "LoRaAux_n.h"

static LoRaAux_n_BACKUP_STRUCT  LoRaAux_n_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: LoRaAux_n_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet LoRaAux_n_SUT.c usage_LoRaAux_n_Sleep_Wakeup
*******************************************************************************/
void LoRaAux_n_Sleep(void)
{
    #if defined(LoRaAux_n__PC)
        LoRaAux_n_backup.pcState = LoRaAux_n_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            LoRaAux_n_backup.usbState = LoRaAux_n_CR1_REG;
            LoRaAux_n_USB_POWER_REG |= LoRaAux_n_USBIO_ENTER_SLEEP;
            LoRaAux_n_CR1_REG &= LoRaAux_n_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LoRaAux_n__SIO)
        LoRaAux_n_backup.sioState = LoRaAux_n_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        LoRaAux_n_SIO_REG &= (uint32)(~LoRaAux_n_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: LoRaAux_n_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to LoRaAux_n_Sleep() for an example usage.
*******************************************************************************/
void LoRaAux_n_Wakeup(void)
{
    #if defined(LoRaAux_n__PC)
        LoRaAux_n_PC = LoRaAux_n_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            LoRaAux_n_USB_POWER_REG &= LoRaAux_n_USBIO_EXIT_SLEEP_PH1;
            LoRaAux_n_CR1_REG = LoRaAux_n_backup.usbState;
            LoRaAux_n_USB_POWER_REG &= LoRaAux_n_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(LoRaAux_n__SIO)
        LoRaAux_n_SIO_REG = LoRaAux_n_backup.sioState;
    #endif
}


/* [] END OF FILE */
