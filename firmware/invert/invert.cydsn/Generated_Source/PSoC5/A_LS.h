/*******************************************************************************
* File Name: A_LS.h  
* Version 1.90
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_A_LS_H) /* Pins A_LS_H */
#define CY_PINS_A_LS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "A_LS_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 A_LS__PORT == 15 && ((A_LS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    A_LS_Write(uint8 value) ;
void    A_LS_SetDriveMode(uint8 mode) ;
uint8   A_LS_ReadDataReg(void) ;
uint8   A_LS_Read(void) ;
uint8   A_LS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define A_LS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define A_LS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define A_LS_DM_RES_UP          PIN_DM_RES_UP
#define A_LS_DM_RES_DWN         PIN_DM_RES_DWN
#define A_LS_DM_OD_LO           PIN_DM_OD_LO
#define A_LS_DM_OD_HI           PIN_DM_OD_HI
#define A_LS_DM_STRONG          PIN_DM_STRONG
#define A_LS_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define A_LS_MASK               A_LS__MASK
#define A_LS_SHIFT              A_LS__SHIFT
#define A_LS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define A_LS_PS                     (* (reg8 *) A_LS__PS)
/* Data Register */
#define A_LS_DR                     (* (reg8 *) A_LS__DR)
/* Port Number */
#define A_LS_PRT_NUM                (* (reg8 *) A_LS__PRT) 
/* Connect to Analog Globals */                                                  
#define A_LS_AG                     (* (reg8 *) A_LS__AG)                       
/* Analog MUX bux enable */
#define A_LS_AMUX                   (* (reg8 *) A_LS__AMUX) 
/* Bidirectional Enable */                                                        
#define A_LS_BIE                    (* (reg8 *) A_LS__BIE)
/* Bit-mask for Aliased Register Access */
#define A_LS_BIT_MASK               (* (reg8 *) A_LS__BIT_MASK)
/* Bypass Enable */
#define A_LS_BYP                    (* (reg8 *) A_LS__BYP)
/* Port wide control signals */                                                   
#define A_LS_CTL                    (* (reg8 *) A_LS__CTL)
/* Drive Modes */
#define A_LS_DM0                    (* (reg8 *) A_LS__DM0) 
#define A_LS_DM1                    (* (reg8 *) A_LS__DM1)
#define A_LS_DM2                    (* (reg8 *) A_LS__DM2) 
/* Input Buffer Disable Override */
#define A_LS_INP_DIS                (* (reg8 *) A_LS__INP_DIS)
/* LCD Common or Segment Drive */
#define A_LS_LCD_COM_SEG            (* (reg8 *) A_LS__LCD_COM_SEG)
/* Enable Segment LCD */
#define A_LS_LCD_EN                 (* (reg8 *) A_LS__LCD_EN)
/* Slew Rate Control */
#define A_LS_SLW                    (* (reg8 *) A_LS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define A_LS_PRTDSI__CAPS_SEL       (* (reg8 *) A_LS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define A_LS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) A_LS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define A_LS_PRTDSI__OE_SEL0        (* (reg8 *) A_LS__PRTDSI__OE_SEL0) 
#define A_LS_PRTDSI__OE_SEL1        (* (reg8 *) A_LS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define A_LS_PRTDSI__OUT_SEL0       (* (reg8 *) A_LS__PRTDSI__OUT_SEL0) 
#define A_LS_PRTDSI__OUT_SEL1       (* (reg8 *) A_LS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define A_LS_PRTDSI__SYNC_OUT       (* (reg8 *) A_LS__PRTDSI__SYNC_OUT) 


#if defined(A_LS__INTSTAT)  /* Interrupt Registers */

    #define A_LS_INTSTAT                (* (reg8 *) A_LS__INTSTAT)
    #define A_LS_SNAP                   (* (reg8 *) A_LS__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_A_LS_H */


/* [] END OF FILE */
