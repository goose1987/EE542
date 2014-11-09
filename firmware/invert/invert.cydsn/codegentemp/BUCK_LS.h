/*******************************************************************************
* File Name: BUCK_LS.h  
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

#if !defined(CY_PINS_BUCK_LS_H) /* Pins BUCK_LS_H */
#define CY_PINS_BUCK_LS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "BUCK_LS_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 BUCK_LS__PORT == 15 && ((BUCK_LS__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    BUCK_LS_Write(uint8 value) ;
void    BUCK_LS_SetDriveMode(uint8 mode) ;
uint8   BUCK_LS_ReadDataReg(void) ;
uint8   BUCK_LS_Read(void) ;
uint8   BUCK_LS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define BUCK_LS_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define BUCK_LS_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define BUCK_LS_DM_RES_UP          PIN_DM_RES_UP
#define BUCK_LS_DM_RES_DWN         PIN_DM_RES_DWN
#define BUCK_LS_DM_OD_LO           PIN_DM_OD_LO
#define BUCK_LS_DM_OD_HI           PIN_DM_OD_HI
#define BUCK_LS_DM_STRONG          PIN_DM_STRONG
#define BUCK_LS_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define BUCK_LS_MASK               BUCK_LS__MASK
#define BUCK_LS_SHIFT              BUCK_LS__SHIFT
#define BUCK_LS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define BUCK_LS_PS                     (* (reg8 *) BUCK_LS__PS)
/* Data Register */
#define BUCK_LS_DR                     (* (reg8 *) BUCK_LS__DR)
/* Port Number */
#define BUCK_LS_PRT_NUM                (* (reg8 *) BUCK_LS__PRT) 
/* Connect to Analog Globals */                                                  
#define BUCK_LS_AG                     (* (reg8 *) BUCK_LS__AG)                       
/* Analog MUX bux enable */
#define BUCK_LS_AMUX                   (* (reg8 *) BUCK_LS__AMUX) 
/* Bidirectional Enable */                                                        
#define BUCK_LS_BIE                    (* (reg8 *) BUCK_LS__BIE)
/* Bit-mask for Aliased Register Access */
#define BUCK_LS_BIT_MASK               (* (reg8 *) BUCK_LS__BIT_MASK)
/* Bypass Enable */
#define BUCK_LS_BYP                    (* (reg8 *) BUCK_LS__BYP)
/* Port wide control signals */                                                   
#define BUCK_LS_CTL                    (* (reg8 *) BUCK_LS__CTL)
/* Drive Modes */
#define BUCK_LS_DM0                    (* (reg8 *) BUCK_LS__DM0) 
#define BUCK_LS_DM1                    (* (reg8 *) BUCK_LS__DM1)
#define BUCK_LS_DM2                    (* (reg8 *) BUCK_LS__DM2) 
/* Input Buffer Disable Override */
#define BUCK_LS_INP_DIS                (* (reg8 *) BUCK_LS__INP_DIS)
/* LCD Common or Segment Drive */
#define BUCK_LS_LCD_COM_SEG            (* (reg8 *) BUCK_LS__LCD_COM_SEG)
/* Enable Segment LCD */
#define BUCK_LS_LCD_EN                 (* (reg8 *) BUCK_LS__LCD_EN)
/* Slew Rate Control */
#define BUCK_LS_SLW                    (* (reg8 *) BUCK_LS__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define BUCK_LS_PRTDSI__CAPS_SEL       (* (reg8 *) BUCK_LS__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define BUCK_LS_PRTDSI__DBL_SYNC_IN    (* (reg8 *) BUCK_LS__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define BUCK_LS_PRTDSI__OE_SEL0        (* (reg8 *) BUCK_LS__PRTDSI__OE_SEL0) 
#define BUCK_LS_PRTDSI__OE_SEL1        (* (reg8 *) BUCK_LS__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define BUCK_LS_PRTDSI__OUT_SEL0       (* (reg8 *) BUCK_LS__PRTDSI__OUT_SEL0) 
#define BUCK_LS_PRTDSI__OUT_SEL1       (* (reg8 *) BUCK_LS__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define BUCK_LS_PRTDSI__SYNC_OUT       (* (reg8 *) BUCK_LS__PRTDSI__SYNC_OUT) 


#if defined(BUCK_LS__INTSTAT)  /* Interrupt Registers */

    #define BUCK_LS_INTSTAT                (* (reg8 *) BUCK_LS__INTSTAT)
    #define BUCK_LS_SNAP                   (* (reg8 *) BUCK_LS__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_BUCK_LS_H */


/* [] END OF FILE */
