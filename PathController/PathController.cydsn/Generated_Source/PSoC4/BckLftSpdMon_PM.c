/*******************************************************************************
* File Name: BckLftSpdMon.c  
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
#include "BckLftSpdMon.h"

static BckLftSpdMon_BACKUP_STRUCT  BckLftSpdMon_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BckLftSpdMon_Sleep
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
*  \snippet BckLftSpdMon_SUT.c usage_BckLftSpdMon_Sleep_Wakeup
*******************************************************************************/
void BckLftSpdMon_Sleep(void)
{
    #if defined(BckLftSpdMon__PC)
        BckLftSpdMon_backup.pcState = BckLftSpdMon_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BckLftSpdMon_backup.usbState = BckLftSpdMon_CR1_REG;
            BckLftSpdMon_USB_POWER_REG |= BckLftSpdMon_USBIO_ENTER_SLEEP;
            BckLftSpdMon_CR1_REG &= BckLftSpdMon_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BckLftSpdMon__SIO)
        BckLftSpdMon_backup.sioState = BckLftSpdMon_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BckLftSpdMon_SIO_REG &= (uint32)(~BckLftSpdMon_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BckLftSpdMon_Wakeup
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
*  Refer to BckLftSpdMon_Sleep() for an example usage.
*******************************************************************************/
void BckLftSpdMon_Wakeup(void)
{
    #if defined(BckLftSpdMon__PC)
        BckLftSpdMon_PC = BckLftSpdMon_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BckLftSpdMon_USB_POWER_REG &= BckLftSpdMon_USBIO_EXIT_SLEEP_PH1;
            BckLftSpdMon_CR1_REG = BckLftSpdMon_backup.usbState;
            BckLftSpdMon_USB_POWER_REG &= BckLftSpdMon_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BckLftSpdMon__SIO)
        BckLftSpdMon_SIO_REG = BckLftSpdMon_backup.sioState;
    #endif
}


/* [] END OF FILE */
