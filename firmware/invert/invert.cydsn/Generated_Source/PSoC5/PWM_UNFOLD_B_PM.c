/*******************************************************************************
* File Name: PWM_UNFOLD_B_PM.c
* Version 2.40
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "cytypes.h"
#include "PWM_UNFOLD_B.h"

static PWM_UNFOLD_B_backupStruct PWM_UNFOLD_B_backup;


/*******************************************************************************
* Function Name: PWM_UNFOLD_B_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_UNFOLD_B_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWM_UNFOLD_B_SaveConfig(void) 
{
    
    #if(!PWM_UNFOLD_B_UsingFixedFunction)
        #if (CY_UDB_V0)
            PWM_UNFOLD_B_backup.PWMUdb = PWM_UNFOLD_B_ReadCounter();
            PWM_UNFOLD_B_backup.PWMPeriod = PWM_UNFOLD_B_ReadPeriod();
            #if (PWM_UNFOLD_B_UseStatus)
                PWM_UNFOLD_B_backup.InterruptMaskValue = PWM_UNFOLD_B_STATUS_MASK;
            #endif /* (PWM_UNFOLD_B_UseStatus) */
            
            #if(PWM_UNFOLD_B_UseOneCompareMode)
                PWM_UNFOLD_B_backup.PWMCompareValue = PWM_UNFOLD_B_ReadCompare();
            #else
                PWM_UNFOLD_B_backup.PWMCompareValue1 = PWM_UNFOLD_B_ReadCompare1();
                PWM_UNFOLD_B_backup.PWMCompareValue2 = PWM_UNFOLD_B_ReadCompare2();
            #endif /* (PWM_UNFOLD_B_UseOneCompareMode) */
            
           #if(PWM_UNFOLD_B_DeadBandUsed)
                PWM_UNFOLD_B_backup.PWMdeadBandValue = PWM_UNFOLD_B_ReadDeadTime();
            #endif /* (PWM_UNFOLD_B_DeadBandUsed) */
          
            #if ( PWM_UNFOLD_B_KillModeMinTime)
                PWM_UNFOLD_B_backup.PWMKillCounterPeriod = PWM_UNFOLD_B_ReadKillTime();
            #endif /* ( PWM_UNFOLD_B_KillModeMinTime) */
        #endif /* (CY_UDB_V0) */
        
        #if (CY_UDB_V1)
            #if(!PWM_UNFOLD_B_PWMModeIsCenterAligned)
                PWM_UNFOLD_B_backup.PWMPeriod = PWM_UNFOLD_B_ReadPeriod();
            #endif /* (!PWM_UNFOLD_B_PWMModeIsCenterAligned) */
            PWM_UNFOLD_B_backup.PWMUdb = PWM_UNFOLD_B_ReadCounter();
            #if (PWM_UNFOLD_B_UseStatus)
                PWM_UNFOLD_B_backup.InterruptMaskValue = PWM_UNFOLD_B_STATUS_MASK;
            #endif /* (PWM_UNFOLD_B_UseStatus) */
            
            #if(PWM_UNFOLD_B_DeadBandMode == PWM_UNFOLD_B__B_PWM__DBM_256_CLOCKS || \
                PWM_UNFOLD_B_DeadBandMode == PWM_UNFOLD_B__B_PWM__DBM_2_4_CLOCKS)
                PWM_UNFOLD_B_backup.PWMdeadBandValue = PWM_UNFOLD_B_ReadDeadTime();
            #endif /*  deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWM_UNFOLD_B_KillModeMinTime)
                 PWM_UNFOLD_B_backup.PWMKillCounterPeriod = PWM_UNFOLD_B_ReadKillTime();
            #endif /* (PWM_UNFOLD_B_KillModeMinTime) */
        #endif /* (CY_UDB_V1) */
        
        #if(PWM_UNFOLD_B_UseControl)
            PWM_UNFOLD_B_backup.PWMControlRegister = PWM_UNFOLD_B_ReadControlRegister();
        #endif /* (PWM_UNFOLD_B_UseControl) */
    #endif  /* (!PWM_UNFOLD_B_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_UNFOLD_B_RestoreConfig
********************************************************************************
* 
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_UNFOLD_B_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_UNFOLD_B_RestoreConfig(void) 
{
        #if(!PWM_UNFOLD_B_UsingFixedFunction)
            #if (CY_UDB_V0)
                /* Interrupt State Backup for Critical Region*/
                uint8 PWM_UNFOLD_B_interruptState;
                /* Enter Critical Region*/
                PWM_UNFOLD_B_interruptState = CyEnterCriticalSection();
                #if (PWM_UNFOLD_B_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    PWM_UNFOLD_B_STATUS_AUX_CTRL |= PWM_UNFOLD_B_STATUS_ACTL_INT_EN_MASK;
                    
                    PWM_UNFOLD_B_STATUS_MASK = PWM_UNFOLD_B_backup.InterruptMaskValue;
                #endif /* (PWM_UNFOLD_B_UseStatus) */
                
                #if (PWM_UNFOLD_B_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    PWM_UNFOLD_B_AUX_CONTROLDP0 |= (PWM_UNFOLD_B_AUX_CTRL_FIFO0_CLR);
                #else /* (PWM_UNFOLD_B_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    PWM_UNFOLD_B_AUX_CONTROLDP0 |= (PWM_UNFOLD_B_AUX_CTRL_FIFO0_CLR);
                    PWM_UNFOLD_B_AUX_CONTROLDP1 |= (PWM_UNFOLD_B_AUX_CTRL_FIFO0_CLR);
                #endif /* (PWM_UNFOLD_B_Resolution == 8) */
                /* Exit Critical Region*/
                CyExitCriticalSection(PWM_UNFOLD_B_interruptState);
                
                PWM_UNFOLD_B_WriteCounter(PWM_UNFOLD_B_backup.PWMUdb);
                PWM_UNFOLD_B_WritePeriod(PWM_UNFOLD_B_backup.PWMPeriod);
                
                #if(PWM_UNFOLD_B_UseOneCompareMode)
                    PWM_UNFOLD_B_WriteCompare(PWM_UNFOLD_B_backup.PWMCompareValue);
                #else
                    PWM_UNFOLD_B_WriteCompare1(PWM_UNFOLD_B_backup.PWMCompareValue1);
                    PWM_UNFOLD_B_WriteCompare2(PWM_UNFOLD_B_backup.PWMCompareValue2);
                #endif /* (PWM_UNFOLD_B_UseOneCompareMode) */
                
               #if(PWM_UNFOLD_B_DeadBandMode == PWM_UNFOLD_B__B_PWM__DBM_256_CLOCKS || \
                   PWM_UNFOLD_B_DeadBandMode == PWM_UNFOLD_B__B_PWM__DBM_2_4_CLOCKS)
                    PWM_UNFOLD_B_WriteDeadTime(PWM_UNFOLD_B_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
                #if ( PWM_UNFOLD_B_KillModeMinTime)
                    PWM_UNFOLD_B_WriteKillTime(PWM_UNFOLD_B_backup.PWMKillCounterPeriod);
                #endif /* ( PWM_UNFOLD_B_KillModeMinTime) */
            #endif /* (CY_UDB_V0) */
            
            #if (CY_UDB_V1)
                #if(!PWM_UNFOLD_B_PWMModeIsCenterAligned)
                    PWM_UNFOLD_B_WritePeriod(PWM_UNFOLD_B_backup.PWMPeriod);
                #endif /* (!PWM_UNFOLD_B_PWMModeIsCenterAligned) */
                PWM_UNFOLD_B_WriteCounter(PWM_UNFOLD_B_backup.PWMUdb);
                #if (PWM_UNFOLD_B_UseStatus)
                    PWM_UNFOLD_B_STATUS_MASK = PWM_UNFOLD_B_backup.InterruptMaskValue;
                #endif /* (PWM_UNFOLD_B_UseStatus) */
                
                #if(PWM_UNFOLD_B_DeadBandMode == PWM_UNFOLD_B__B_PWM__DBM_256_CLOCKS || \
                    PWM_UNFOLD_B_DeadBandMode == PWM_UNFOLD_B__B_PWM__DBM_2_4_CLOCKS)
                    PWM_UNFOLD_B_WriteDeadTime(PWM_UNFOLD_B_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
                
                #if(PWM_UNFOLD_B_KillModeMinTime)
                    PWM_UNFOLD_B_WriteKillTime(PWM_UNFOLD_B_backup.PWMKillCounterPeriod);
                #endif /* (PWM_UNFOLD_B_KillModeMinTime) */
            #endif /* (CY_UDB_V1) */
            
            #if(PWM_UNFOLD_B_UseControl)
                PWM_UNFOLD_B_WriteControlRegister(PWM_UNFOLD_B_backup.PWMControlRegister); 
            #endif /* (PWM_UNFOLD_B_UseControl) */
        #endif  /* (!PWM_UNFOLD_B_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_UNFOLD_B_Sleep
********************************************************************************
* 
* Summary:
*  Disables block's operation and saves the user configuration. Should be called 
*  just prior to entering sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_UNFOLD_B_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_UNFOLD_B_Sleep(void) 
{
    #if(PWM_UNFOLD_B_UseControl)
        if(PWM_UNFOLD_B_CTRL_ENABLE == (PWM_UNFOLD_B_CONTROL & PWM_UNFOLD_B_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_UNFOLD_B_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_UNFOLD_B_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_UNFOLD_B_UseControl) */

    /* Stop component */
    PWM_UNFOLD_B_Stop();
    
    /* Save registers configuration */
    PWM_UNFOLD_B_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_UNFOLD_B_Wakeup
********************************************************************************
* 
* Summary:
*  Restores and enables the user configuration. Should be called just after 
*  awaking from sleep.
*  
* Parameters:  
*  None
*
* Return: 
*  None
*
* Global variables:
*  PWM_UNFOLD_B_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_UNFOLD_B_Wakeup(void) 
{
     /* Restore registers values */
    PWM_UNFOLD_B_RestoreConfig();
    
    if(PWM_UNFOLD_B_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_UNFOLD_B_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
