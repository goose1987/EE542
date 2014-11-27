/*******************************************************************************
* File Name: Clock_UNFOLDER.h
* Version 2.0
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clock_UNFOLDER_H)
#define CY_CLOCK_Clock_UNFOLDER_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Clock_UNFOLDER_Start(void) ;
void Clock_UNFOLDER_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Clock_UNFOLDER_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Clock_UNFOLDER_StandbyPower(uint8 state) ;
void Clock_UNFOLDER_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Clock_UNFOLDER_GetDividerRegister(void) ;
void Clock_UNFOLDER_SetModeRegister(uint8 modeBitMask) ;
void Clock_UNFOLDER_ClearModeRegister(uint8 modeBitMask) ;
uint8 Clock_UNFOLDER_GetModeRegister(void) ;
void Clock_UNFOLDER_SetSourceRegister(uint8 clkSource) ;
uint8 Clock_UNFOLDER_GetSourceRegister(void) ;
#if defined(Clock_UNFOLDER__CFG3)
void Clock_UNFOLDER_SetPhaseRegister(uint8 clkPhase) ;
uint8 Clock_UNFOLDER_GetPhaseRegister(void) ;
#endif /* defined(Clock_UNFOLDER__CFG3) */

#define Clock_UNFOLDER_Enable()                       Clock_UNFOLDER_Start()
#define Clock_UNFOLDER_Disable()                      Clock_UNFOLDER_Stop()
#define Clock_UNFOLDER_SetDivider(clkDivider)         Clock_UNFOLDER_SetDividerRegister(clkDivider, 1)
#define Clock_UNFOLDER_SetDividerValue(clkDivider)    Clock_UNFOLDER_SetDividerRegister((clkDivider) - 1, 1)
#define Clock_UNFOLDER_SetMode(clkMode)               Clock_UNFOLDER_SetModeRegister(clkMode)
#define Clock_UNFOLDER_SetSource(clkSource)           Clock_UNFOLDER_SetSourceRegister(clkSource)
#if defined(Clock_UNFOLDER__CFG3)
#define Clock_UNFOLDER_SetPhase(clkPhase)             Clock_UNFOLDER_SetPhaseRegister(clkPhase)
#define Clock_UNFOLDER_SetPhaseValue(clkPhase)        Clock_UNFOLDER_SetPhaseRegister((clkPhase) + 1)
#endif /* defined(Clock_UNFOLDER__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Clock_UNFOLDER_CLKEN              (* (reg8 *) Clock_UNFOLDER__PM_ACT_CFG)
#define Clock_UNFOLDER_CLKEN_PTR          ((reg8 *) Clock_UNFOLDER__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Clock_UNFOLDER_CLKSTBY            (* (reg8 *) Clock_UNFOLDER__PM_STBY_CFG)
#define Clock_UNFOLDER_CLKSTBY_PTR        ((reg8 *) Clock_UNFOLDER__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Clock_UNFOLDER_DIV_LSB            (* (reg8 *) Clock_UNFOLDER__CFG0)
#define Clock_UNFOLDER_DIV_LSB_PTR        ((reg8 *) Clock_UNFOLDER__CFG0)
#define Clock_UNFOLDER_DIV_PTR            ((reg16 *) Clock_UNFOLDER__CFG0)

/* Clock MSB divider configuration register. */
#define Clock_UNFOLDER_DIV_MSB            (* (reg8 *) Clock_UNFOLDER__CFG1)
#define Clock_UNFOLDER_DIV_MSB_PTR        ((reg8 *) Clock_UNFOLDER__CFG1)

/* Mode and source configuration register */
#define Clock_UNFOLDER_MOD_SRC            (* (reg8 *) Clock_UNFOLDER__CFG2)
#define Clock_UNFOLDER_MOD_SRC_PTR        ((reg8 *) Clock_UNFOLDER__CFG2)

#if defined(Clock_UNFOLDER__CFG3)
/* Analog clock phase configuration register */
#define Clock_UNFOLDER_PHASE              (* (reg8 *) Clock_UNFOLDER__CFG3)
#define Clock_UNFOLDER_PHASE_PTR          ((reg8 *) Clock_UNFOLDER__CFG3)
#endif /* defined(Clock_UNFOLDER__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Clock_UNFOLDER_CLKEN_MASK         Clock_UNFOLDER__PM_ACT_MSK
#define Clock_UNFOLDER_CLKSTBY_MASK       Clock_UNFOLDER__PM_STBY_MSK

/* CFG2 field masks */
#define Clock_UNFOLDER_SRC_SEL_MSK        Clock_UNFOLDER__CFG2_SRC_SEL_MASK
#define Clock_UNFOLDER_MODE_MASK          (~(Clock_UNFOLDER_SRC_SEL_MSK))

#if defined(Clock_UNFOLDER__CFG3)
/* CFG3 phase mask */
#define Clock_UNFOLDER_PHASE_MASK         Clock_UNFOLDER__CFG3_PHASE_DLY_MASK
#endif /* defined(Clock_UNFOLDER__CFG3) */

#endif /* CY_CLOCK_Clock_UNFOLDER_H */


/* [] END OF FILE */
