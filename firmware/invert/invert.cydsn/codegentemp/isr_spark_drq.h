/*******************************************************************************
* File Name: isr_spark_drq.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_spark_drq_H)
#define CY_ISR_isr_spark_drq_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_spark_drq_Start(void);
void isr_spark_drq_StartEx(cyisraddress address);
void isr_spark_drq_Stop(void);

CY_ISR_PROTO(isr_spark_drq_Interrupt);

void isr_spark_drq_SetVector(cyisraddress address);
cyisraddress isr_spark_drq_GetVector(void);

void isr_spark_drq_SetPriority(uint8 priority);
uint8 isr_spark_drq_GetPriority(void);

void isr_spark_drq_Enable(void);
uint8 isr_spark_drq_GetState(void);
void isr_spark_drq_Disable(void);

void isr_spark_drq_SetPending(void);
void isr_spark_drq_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_spark_drq ISR. */
#define isr_spark_drq_INTC_VECTOR            ((reg32 *) isr_spark_drq__INTC_VECT)

/* Address of the isr_spark_drq ISR priority. */
#define isr_spark_drq_INTC_PRIOR             ((reg8 *) isr_spark_drq__INTC_PRIOR_REG)

/* Priority of the isr_spark_drq interrupt. */
#define isr_spark_drq_INTC_PRIOR_NUMBER      isr_spark_drq__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_spark_drq interrupt. */
#define isr_spark_drq_INTC_SET_EN            ((reg32 *) isr_spark_drq__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_spark_drq interrupt. */
#define isr_spark_drq_INTC_CLR_EN            ((reg32 *) isr_spark_drq__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_spark_drq interrupt state to pending. */
#define isr_spark_drq_INTC_SET_PD            ((reg32 *) isr_spark_drq__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_spark_drq interrupt. */
#define isr_spark_drq_INTC_CLR_PD            ((reg32 *) isr_spark_drq__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_spark_drq_H */


/* [] END OF FILE */
