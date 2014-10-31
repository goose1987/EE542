/*******************************************************************************
* File Name: PWM_BUCK.h  
* Version 2.40
*
* Description:
*  Contains the prototypes and constants for the functions available to the 
*  PWM user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_PWM_PWM_BUCK_H)
#define CY_PWM_PWM_BUCK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 PWM_BUCK_initVar;


/***************************************
* Conditional Compilation Parameters
***************************************/
#define PWM_BUCK_Resolution 16u
#define PWM_BUCK_UsingFixedFunction 0u
#define PWM_BUCK_DeadBandMode 1u
#define PWM_BUCK_KillModeMinTime 0u
#define PWM_BUCK_KillMode 0u
#define PWM_BUCK_PWMMode 0u
#define PWM_BUCK_PWMModeIsCenterAligned 0u
#define PWM_BUCK_DeadBandUsed 1u
#define PWM_BUCK_DeadBand2_4 1u
#if !defined(PWM_BUCK_PWMUDB_sSTSReg_stsreg__REMOVED)
    #define PWM_BUCK_UseStatus 1u
#else
    #define PWM_BUCK_UseStatus 0u
#endif /* !defined(PWM_BUCK_PWMUDB_sSTSReg_stsreg__REMOVED) */
#if !defined(PWM_BUCK_PWMUDB_sCTRLReg_ctrlreg__REMOVED)
    #define PWM_BUCK_UseControl 1u
#else
    #define PWM_BUCK_UseControl 0u
#endif /* !defined(PWM_BUCK_PWMUDB_sCTRLReg_ctrlreg__REMOVED) */
#define PWM_BUCK_UseOneCompareMode 1u
#define PWM_BUCK_MinimumKillTime 1u
#define PWM_BUCK_EnableMode 0u

#define PWM_BUCK_CompareMode1SW 0u
#define PWM_BUCK_CompareMode2SW 0u

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component PWM_v2_40 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Use Kill Mode Enumerated Types */
#define PWM_BUCK__B_PWM__DISABLED 0
#define PWM_BUCK__B_PWM__ASYNCHRONOUS 1
#define PWM_BUCK__B_PWM__SINGLECYCLE 2
#define PWM_BUCK__B_PWM__LATCHED 3
#define PWM_BUCK__B_PWM__MINTIME 4


/* Use Dead Band Mode Enumerated Types */
#define PWM_BUCK__B_PWM__DBMDISABLED 0
#define PWM_BUCK__B_PWM__DBM_2_4_CLOCKS 1
#define PWM_BUCK__B_PWM__DBM_256_CLOCKS 2


/* Used PWM Mode Enumerated Types */
#define PWM_BUCK__B_PWM__ONE_OUTPUT 0
#define PWM_BUCK__B_PWM__TWO_OUTPUTS 1
#define PWM_BUCK__B_PWM__DUAL_EDGE 2
#define PWM_BUCK__B_PWM__CENTER_ALIGN 3
#define PWM_BUCK__B_PWM__DITHER 5
#define PWM_BUCK__B_PWM__HARDWARESELECT 4


/* Used PWM Compare Mode Enumerated Types */
#define PWM_BUCK__B_PWM__LESS_THAN 1
#define PWM_BUCK__B_PWM__LESS_THAN_OR_EQUAL 2
#define PWM_BUCK__B_PWM__GREATER_THAN 3
#define PWM_BUCK__B_PWM__GREATER_THAN_OR_EQUAL_TO 4
#define PWM_BUCK__B_PWM__EQUAL 0
#define PWM_BUCK__B_PWM__FIRMWARE 5



/***************************************
* Data Struct Definition
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for PWM Component
 *************************************************************************/
typedef struct
{
    
    uint8 PWMEnableState;
       
    #if(!PWM_BUCK_UsingFixedFunction)
        #if (CY_UDB_V0)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            uint16 PWMPeriod;            /* PWM Current Period value   */
            #if (PWM_BUCK_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif /* (PWM_BUCK_UseStatus) */
            #if(PWM_BUCK_UseOneCompareMode)
                uint16 PWMCompareValue;     /* PWM Current Compare value */
            #else
                uint16 PWMCompareValue1;     /* PWM Current Compare value1 */
                uint16 PWMCompareValue2;     /* PWM Current Compare value2 */
            #endif /* (PWM_BUCK_UseOneCompareMode) */
            
            /* Backup for Deadband parameters */
            #if(PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_256_CLOCKS || \
                PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            /* Backup Kill Mode Counter*/
            #if(PWM_BUCK_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif /* (PWM_BUCK_KillModeMinTime) */
            
        #endif /* (CY_UDB_V0) */
        
        #if (CY_UDB_V1)
            uint16 PWMUdb;               /* PWM Current Counter value  */
            #if(!PWM_BUCK_PWMModeIsCenterAligned)
                uint16 PWMPeriod;
            #endif /* (!PWM_BUCK_PWMModeIsCenterAligned) */
            #if (PWM_BUCK_UseStatus)
                uint8 InterruptMaskValue;   /* PWM Current Interrupt Mask */
            #endif /* (PWM_BUCK_UseStatus) */
            
            /* Backup for Deadband parameters */
            #if(PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_256_CLOCKS || \
                PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_2_4_CLOCKS)
                uint8 PWMdeadBandValue; /* Dead Band Counter Current Value */
            #endif /* deadband count is either 2-4 clocks or 256 clocks */
            
            /* Backup Kill Mode Counter*/
            #if(PWM_BUCK_KillModeMinTime)
                uint8 PWMKillCounterPeriod; /* Kill Mode period value */
            #endif /* (PWM_BUCK_KillModeMinTime) */
        #endif /* (CY_UDB_V1) */
        
        /* Backup control register */
        #if(PWM_BUCK_UseControl)
            uint8 PWMControlRegister; /* PWM Control Register value */
        #endif /* (PWM_BUCK_UseControl) */
        
    #endif /* (!PWM_BUCK_UsingFixedFunction) */
   
}PWM_BUCK_backupStruct;


/***************************************
*        Function Prototypes
 **************************************/
 
void    PWM_BUCK_Start(void) ;
void    PWM_BUCK_Stop(void) ;

#if (PWM_BUCK_UseStatus || PWM_BUCK_UsingFixedFunction)
    void  PWM_BUCK_SetInterruptMode(uint8 interruptMode) ;
    uint8 PWM_BUCK_ReadStatusRegister(void) ;
#endif /* (PWM_BUCK_UseStatus || PWM_BUCK_UsingFixedFunction) */

#define PWM_BUCK_GetInterruptSource() PWM_BUCK_ReadStatusRegister()

#if (PWM_BUCK_UseControl)
    uint8 PWM_BUCK_ReadControlRegister(void) ; 
    void  PWM_BUCK_WriteControlRegister(uint8 control) ;
#endif /* (PWM_BUCK_UseControl) */

#if (PWM_BUCK_UseOneCompareMode)
   #if (PWM_BUCK_CompareMode1SW)
       void    PWM_BUCK_SetCompareMode(uint8 comparemode) ;
   #endif /* (PWM_BUCK_CompareMode1SW) */
#else
    #if (PWM_BUCK_CompareMode1SW)
        void    PWM_BUCK_SetCompareMode1(uint8 comparemode) ;
    #endif /* (PWM_BUCK_CompareMode1SW) */
    #if (PWM_BUCK_CompareMode2SW)
        void    PWM_BUCK_SetCompareMode2(uint8 comparemode) ;
    #endif /* (PWM_BUCK_CompareMode2SW) */
#endif /* (PWM_BUCK_UseOneCompareMode) */

#if (!PWM_BUCK_UsingFixedFunction)
    uint16   PWM_BUCK_ReadCounter(void) ;
    uint16 PWM_BUCK_ReadCapture(void) ;
    
	#if (PWM_BUCK_UseStatus)
	        void PWM_BUCK_ClearFIFO(void) ;
	#endif /* (PWM_BUCK_UseStatus) */

    void    PWM_BUCK_WriteCounter(uint16 counter) ;
#endif /* (!PWM_BUCK_UsingFixedFunction) */

void    PWM_BUCK_WritePeriod(uint16 period) ;
uint16 PWM_BUCK_ReadPeriod(void) ;

#if (PWM_BUCK_UseOneCompareMode)
    void    PWM_BUCK_WriteCompare(uint16 compare) ;
    uint16 PWM_BUCK_ReadCompare(void) ; 
#else
    void    PWM_BUCK_WriteCompare1(uint16 compare) ;
    uint16 PWM_BUCK_ReadCompare1(void) ; 
    void    PWM_BUCK_WriteCompare2(uint16 compare) ;
    uint16 PWM_BUCK_ReadCompare2(void) ; 
#endif /* (PWM_BUCK_UseOneCompareMode) */


#if (PWM_BUCK_DeadBandUsed)
    void    PWM_BUCK_WriteDeadTime(uint8 deadtime) ;
    uint8   PWM_BUCK_ReadDeadTime(void) ;
#endif /* (PWM_BUCK_DeadBandUsed) */

#if ( PWM_BUCK_KillModeMinTime)
    void PWM_BUCK_WriteKillTime(uint8 killtime) ;
    uint8 PWM_BUCK_ReadKillTime(void) ; 
#endif /* ( PWM_BUCK_KillModeMinTime) */

void PWM_BUCK_Init(void) ;
void PWM_BUCK_Enable(void) ;
void PWM_BUCK_Sleep(void) ;
void PWM_BUCK_Wakeup(void) ;
void PWM_BUCK_SaveConfig(void) ;
void PWM_BUCK_RestoreConfig(void) ;


/***************************************
*         Initialization Values
**************************************/
#define PWM_BUCK_INIT_PERIOD_VALUE        512u
#define PWM_BUCK_INIT_COMPARE_VALUE1      256u
#define PWM_BUCK_INIT_COMPARE_VALUE2      20000u
#define PWM_BUCK_INIT_INTERRUPTS_MODE     (uint8)(((uint8)(0u << PWM_BUCK_STATUS_TC_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << PWM_BUCK_STATUS_CMP2_INT_EN_MASK_SHIFT)) | \
                                                  (uint8)((uint8)(0u << PWM_BUCK_STATUS_CMP1_INT_EN_MASK_SHIFT )) | \
                                                  (uint8)((uint8)(0u << PWM_BUCK_STATUS_KILL_INT_EN_MASK_SHIFT )))
#define PWM_BUCK_DEFAULT_COMPARE2_MODE    (uint8)((uint8)3u << PWM_BUCK_CTRL_CMPMODE2_SHIFT)
#define PWM_BUCK_DEFAULT_COMPARE1_MODE    (uint8)((uint8)1u << PWM_BUCK_CTRL_CMPMODE1_SHIFT)
#define PWM_BUCK_INIT_DEAD_TIME           3u


/********************************
*         Registers
******************************** */

#if (PWM_BUCK_UsingFixedFunction)
   #define PWM_BUCK_PERIOD_LSB          (*(reg16 *) PWM_BUCK_PWMHW__PER0)
   #define PWM_BUCK_PERIOD_LSB_PTR      ( (reg16 *) PWM_BUCK_PWMHW__PER0)
   #define PWM_BUCK_COMPARE1_LSB        (*(reg16 *) PWM_BUCK_PWMHW__CNT_CMP0)
   #define PWM_BUCK_COMPARE1_LSB_PTR    ( (reg16 *) PWM_BUCK_PWMHW__CNT_CMP0)
   #define PWM_BUCK_COMPARE2_LSB        0x00u
   #define PWM_BUCK_COMPARE2_LSB_PTR    0x00u
   #define PWM_BUCK_COUNTER_LSB         (*(reg16 *) PWM_BUCK_PWMHW__CNT_CMP0)
   #define PWM_BUCK_COUNTER_LSB_PTR     ( (reg16 *) PWM_BUCK_PWMHW__CNT_CMP0)
   #define PWM_BUCK_CAPTURE_LSB         (*(reg16 *) PWM_BUCK_PWMHW__CAP0)
   #define PWM_BUCK_CAPTURE_LSB_PTR     ( (reg16 *) PWM_BUCK_PWMHW__CAP0)
   #define PWM_BUCK_RT1                 (*(reg8 *)  PWM_BUCK_PWMHW__RT1)
   #define PWM_BUCK_RT1_PTR             ( (reg8 *)  PWM_BUCK_PWMHW__RT1)
      
#else
   #if (PWM_BUCK_Resolution == 8u) /* 8bit - PWM */
	   
	   #if(PWM_BUCK_PWMModeIsCenterAligned)
	       #define PWM_BUCK_PERIOD_LSB      (*(reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D1_REG)
	       #define PWM_BUCK_PERIOD_LSB_PTR   ((reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D1_REG)
	   #else
	       #define PWM_BUCK_PERIOD_LSB      (*(reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__F0_REG)
	       #define PWM_BUCK_PERIOD_LSB_PTR   ((reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__F0_REG)
	   #endif /* (PWM_BUCK_PWMModeIsCenterAligned) */
	   
	   #define PWM_BUCK_COMPARE1_LSB    (*(reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D0_REG)
	   #define PWM_BUCK_COMPARE1_LSB_PTR ((reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D0_REG)
	   #define PWM_BUCK_COMPARE2_LSB    (*(reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D1_REG)
	   #define PWM_BUCK_COMPARE2_LSB_PTR ((reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D1_REG)
	   #define PWM_BUCK_COUNTERCAP_LSB   (*(reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__A1_REG)
	   #define PWM_BUCK_COUNTERCAP_LSB_PTR ((reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__A1_REG)
	   #define PWM_BUCK_COUNTER_LSB     (*(reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__A0_REG)
	   #define PWM_BUCK_COUNTER_LSB_PTR  ((reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__A0_REG)
	   #define PWM_BUCK_CAPTURE_LSB     (*(reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__F1_REG)
	   #define PWM_BUCK_CAPTURE_LSB_PTR  ((reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__F1_REG)
   
   #else
   		#if(CY_PSOC3) /* 8-bit address space */	
			#if(PWM_BUCK_PWMModeIsCenterAligned)
		       #define PWM_BUCK_PERIOD_LSB      (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D1_REG)
		       #define PWM_BUCK_PERIOD_LSB_PTR   ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D1_REG)
		    #else
		       #define PWM_BUCK_PERIOD_LSB      (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__F0_REG)
		       #define PWM_BUCK_PERIOD_LSB_PTR   ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__F0_REG)
		    #endif /* (PWM_BUCK_PWMModeIsCenterAligned) */
		   
		    #define PWM_BUCK_COMPARE1_LSB    (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D0_REG)
		    #define PWM_BUCK_COMPARE1_LSB_PTR ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D0_REG)
		    #define PWM_BUCK_COMPARE2_LSB    (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D1_REG)
		    #define PWM_BUCK_COMPARE2_LSB_PTR ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__D1_REG)
		    #define PWM_BUCK_COUNTERCAP_LSB   (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__A1_REG)
		    #define PWM_BUCK_COUNTERCAP_LSB_PTR ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__A1_REG)
		    #define PWM_BUCK_COUNTER_LSB     (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__A0_REG)
		    #define PWM_BUCK_COUNTER_LSB_PTR  ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__A0_REG)
		    #define PWM_BUCK_CAPTURE_LSB     (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__F1_REG)
		    #define PWM_BUCK_CAPTURE_LSB_PTR  ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__F1_REG)
		#else
			#if(PWM_BUCK_PWMModeIsCenterAligned)
		       #define PWM_BUCK_PERIOD_LSB      (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
		       #define PWM_BUCK_PERIOD_LSB_PTR   ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
		    #else
		       #define PWM_BUCK_PERIOD_LSB      (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
		       #define PWM_BUCK_PERIOD_LSB_PTR   ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_F0_REG)
		    #endif /* (PWM_BUCK_PWMModeIsCenterAligned) */
		   
		    #define PWM_BUCK_COMPARE1_LSB    (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
		    #define PWM_BUCK_COMPARE1_LSB_PTR ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_D0_REG)
		    #define PWM_BUCK_COMPARE2_LSB    (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
		    #define PWM_BUCK_COMPARE2_LSB_PTR ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_D1_REG)
		    #define PWM_BUCK_COUNTERCAP_LSB   (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
		    #define PWM_BUCK_COUNTERCAP_LSB_PTR ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_A1_REG)
		    #define PWM_BUCK_COUNTER_LSB     (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
		    #define PWM_BUCK_COUNTER_LSB_PTR  ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_A0_REG)
		    #define PWM_BUCK_CAPTURE_LSB     (*(reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
		    #define PWM_BUCK_CAPTURE_LSB_PTR  ((reg16 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__16BIT_F1_REG)
		#endif
		
	   #define PWM_BUCK_AUX_CONTROLDP1    (*(reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)
       #define PWM_BUCK_AUX_CONTROLDP1_PTR  ((reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u1__DP_AUX_CTL_REG)

   #endif /* (PWM_BUCK_Resolution == 8) */
   
   #define PWM_BUCK_AUX_CONTROLDP0      (*(reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)
   #define PWM_BUCK_AUX_CONTROLDP0_PTR  ((reg8 *) PWM_BUCK_PWMUDB_sP16_pwmdp_u0__DP_AUX_CTL_REG)

#endif /* (PWM_BUCK_UsingFixedFunction) */
   
#if(PWM_BUCK_KillModeMinTime )
    #define PWM_BUCK_KILLMODEMINTIME      (*(reg8 *) PWM_BUCK_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    #define PWM_BUCK_KILLMODEMINTIME_PTR   ((reg8 *) PWM_BUCK_PWMUDB_sKM_killmodecounterdp_u0__D0_REG)
    /* Fixed Function Block has no Kill Mode parameters because it is Asynchronous only */
#endif /* (PWM_BUCK_KillModeMinTime ) */

#if(PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_256_CLOCKS)
    #define PWM_BUCK_DEADBAND_COUNT      (*(reg8 *) PWM_BUCK_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWM_BUCK_DEADBAND_COUNT_PTR  ((reg8 *) PWM_BUCK_PWMUDB_sDB255_deadbandcounterdp_u0__D0_REG)
    #define PWM_BUCK_DEADBAND_LSB_PTR    ((reg8 *) PWM_BUCK_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
    #define PWM_BUCK_DEADBAND_LSB        (*(reg8 *) PWM_BUCK_PWMUDB_sDB255_deadbandcounterdp_u0__A0_REG)
#elif(PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_2_4_CLOCKS)
    /* In Fixed Function Block these bits are in the control blocks control register */
    #if (PWM_BUCK_UsingFixedFunction)
        #define PWM_BUCK_DEADBAND_COUNT        (*(reg8 *) PWM_BUCK_PWMHW__CFG0) 
        #define PWM_BUCK_DEADBAND_COUNT_PTR     ((reg8 *) PWM_BUCK_PWMHW__CFG0)
        #define PWM_BUCK_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWM_BUCK_DEADBAND_COUNT_SHIFT)
        /* As defined by the Register Map as DEADBAND_PERIOD[1:0] in CFG0 */
        #define PWM_BUCK_DEADBAND_COUNT_SHIFT   0x06u  
    #else
        /* Lower two bits of the added control register define the count 1-3 */
        #define PWM_BUCK_DEADBAND_COUNT        (*(reg8 *) PWM_BUCK_PWMUDB_sDB3_AsyncCtl_dbctrlreg__CONTROL_REG)
        #define PWM_BUCK_DEADBAND_COUNT_PTR     ((reg8 *) PWM_BUCK_PWMUDB_sDB3_AsyncCtl_dbctrlreg__CONTROL_REG)
        #define PWM_BUCK_DEADBAND_COUNT_MASK    (uint8)((uint8)0x03u << PWM_BUCK_DEADBAND_COUNT_SHIFT) 
        /* As defined by the verilog implementation of the Control Register */
        #define PWM_BUCK_DEADBAND_COUNT_SHIFT   0x00u 
    #endif /* (PWM_BUCK_UsingFixedFunction) */
#endif /* (PWM_BUCK_DeadBandMode == PWM_BUCK__B_PWM__DBM_256_CLOCKS) */



#if (PWM_BUCK_UsingFixedFunction)
    #define PWM_BUCK_STATUS                (*(reg8 *) PWM_BUCK_PWMHW__SR0)
    #define PWM_BUCK_STATUS_PTR            ((reg8 *) PWM_BUCK_PWMHW__SR0)
    #define PWM_BUCK_STATUS_MASK           (*(reg8 *) PWM_BUCK_PWMHW__SR0)
    #define PWM_BUCK_STATUS_MASK_PTR       ((reg8 *) PWM_BUCK_PWMHW__SR0)
    #define PWM_BUCK_CONTROL               (*(reg8 *) PWM_BUCK_PWMHW__CFG0)
    #define PWM_BUCK_CONTROL_PTR           ((reg8 *) PWM_BUCK_PWMHW__CFG0)    
    #define PWM_BUCK_CONTROL2              (*(reg8 *) PWM_BUCK_PWMHW__CFG1)    
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define PWM_BUCK_CONTROL3              (*(reg8 *) PWM_BUCK_PWMHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define PWM_BUCK_GLOBAL_ENABLE         (*(reg8 *) PWM_BUCK_PWMHW__PM_ACT_CFG)
    #define PWM_BUCK_GLOBAL_ENABLE_PTR       ( (reg8 *) PWM_BUCK_PWMHW__PM_ACT_CFG)
    #define PWM_BUCK_GLOBAL_STBY_ENABLE      (*(reg8 *) PWM_BUCK_PWMHW__PM_STBY_CFG)
    #define PWM_BUCK_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) PWM_BUCK_PWMHW__PM_STBY_CFG)
  
  
    /***********************************
    *          Constants
    ***********************************/

    /* Fixed Function Block Chosen */
    #define PWM_BUCK_BLOCK_EN_MASK          PWM_BUCK_PWMHW__PM_ACT_MSK
    #define PWM_BUCK_BLOCK_STBY_EN_MASK     PWM_BUCK_PWMHW__PM_STBY_MSK 
    /* Control Register definitions */
    #define PWM_BUCK_CTRL_ENABLE_SHIFT      0x00u
    
    #if(CY_PSOC5A)
        #define PWM_BUCK_CTRL_CMPMODE1_SHIFT    0x01u   /* As defined by Register map as MODE_CFG bits in CFG1*/
    #endif /* (CY_PSOC5A) */
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define PWM_BUCK_CTRL_CMPMODE1_SHIFT    0x04u  /* As defined by Register map as MODE_CFG bits in CFG2*/
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    #define PWM_BUCK_CTRL_DEAD_TIME_SHIFT   0x06u   /* As defined by Register map */
    /* Fixed Function Block Only CFG register bit definitions */
    #define PWM_BUCK_CFG0_MODE              0x02u   /*  Set to compare mode */
    /* #define PWM_BUCK_CFG0_ENABLE            0x01u */  /* Enable the block to run */
    #define PWM_BUCK_CFG0_DB                0x20u   /* As defined by Register map as DB bit in CFG0 */

    /* Control Register Bit Masks */
    #define PWM_BUCK_CTRL_ENABLE            (uint8)((uint8)0x01u << PWM_BUCK_CTRL_ENABLE_SHIFT)
    #define PWM_BUCK_CTRL_RESET             (uint8)((uint8)0x01u << PWM_BUCK_CTRL_RESET_SHIFT)
    #define PWM_BUCK_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWM_BUCK_CTRL_CMPMODE2_SHIFT)
    #if(CY_PSOC5A)
        #define PWM_BUCK_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWM_BUCK_CTRL_CMPMODE1_SHIFT)
    #endif /* (CY_PSOC5A) */
    #if(CY_PSOC3 || CY_PSOC5LP)
        #define PWM_BUCK_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWM_BUCK_CTRL_CMPMODE1_SHIFT)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    
    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define PWM_BUCK_CTRL2_IRQ_SEL_SHIFT    0x00u       
    #define PWM_BUCK_CTRL2_IRQ_SEL          (uint8)((uint8)0x01u << PWM_BUCK_CTRL2_IRQ_SEL_SHIFT)  
    
    /* Status Register Bit Locations */
    #define PWM_BUCK_STATUS_TC_SHIFT            0x07u   /* As defined by Register map as TC in SR0 */
    #define PWM_BUCK_STATUS_CMP1_SHIFT          0x06u   /* As defined by the Register map as CAP_CMP in SR0 */
    
    /* Status Register Interrupt Enable Bit Locations */
    #define PWM_BUCK_STATUS_KILL_INT_EN_MASK_SHIFT          (0x00u)    
    #define PWM_BUCK_STATUS_TC_INT_EN_MASK_SHIFT            (PWM_BUCK_STATUS_TC_SHIFT - 4u)
    #define PWM_BUCK_STATUS_CMP2_INT_EN_MASK_SHIFT          (0x00u)  
    #define PWM_BUCK_STATUS_CMP1_INT_EN_MASK_SHIFT          (PWM_BUCK_STATUS_CMP1_SHIFT - 4u)
    
    /* Status Register Bit Masks */
    #define PWM_BUCK_STATUS_TC              (uint8)((uint8)0x01u << PWM_BUCK_STATUS_TC_SHIFT)
    #define PWM_BUCK_STATUS_CMP1            (uint8)((uint8)0x01u << PWM_BUCK_STATUS_CMP1_SHIFT)
    
    /* Status Register Interrupt Bit Masks*/
    #define PWM_BUCK_STATUS_TC_INT_EN_MASK              (uint8)((uint8)PWM_BUCK_STATUS_TC >> 4u)
    #define PWM_BUCK_STATUS_CMP1_INT_EN_MASK            (uint8)((uint8)PWM_BUCK_STATUS_CMP1 >> 4u)
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP*/
    #define PWM_BUCK_RT1_SHIFT             0x04u
    #define PWM_BUCK_RT1_MASK              (uint8)((uint8)0x03u << PWM_BUCK_RT1_SHIFT)/* Sync TC and CMP bit masks */
    #define PWM_BUCK_SYNC                  (uint8)((uint8)0x03u << PWM_BUCK_RT1_SHIFT)
    #define PWM_BUCK_SYNCDSI_SHIFT         0x00u
    #define PWM_BUCK_SYNCDSI_MASK          (uint8)((uint8)0x0Fu << PWM_BUCK_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    #define PWM_BUCK_SYNCDSI_EN            (uint8)((uint8)0x0Fu << PWM_BUCK_SYNCDSI_SHIFT) /* Sync all DSI inputs */
    

#else
    #define PWM_BUCK_STATUS                (*(reg8 *) PWM_BUCK_PWMUDB_sSTSReg_nrstSts_stsreg__STATUS_REG )
    #define PWM_BUCK_STATUS_PTR            ((reg8 *) PWM_BUCK_PWMUDB_sSTSReg_nrstSts_stsreg__STATUS_REG )
    #define PWM_BUCK_STATUS_MASK           (*(reg8 *) PWM_BUCK_PWMUDB_sSTSReg_nrstSts_stsreg__MASK_REG)
    #define PWM_BUCK_STATUS_MASK_PTR       ((reg8 *) PWM_BUCK_PWMUDB_sSTSReg_nrstSts_stsreg__MASK_REG)
    #define PWM_BUCK_STATUS_AUX_CTRL       (*(reg8 *) PWM_BUCK_PWMUDB_sSTSReg_nrstSts_stsreg__STATUS_AUX_CTL_REG)
    #define PWM_BUCK_CONTROL               (*(reg8 *) PWM_BUCK_PWMUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG)
    #define PWM_BUCK_CONTROL_PTR           ((reg8 *) PWM_BUCK_PWMUDB_sCTRLReg_AsyncCtl_ctrlreg__CONTROL_REG)
    
    
    /***********************************
    *          Constants
    ***********************************/

    /* Control Register definitions */
    #define PWM_BUCK_CTRL_ENABLE_SHIFT      0x07u
    #define PWM_BUCK_CTRL_RESET_SHIFT       0x06u
    #define PWM_BUCK_CTRL_CMPMODE2_SHIFT    0x03u
    #define PWM_BUCK_CTRL_CMPMODE1_SHIFT    0x00u
    #define PWM_BUCK_CTRL_DEAD_TIME_SHIFT   0x00u   /* No Shift Needed for UDB block */
    /* Control Register Bit Masks */
    #define PWM_BUCK_CTRL_ENABLE            (uint8)((uint8)0x01u << PWM_BUCK_CTRL_ENABLE_SHIFT)
    #define PWM_BUCK_CTRL_RESET             (uint8)((uint8)0x01u << PWM_BUCK_CTRL_RESET_SHIFT)
    #define PWM_BUCK_CTRL_CMPMODE2_MASK     (uint8)((uint8)0x07u << PWM_BUCK_CTRL_CMPMODE2_SHIFT)
    #define PWM_BUCK_CTRL_CMPMODE1_MASK     (uint8)((uint8)0x07u << PWM_BUCK_CTRL_CMPMODE1_SHIFT) 
    
    /* Status Register Bit Locations */
    #define PWM_BUCK_STATUS_KILL_SHIFT          0x05u
    #define PWM_BUCK_STATUS_FIFONEMPTY_SHIFT    0x04u
    #define PWM_BUCK_STATUS_FIFOFULL_SHIFT      0x03u  
    #define PWM_BUCK_STATUS_TC_SHIFT            0x02u
    #define PWM_BUCK_STATUS_CMP2_SHIFT          0x01u
    #define PWM_BUCK_STATUS_CMP1_SHIFT          0x00u
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define PWM_BUCK_STATUS_KILL_INT_EN_MASK_SHIFT          PWM_BUCK_STATUS_KILL_SHIFT          
    #define PWM_BUCK_STATUS_FIFONEMPTY_INT_EN_MASK_SHIFT    PWM_BUCK_STATUS_FIFONEMPTY_SHIFT    
    #define PWM_BUCK_STATUS_FIFOFULL_INT_EN_MASK_SHIFT      PWM_BUCK_STATUS_FIFOFULL_SHIFT        
    #define PWM_BUCK_STATUS_TC_INT_EN_MASK_SHIFT            PWM_BUCK_STATUS_TC_SHIFT            
    #define PWM_BUCK_STATUS_CMP2_INT_EN_MASK_SHIFT          PWM_BUCK_STATUS_CMP2_SHIFT          
    #define PWM_BUCK_STATUS_CMP1_INT_EN_MASK_SHIFT          PWM_BUCK_STATUS_CMP1_SHIFT   
    /* Status Register Bit Masks */
    #define PWM_BUCK_STATUS_KILL            (uint8)((uint8)0x00u << PWM_BUCK_STATUS_KILL_SHIFT )
    #define PWM_BUCK_STATUS_FIFOFULL        (uint8)((uint8)0x01u << PWM_BUCK_STATUS_FIFOFULL_SHIFT)
    #define PWM_BUCK_STATUS_FIFONEMPTY      (uint8)((uint8)0x01u << PWM_BUCK_STATUS_FIFONEMPTY_SHIFT)
    #define PWM_BUCK_STATUS_TC              (uint8)((uint8)0x01u << PWM_BUCK_STATUS_TC_SHIFT)
    #define PWM_BUCK_STATUS_CMP2            (uint8)((uint8)0x01u << PWM_BUCK_STATUS_CMP2_SHIFT) 
    #define PWM_BUCK_STATUS_CMP1            (uint8)((uint8)0x01u << PWM_BUCK_STATUS_CMP1_SHIFT)
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define PWM_BUCK_STATUS_KILL_INT_EN_MASK            PWM_BUCK_STATUS_KILL
    #define PWM_BUCK_STATUS_FIFOFULL_INT_EN_MASK        PWM_BUCK_STATUS_FIFOFULL
    #define PWM_BUCK_STATUS_FIFONEMPTY_INT_EN_MASK      PWM_BUCK_STATUS_FIFONEMPTY
    #define PWM_BUCK_STATUS_TC_INT_EN_MASK              PWM_BUCK_STATUS_TC
    #define PWM_BUCK_STATUS_CMP2_INT_EN_MASK            PWM_BUCK_STATUS_CMP2
    #define PWM_BUCK_STATUS_CMP1_INT_EN_MASK            PWM_BUCK_STATUS_CMP1
                                                          
    /* Datapath Auxillary Control Register definitions */
    #define PWM_BUCK_AUX_CTRL_FIFO0_CLR     0x01u
    #define PWM_BUCK_AUX_CTRL_FIFO1_CLR     0x02u
    #define PWM_BUCK_AUX_CTRL_FIFO0_LVL     0x04u
    #define PWM_BUCK_AUX_CTRL_FIFO1_LVL     0x08u
    #define PWM_BUCK_STATUS_ACTL_INT_EN_MASK  0x10u /* As defined for the ACTL Register */
#endif /* PWM_BUCK_UsingFixedFunction */

#endif  /* CY_PWM_PWM_BUCK_H */


/* [] END OF FILE */
