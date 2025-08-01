/*******************************************************************************
* File Name: FrntESC.c  
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
#include "FrntESC.h"

static FrntESC_BACKUP_STRUCT  FrntESC_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: FrntESC_Sleep
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
*  \snippet FrntESC_SUT.c usage_FrntESC_Sleep_Wakeup
*******************************************************************************/
void FrntESC_Sleep(void)
{
    #if defined(FrntESC__PC)
        FrntESC_backup.pcState = FrntESC_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            FrntESC_backup.usbState = FrntESC_CR1_REG;
            FrntESC_USB_POWER_REG |= FrntESC_USBIO_ENTER_SLEEP;
            FrntESC_CR1_REG &= FrntESC_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(FrntESC__SIO)
        FrntESC_backup.sioState = FrntESC_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        FrntESC_SIO_REG &= (uint32)(~FrntESC_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: FrntESC_Wakeup
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
*  Refer to FrntESC_Sleep() for an example usage.
*******************************************************************************/
void FrntESC_Wakeup(void)
{
    #if defined(FrntESC__PC)
        FrntESC_PC = FrntESC_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            FrntESC_USB_POWER_REG &= FrntESC_USBIO_EXIT_SLEEP_PH1;
            FrntESC_CR1_REG = FrntESC_backup.usbState;
            FrntESC_USB_POWER_REG &= FrntESC_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(FrntESC__SIO)
        FrntESC_SIO_REG = FrntESC_backup.sioState;
    #endif
}


/* [] END OF FILE */
