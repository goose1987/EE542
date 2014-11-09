/*******************************************************************************
* File Name: B_LS.h  
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

#if !defined(CY_PINS_B_LS_H) /* Pins B_LS_H */
#define CY_PINS_B_LS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "B_LS_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 B_LS__PORT == 15 && ((B_LS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    B_LS_Write(uint8 value) ;
void    B_LS_SetDriveMode(uint8 mode) ;
uint8   B_LS_ReadDataReg(void) ;
uint8   B_LS_Read(void) ;
uint8   B_LS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define B_LS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define B_LS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define B_LS_DM_RES_UP          PIN_DM_RES_UP
#define B_LS_DM_RES_DWN         PIN_DM_RES_DWN
#define B_LS_DM_OD_LO           PIN_DM_OD_LO
#define B_LS_DM_OD_HI           PIN_DM_OD_HI
#define B_LS_DM_STRONG          PIN_DM_STRONG
#define B_LS_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define B_LS_MASK               B_LS__MASK
#define B_LS_SHIFT              B_LS__SHIFT
#define B_LS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define B_LS_PS                     (* (reg8 *) B_LS__PS)
/* Data Register */
#define B_LS_DR                     (* (reg8 *) B_LS__DR)
/* Port Number */
#define B_LS_PRT_NUM                (* (reg8 *) B_LS__PRT) 
/* Connect to Analog Globals */                                                  
#define B_LS_AG                     (* (reg8 *) B_LS__AG)                       
/* Analog MUX bux enable */
#define B_LS_AMUX                   (* (reg8 *) B_LS__AMUX) 
/* Bidirectional Enable */                                                        
#define B_LS_BIE                    (* (reg8 *) B_LS__BIE)
/* Bit-mask for Aliased Register Access */
#define B_LS_BIT_MASK               (* (reg8 *) B_LS__BIT_MASK)
/* Bypass Enable */
#define B_LS_BYP                    (* (reg8 *) B_LS__BYP)
/* Port wide control signals */                                                   
#define B_LS_CTL                    (* (reg8 *) B_LS__CTL)
/* Drive Modes */
#define B_LS_DM0                    (* (reg8 *) B_LS__DM0) 
#define B_LS_DM1                    (* (reg8 *) B_LS__DM1)
#define B_LS_DM2                    (* (reg8 *) B_LS__DM2) 
/* Input Buffer Disable Override */
#define B_LS_INP_DIS                (* (reg8 *) B_LS__INP_DIS)
/* LCD Common or Segment Drive */
#define B_LS_LCD_COM_SEG            (* (reg8 *) B_LS__LCD_COM_SEG)
/* Enable Segment LCD */
#define B_LS_LCD_EN                 (* (reg8 *) B_LS__LCD_EN)
/* Slew Rate Control */
#define B_LS_SLW                    (* (reg8 *) B_LS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define B_LS_PRTDSI__CAPS_SEL       (* (reg8 *) B_LS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define B_LS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) B_LS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define B_LS_PRTDSI__OE_SEL0        (* (reg8 *) B_LS__PRTDSI__OE_SEL0) 
#define B_LS_PRTDSI__OE_SEL1        (* (reg8 *) B_LS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define B_LS_PRTDSI__OUT_SEL0       (* (reg8 *) B_LS__PRTDSI__OUT_SEL0) 
#define B_LS_PRTDSI__OUT_SEL1       (* (reg8 *) B_LS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define B_LS_PRTDSI__SYNC_OUT       (* (reg8 *) B_LS__PRTDSI__SYNC_OUT) 


#if defined(B_LS__INTSTAT)  /* Interrupt Registers */

    #define B_LS_INTSTAT                (* (reg8 *) B_LS__INTSTAT)
    #define B_LS_SNAP                   (* (reg8 *) B_LS__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_B_LS_H */


/* [] END OF FILE */
