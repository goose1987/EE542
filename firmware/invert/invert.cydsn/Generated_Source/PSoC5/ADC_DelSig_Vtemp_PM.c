/*******************************************************************************
* File Name: ADC_DelSig_Vtemp_PM.c  
* Version 2.30
*
* Description:
*  This file provides the power manager source code to the API for the 
*  Delta-Sigma ADC Component.
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "ADC_DelSig_Vtemp.h"

static ADC_DelSig_Vtemp_BACKUP_STRUCT ADC_DelSig_Vtemp_backup = 
{
    ADC_DelSig_Vtemp_DISABLED,
    ADC_DelSig_Vtemp_CFG1_DEC_CR
};


/*******************************************************************************  
* Function Name: ADC_DelSig_Vtemp_SaveConfig
********************************************************************************
*
* Summary:
*  Save the register configuration which are not retention.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
* Global variables:
*  ADC_DelSig_Vtemp_backup:  This global structure variable is used to store 
*  configuration registers which are non retention whenever user wants to go 
*  sleep mode by calling Sleep() API.
*
*******************************************************************************/
void ADC_DelSig_Vtemp_SaveConfig(void) 
{
    ADC_DelSig_Vtemp_backup.deccr = ADC_DelSig_Vtemp_DEC_CR_REG;
}


/*******************************************************************************  
* Function Name: ADC_DelSig_Vtemp_RestoreConfig
********************************************************************************
*
* Summary:
*  Restore the register configurations which are not retention.
* 
* Parameters:
*  void
* 
* Return:
*  void
*
* Global variables:
*  ADC_DelSig_Vtemp_backup:  This global structure variable is used to restore 
*  configuration registers which are non retention whenever user wants to switch 
*  to active power mode by calling Wakeup() API.
*
*******************************************************************************/
void ADC_DelSig_Vtemp_RestoreConfig(void) 
{
    ADC_DelSig_Vtemp_DEC_CR_REG = ADC_DelSig_Vtemp_backup.deccr;
}


/******************************************************************************* 
* Function Name: ADC_DelSig_Vtemp_Sleep
********************************************************************************
*
* Summary:
*  Stops the operation of the block and saves the user configuration. 
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ADC_DelSig_Vtemp_backup:  The structure field 'enableState' is modified 
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_DelSig_Vtemp_Sleep(void) 
{
    /* Save ADC enable state */
    if((ADC_DelSig_Vtemp_ACT_PWR_DEC_EN == (ADC_DelSig_Vtemp_PWRMGR_DEC_REG & ADC_DelSig_Vtemp_ACT_PWR_DEC_EN)) &&
       (ADC_DelSig_Vtemp_ACT_PWR_DSM_EN == (ADC_DelSig_Vtemp_PWRMGR_DSM_REG & ADC_DelSig_Vtemp_ACT_PWR_DSM_EN)))
    {
        /* Component is enabled */
        ADC_DelSig_Vtemp_backup.enableState = ADC_DelSig_Vtemp_ENABLED;
    }
    else
    {
        /* Component is disabled */
        ADC_DelSig_Vtemp_backup.enableState = ADC_DelSig_Vtemp_DISABLED;
    }

    /* Stop the configuration */
    ADC_DelSig_Vtemp_Stop();

    /* Save the user configuration */
    ADC_DelSig_Vtemp_SaveConfig();
}


/******************************************************************************* 
* Function Name: ADC_DelSig_Vtemp_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and enables the power to the block.
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  ADC_DelSig_Vtemp_backup:  The structure field 'enableState' is used to 
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_DelSig_Vtemp_Wakeup(void) 
{
    /* Restore the configuration */
    ADC_DelSig_Vtemp_RestoreConfig();

    /* Enable's the component operation */
    if(ADC_DelSig_Vtemp_backup.enableState == ADC_DelSig_Vtemp_ENABLED)
    {
        ADC_DelSig_Vtemp_Enable();

        /* Start the conversion only if conversion is not triggered by the hardware */
        if(!(ADC_DelSig_Vtemp_DEC_CR_REG & ADC_DelSig_Vtemp_DEC_XSTART_EN))
        {
            ADC_DelSig_Vtemp_StartConvert();
        }

    } /* Do nothing if component was disable before */
}


/* [] END OF FILE */
