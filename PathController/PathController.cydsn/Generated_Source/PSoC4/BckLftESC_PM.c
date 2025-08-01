/*******************************************************************************
* File Name: BckLftESC.c  
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
#include "BckLftESC.h"

static BckLftESC_BACKUP_STRUCT  BckLftESC_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: BckLftESC_Sleep
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
*  \snippet BckLftESC_SUT.c usage_BckLftESC_Sleep_Wakeup
*******************************************************************************/
void BckLftESC_Sleep(void)
{
    #if defined(BckLftESC__PC)
        BckLftESC_backup.pcState = BckLftESC_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            BckLftESC_backup.usbState = BckLftESC_CR1_REG;
            BckLftESC_USB_POWER_REG |= BckLftESC_USBIO_ENTER_SLEEP;
            BckLftESC_CR1_REG &= BckLftESC_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BckLftESC__SIO)
        BckLftESC_backup.sioState = BckLftESC_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        BckLftESC_SIO_REG &= (uint32)(~BckLftESC_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: BckLftESC_Wakeup
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
*  Refer to BckLftESC_Sleep() for an example usage.
*******************************************************************************/
void BckLftESC_Wakeup(void)
{
    #if defined(BckLftESC__PC)
        BckLftESC_PC = BckLftESC_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            BckLftESC_USB_POWER_REG &= BckLftESC_USBIO_EXIT_SLEEP_PH1;
            BckLftESC_CR1_REG = BckLftESC_backup.usbState;
            BckLftESC_USB_POWER_REG &= BckLftESC_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(BckLftESC__SIO)
        BckLftESC_SIO_REG = BckLftESC_backup.sioState;
    #endif
}


/* [] END OF FILE */
