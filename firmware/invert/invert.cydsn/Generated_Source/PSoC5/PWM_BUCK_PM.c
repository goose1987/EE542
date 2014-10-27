/*******************************************************************************
* File Name: PWM_BUCK_PM.c
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
#include "PWM_BUCK.h"

static PWM_BUCK_backupStruct PWM_BUCK_backup;


/*******************************************************************************
* Function Name: PWM_BUCK_SaveConfig
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
*  PWM_BUCK_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void PWM_BUCK_SaveConfig(void) 
{
    
    #if(!PWM_BUCK_UsingFixedFunction)
        #if (CY_UDB_V0)
            PWM_BUCK_backup.PWMUdb = PWM_BUCK_ReadCounter();
            PWM_BUCK_backup.PWMPeriod = PWM_BUCK_ReadPeriod();
            #if (PWM_BUCK_UseStatus)
                PWM_BUCK_backup.InterruptMaskValue = PWM_BUCK_STATUS_MASK;
            #endif /* (PWM_BUCK_UseStatus) */
            
            #if(PWM_BUCK_UseOneCompareMode)
                PWM_BUCK_backup.PWMCompareValue = PWM_BUCK_ReadCompare();
            #else
                PWM_BUCK_backup.PWMCompareValue1 = PWM_BUCK_ReadCompare1();
                PWM_BUCK_backup.PWMCompareValue2 = PWM_BUCK_ReadCompare2();
            #endif /* (PWM_BUCK_UseOneCompareMode) */
            
           #if(PWM_BUCK_DeadBandUsed)
                PWM_BUCK_backup.PWMdeadBandValue = PWM_BUCK_ReadDeadTime();
            #endif /* (PWM_BUCK_DeadBandUsed) */
          
            #if ( PWM_BUCK_KillModeMinTime)
                PWM_BUCK_backup.PWMKillCounterPeriod = PWM_BUCK_ReadKillTime();
            #endif /* ( PWM_BUCK_KillModeMinTime) */
        #endif /* (CY_UDB_V0) */
        
        #if (CY_UDB_V1)
            #if(!PWM_BUCK_PWMModeIsCenterAligned)
                PWM_BUCK_backup.PWMPeriod = PWM_BUCK_ReadPeriod();
            #endif /* (!PWM_BUCK_PWMModeIsCenterAligned) */
            PWM_BUCK_backup.PWMUdb = PWM_BUCK_ReadCounter();
            #if (PWM_BUCK_UseStatus)
                PWM_BUCK_backup.InterruptMaskValue = PWM_BUCK_STATUS_MASK;
            #endif /* (PWM_BUCK_UseStatus) */
            
            #if(PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_256_CLOCKS || \
                PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_2_4_CLOCKS)
                PWM_BUCK_backup.PWMdeadBandValue = PWM_BUCK_ReadDeadTime();
            #endif /*  deadband count is either 2-4 clocks or 256 clocks */
            
            #if(PWM_BUCK_KillModeMinTime)
                 PWM_BUCK_backup.PWMKillCounterPeriod = PWM_BUCK_ReadKillTime();
            #endif /* (PWM_BUCK_KillModeMinTime) */
        #endif /* (CY_UDB_V1) */
        
        #if(PWM_BUCK_UseControl)
            PWM_BUCK_backup.PWMControlRegister = PWM_BUCK_ReadControlRegister();
        #endif /* (PWM_BUCK_UseControl) */
    #endif  /* (!PWM_BUCK_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_BUCK_RestoreConfig
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
*  PWM_BUCK_backup:  Variables of this global structure are used to  
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_BUCK_RestoreConfig(void) 
{
        #if(!PWM_BUCK_UsingFixedFunction)
            #if (CY_UDB_V0)
                /* Interrupt State Backup for Critical Region*/
                uint8 PWM_BUCK_interruptState;
                /* Enter Critical Region*/
                PWM_BUCK_interruptState = CyEnterCriticalSection();
                #if (PWM_BUCK_UseStatus)
                    /* Use the interrupt output of the status register for IRQ output */
                    PWM_BUCK_STATUS_AUX_CTRL |= PWM_BUCK_STATUS_ACTL_INT_EN_MASK;
                    
                    PWM_BUCK_STATUS_MASK = PWM_BUCK_backup.InterruptMaskValue;
                #endif /* (PWM_BUCK_UseStatus) */
                
                #if (PWM_BUCK_Resolution == 8)
                    /* Set FIFO 0 to 1 byte register for period*/
                    PWM_BUCK_AUX_CONTROLDP0 |= (PWM_BUCK_AUX_CTRL_FIFO0_CLR);
                #else /* (PWM_BUCK_Resolution == 16)*/
                    /* Set FIFO 0 to 1 byte register for period */
                    PWM_BUCK_AUX_CONTROLDP0 |= (PWM_BUCK_AUX_CTRL_FIFO0_CLR);
                    PWM_BUCK_AUX_CONTROLDP1 |= (PWM_BUCK_AUX_CTRL_FIFO0_CLR);
                #endif /* (PWM_BUCK_Resolution == 8) */
                /* Exit Critical Region*/
                CyExitCriticalSection(PWM_BUCK_interruptState);
                
                PWM_BUCK_WriteCounter(PWM_BUCK_backup.PWMUdb);
                PWM_BUCK_WritePeriod(PWM_BUCK_backup.PWMPeriod);
                
                #if(PWM_BUCK_UseOneCompareMode)
                    PWM_BUCK_WriteCompare(PWM_BUCK_backup.PWMCompareValue);
                #else
                    PWM_BUCK_WriteCompare1(PWM_BUCK_backup.PWMCompareValue1);
                    PWM_BUCK_WriteCompare2(PWM_BUCK_backup.PWMCompareValue2);
                #endif /* (PWM_BUCK_UseOneCompareMode) */
                
               #if(PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_256_CLOCKS || \
                   PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_2_4_CLOCKS)
                    PWM_BUCK_WriteDeadTime(PWM_BUCK_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
                #if ( PWM_BUCK_KillModeMinTime)
                    PWM_BUCK_WriteKillTime(PWM_BUCK_backup.PWMKillCounterPeriod);
                #endif /* ( PWM_BUCK_KillModeMinTime) */
            #endif /* (CY_UDB_V0) */
            
            #if (CY_UDB_V1)
                #if(!PWM_BUCK_PWMModeIsCenterAligned)
                    PWM_BUCK_WritePeriod(PWM_BUCK_backup.PWMPeriod);
                #endif /* (!PWM_BUCK_PWMModeIsCenterAligned) */
                PWM_BUCK_WriteCounter(PWM_BUCK_backup.PWMUdb);
                #if (PWM_BUCK_UseStatus)
                    PWM_BUCK_STATUS_MASK = PWM_BUCK_backup.InterruptMaskValue;
                #endif /* (PWM_BUCK_UseStatus) */
                
                #if(PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_256_CLOCKS || \
                    PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_2_4_CLOCKS)
                    PWM_BUCK_WriteDeadTime(PWM_BUCK_backup.PWMdeadBandValue);
                #endif /* deadband count is either 2-4 clocks or 256 clocks */
                
                #if(PWM_BUCK_KillModeMinTime)
                    PWM_BUCK_WriteKillTime(PWM_BUCK_backup.PWMKillCounterPeriod);
                #endif /* (PWM_BUCK_KillModeMinTime) */
            #endif /* (CY_UDB_V1) */
            
            #if(PWM_BUCK_UseControl)
                PWM_BUCK_WriteControlRegister(PWM_BUCK_backup.PWMControlRegister); 
            #endif /* (PWM_BUCK_UseControl) */
        #endif  /* (!PWM_BUCK_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_BUCK_Sleep
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
*  PWM_BUCK_backup.PWMEnableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_BUCK_Sleep(void) 
{
    #if(PWM_BUCK_UseControl)
        if(PWM_BUCK_CTRL_ENABLE == (PWM_BUCK_CONTROL & PWM_BUCK_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_BUCK_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_BUCK_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_BUCK_UseControl) */

    /* Stop component */
    PWM_BUCK_Stop();
    
    /* Save registers configuration */
    PWM_BUCK_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_BUCK_Wakeup
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
*  PWM_BUCK_backup.pwmEnable:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_BUCK_Wakeup(void) 
{
     /* Restore registers values */
    PWM_BUCK_RestoreConfig();
    
    if(PWM_BUCK_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_BUCK_Enable();
    } /* Do nothing if component's block was disabled before */
    
}


/* [] END OF FILE */
