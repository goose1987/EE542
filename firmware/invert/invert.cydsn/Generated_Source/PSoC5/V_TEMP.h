/*******************************************************************************
* File Name: V_TEMP.h  
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

#if !defined(CY_PINS_V_TEMP_H) /* Pins V_TEMP_H */
#define CY_PINS_V_TEMP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "V_TEMP_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v1_90 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 V_TEMP__PORT == 15 && ((V_TEMP__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    V_TEMP_Write(uint8 value) ;
void    V_TEMP_SetDriveMode(uint8 mode) ;
uint8   V_TEMP_ReadDataReg(void) ;
uint8   V_TEMP_Read(void) ;
uint8   V_TEMP_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define V_TEMP_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define V_TEMP_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define V_TEMP_DM_RES_UP          PIN_DM_RES_UP
#define V_TEMP_DM_RES_DWN         PIN_DM_RES_DWN
#define V_TEMP_DM_OD_LO           PIN_DM_OD_LO
#define V_TEMP_DM_OD_HI           PIN_DM_OD_HI
#define V_TEMP_DM_STRONG          PIN_DM_STRONG
#define V_TEMP_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define V_TEMP_MASK               V_TEMP__MASK
#define V_TEMP_SHIFT              V_TEMP__SHIFT
#define V_TEMP_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define V_TEMP_PS                     (* (reg8 *) V_TEMP__PS)
/* Data Register */
#define V_TEMP_DR                     (* (reg8 *) V_TEMP__DR)
/* Port Number */
#define V_TEMP_PRT_NUM                (* (reg8 *) V_TEMP__PRT) 
/* Connect to Analog Globals */                                                  
#define V_TEMP_AG                     (* (reg8 *) V_TEMP__AG)                       
/* Analog MUX bux enable */
#define V_TEMP_AMUX                   (* (reg8 *) V_TEMP__AMUX) 
/* Bidirectional Enable */                                                        
#define V_TEMP_BIE                    (* (reg8 *) V_TEMP__BIE)
/* Bit-mask for Aliased Register Access */
#define V_TEMP_BIT_MASK               (* (reg8 *) V_TEMP__BIT_MASK)
/* Bypass Enable */
#define V_TEMP_BYP                    (* (reg8 *) V_TEMP__BYP)
/* Port wide control signals */                                                   
#define V_TEMP_CTL                    (* (reg8 *) V_TEMP__CTL)
/* Drive Modes */
#define V_TEMP_DM0                    (* (reg8 *) V_TEMP__DM0) 
#define V_TEMP_DM1                    (* (reg8 *) V_TEMP__DM1)
#define V_TEMP_DM2                    (* (reg8 *) V_TEMP__DM2) 
/* Input Buffer Disable Override */
#define V_TEMP_INP_DIS                (* (reg8 *) V_TEMP__INP_DIS)
/* LCD Common or Segment Drive */
#define V_TEMP_LCD_COM_SEG            (* (reg8 *) V_TEMP__LCD_COM_SEG)
/* Enable Segment LCD */
#define V_TEMP_LCD_EN                 (* (reg8 *) V_TEMP__LCD_EN)
/* Slew Rate Control */
#define V_TEMP_SLW                    (* (reg8 *) V_TEMP__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define V_TEMP_PRTDSI__CAPS_SEL       (* (reg8 *) V_TEMP__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define V_TEMP_PRTDSI__DBL_SYNC_IN    (* (reg8 *) V_TEMP__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define V_TEMP_PRTDSI__OE_SEL0        (* (reg8 *) V_TEMP__PRTDSI__OE_SEL0) 
#define V_TEMP_PRTDSI__OE_SEL1        (* (reg8 *) V_TEMP__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define V_TEMP_PRTDSI__OUT_SEL0       (* (reg8 *) V_TEMP__PRTDSI__OUT_SEL0) 
#define V_TEMP_PRTDSI__OUT_SEL1       (* (reg8 *) V_TEMP__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define V_TEMP_PRTDSI__SYNC_OUT       (* (reg8 *) V_TEMP__PRTDSI__SYNC_OUT) 


#if defined(V_TEMP__INTSTAT)  /* Interrupt Registers */

    #define V_TEMP_INTSTAT                (* (reg8 *) V_TEMP__INTSTAT)
    #define V_TEMP_SNAP                   (* (reg8 *) V_TEMP__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_V_TEMP_H */


/* [] END OF FILE */
