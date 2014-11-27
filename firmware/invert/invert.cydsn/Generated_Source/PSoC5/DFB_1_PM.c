/*******************************************************************************
* File Name: DFB_1_PM.c
* Version 1.20
*
* Description:
*  This file contains the setup, control and status commands to support
*  component operations in low power mode.
*
* Note:
*
********************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DFB_1.h"

static DFB_1_BACKUP_STRUCT DFB_1_backup = { 0u };


/*******************************************************************************
* Function Name: DFB_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the user configuration of the DFB non-retention registers. This routine
*  is called by DFB_Sleep() to save the component configuration before entering
*  sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_SaveConfig(void) 
{
    /* */
}


/*******************************************************************************
* Function Name: DFB_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the user configuration of the DFB non-retention registers. This
*  routine is called by DFB_Wakeup() to restore the component configuration when
*  exiting sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_RestoreConfig(void) 
{
    /* */
}


/*******************************************************************************
* Function Name: DFB_1_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep. The
*  DFB_1_Sleep() routine saves the current component state. Then it
*  calls the DFB_Stop() function and calls DFB_1_SaveConfig() to save
*  the hardware configuration. Call the DFB_1_Sleep() function before
*  calling the CyPmSleep() or the CyPmHibernate() function. Refer to the PSoC
*  Creator System Reference Guide for more information about power management
*  functions.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DFB_1_Sleep(void) 
{
    if (0u != (DFB_1_CR_REG & DFB_1_RUN_MASK))
    {
        DFB_1_backup.enableState = 1u;
    }
    else /* The DFB block is disabled */
    {
        DFB_1_backup.enableState = 0u;
    }

    /* Disables the clock to the entire core of the block */
    DFB_1_CR_REG |= DFB_1_CORECLK_DISABLE;

    DFB_1_Pause();
}


/*******************************************************************************
* Function Name: DFB_1_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  DFB_1_Sleep() was called. The DFB_1_Wakeup() function
*  calls the DFB_1_RestoreConfig() function to restore the
*  configuration. If the component was enabled before the
*  DFB_1_Sleep() function was called, the DFB_1_Wakeup()
*  function will also re-enable the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Calling the DFB_1_Wakeup() function without first calling the
*  DFB_1_Sleep() or DFB_1_SaveConfig() function may
*  produce unexpected behavior.
*
*******************************************************************************/
void DFB_1_Wakeup(void) 
{
   DFB_1_RestoreConfig();

    /* Enables the clock to the entire core of the block */
    DFB_1_CR_REG &= (uint8) (~DFB_1_CORECLK_DISABLE);

    if (DFB_1_backup.enableState != 0u)
    {
        /* Enables component's operation */
        DFB_1_Resume();
    } /* Left Run Bit in off state if component's block was disabled before */
    else
    {
        /* Takes DFB RAM off the bus */
        DFB_1_RAM_DIR_REG = DFB_1_RAM_DIR_DFB;
        /* Clears any pending interrupts */
        DFB_1_SR_REG = 0xFFu;
    }
}


/* [] END OF FILE */
