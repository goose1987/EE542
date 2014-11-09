/*******************************************************************************
* File Name: A_HS.h  
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

#if !defined(CY_PINS_A_HS_H) /* Pins A_HS_H */
#define CY_PINS_A_HS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "A_HS_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 A_HS__PORT == 15 && ((A_HS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    A_HS_Write(uint8 value) ;
void    A_HS_SetDriveMode(uint8 mode) ;
uint8   A_HS_ReadDataReg(void) ;
uint8   A_HS_Read(void) ;
uint8   A_HS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define A_HS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define A_HS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define A_HS_DM_RES_UP          PIN_DM_RES_UP
#define A_HS_DM_RES_DWN         PIN_DM_RES_DWN
#define A_HS_DM_OD_LO           PIN_DM_OD_LO
#define A_HS_DM_OD_HI           PIN_DM_OD_HI
#define A_HS_DM_STRONG          PIN_DM_STRONG
#define A_HS_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define A_HS_MASK               A_HS__MASK
#define A_HS_SHIFT              A_HS__SHIFT
#define A_HS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define A_HS_PS                     (* (reg8 *) A_HS__PS)
/* Data Register */
#define A_HS_DR                     (* (reg8 *) A_HS__DR)
/* Port Number */
#define A_HS_PRT_NUM                (* (reg8 *) A_HS__PRT) 
/* Connect to Analog Globals */                                                  
#define A_HS_AG                     (* (reg8 *) A_HS__AG)                       
/* Analog MUX bux enable */
#define A_HS_AMUX                   (* (reg8 *) A_HS__AMUX) 
/* Bidirectional Enable */                                                        
#define A_HS_BIE                    (* (reg8 *) A_HS__BIE)
/* Bit-mask for Aliased Register Access */
#define A_HS_BIT_MASK               (* (reg8 *) A_HS__BIT_MASK)
/* Bypass Enable */
#define A_HS_BYP                    (* (reg8 *) A_HS__BYP)
/* Port wide control signals */                                                   
#define A_HS_CTL                    (* (reg8 *) A_HS__CTL)
/* Drive Modes */
#define A_HS_DM0                    (* (reg8 *) A_HS__DM0) 
#define A_HS_DM1                    (* (reg8 *) A_HS__DM1)
#define A_HS_DM2                    (* (reg8 *) A_HS__DM2) 
/* Input Buffer Disable Override */
#define A_HS_INP_DIS                (* (reg8 *) A_HS__INP_DIS)
/* LCD Common or Segment Drive */
#define A_HS_LCD_COM_SEG            (* (reg8 *) A_HS__LCD_COM_SEG)
/* Enable Segment LCD */
#define A_HS_LCD_EN                 (* (reg8 *) A_HS__LCD_EN)
/* Slew Rate Control */
#define A_HS_SLW                    (* (reg8 *) A_HS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define A_HS_PRTDSI__CAPS_SEL       (* (reg8 *) A_HS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define A_HS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) A_HS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define A_HS_PRTDSI__OE_SEL0        (* (reg8 *) A_HS__PRTDSI__OE_SEL0) 
#define A_HS_PRTDSI__OE_SEL1        (* (reg8 *) A_HS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define A_HS_PRTDSI__OUT_SEL0       (* (reg8 *) A_HS__PRTDSI__OUT_SEL0) 
#define A_HS_PRTDSI__OUT_SEL1       (* (reg8 *) A_HS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define A_HS_PRTDSI__SYNC_OUT       (* (reg8 *) A_HS__PRTDSI__SYNC_OUT) 


#if defined(A_HS__INTSTAT)  /* Interrupt Registers */

    #define A_HS_INTSTAT                (* (reg8 *) A_HS__INTSTAT)
    #define A_HS_SNAP                   (* (reg8 *) A_HS__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_A_HS_H */


/* [] END OF FILE */
