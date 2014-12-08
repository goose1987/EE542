/*******************************************************************************
* File Name: ADC_DelSig_V_INT.c  
* Version 2.30
*
* Description:
*  This file contains the code that operates during the ADC_DelSig interrupt 
*  service routine.  
*
* Note:
*
*******************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "ADC_DelSig_V.h"  


/*******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following 
*   #START and #END tags
*******************************************************************************/
/* `#START ADC_SYS_VAR`  */
extern int16 buffvolt;
extern int16 sineLUTindex;
extern int16 sineLUT[256];
extern uint32 varray[4];


int16 A1 = -7;
int16 A2 = 32;
int16 A3 = 7;

int16 B0 = 14;
int16 B1 = -2;
int16 B2 = -12;
int16 B3 = 5;

extern int32 E[4];
extern int32 U[4];
//extern float calcDuty();

//extern float K; 

/* `#END`  */


/*****************************************************************************
* Function Name: ADC_DelSig_V_ISR1
******************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( ADC_DelSig_V_ISR1)
{
    /***************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    **************************************************************************/
    /* `#START MAIN_ADC_ISR1`  */
    
    buffvolt=ADC_DelSig_V_GetResult16();
    sineLUTindex=Counter_2_ReadCounter();
    varray[sineLUTindex>>6]=buffvolt<<12;
    
    
    
    if (buffvolt < 0) {
        buffvolt = 0;
        
    }
    if (buffvolt<20){
        Control_Reg_1_Write(1);
    
    }else{
        Control_Reg_1_Write(0);
    }

    E[0] = sineLUT[sineLUTindex]-200-buffvolt; 

    
    //integral .6 and .16
    U[1] += E[0]*.22;
    //calculating PI output
    U[0] = E[0]*.008+U[1];

    
    if (U[0] > 398) {
        U[0]=398;
    } else if (U[0] < 0) {
        U[0]=0;
    }
    
    PWM_BUCK_WriteCompare(U[0]);
    
    
    /* `#END`  */
    
    /* Stop the conversion if conversion mode is single sample and resolution
       is above 16 bits. 
    */
    #if(ADC_DelSig_V_CFG1_RESOLUTION > 16 && \
        ADC_DelSig_V_CFG1_CONV_MODE == ADC_DelSig_V_MODE_SINGLE_SAMPLE) 
        ADC_DelSig_V_StopConvert(); 
    #endif /* Single sample conversion mode with resolution above 16 bits */         
        
}


/*****************************************************************************
* Function Name: ADC_DelSig_V_ISR2
******************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( ADC_DelSig_V_ISR2)
{
    /***************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    **************************************************************************/
    /* `#START MAIN_ADC_ISR2`  */

    /* `#END`  */
    
    /* Stop the conversion conversion mode is single sample and resolution
       is above 16 bits.
    */
    #if(ADC_DelSig_V_CFG2_RESOLUTION > 16 && \
        ADC_DelSig_V_CFG2_CONVMODE == ADC_DelSig_V_MODE_SINGLE_SAMPLE) 
        ADC_DelSig_V_StopConvert(); 
    #endif /* Single sample conversion mode with resolution above 16 bits */
    
}


/*****************************************************************************
* Function Name: ADC_DelSig_V_ISR3
******************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( ADC_DelSig_V_ISR3)
{
    /***************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    **************************************************************************/
    /* `#START MAIN_ADC_ISR3`  */

    /* `#END`  */

    /* Stop the conversion if conversion mode is set to single sample and 
       resolution is above 16 bits. 
    */
    #if(ADC_DelSig_V_CFG3_RESOLUTION > 16 && \
        ADC_DelSig_V_CFG3_CONVMODE == ADC_DelSig_V_MODE_SINGLE_SAMPLE) 
        ADC_DelSig_V_StopConvert(); 
    #endif /* Single sample conversion mode with resolution above 16 bits */  
}


/*****************************************************************************
* Function Name: ADC_DelSig_V_ISR4
******************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.  
*
* Parameters:  
*  void
*
* Return: 
*  void 
*
* Reentrant: 
*  No
*
*****************************************************************************/
CY_ISR( ADC_DelSig_V_ISR4)
{
    /***************************************************************************
    *  Custom Code
    *  - add user ISR code between the following #START and #END tags
    **************************************************************************/
    /* `#START MAIN_ADC_ISR4`  */

    /* `#END`  */
    
    /* Stop the conversion if conversion mode is set to single sample and 
       resolution is above 16 bits. 
    */
    #if(ADC_DelSig_V_CFG4_RESOLUTION > 16 && \
        ADC_DelSig_V_CFG4_CONVMODE == ADC_DelSig_V_MODE_SINGLE_SAMPLE) 
        ADC_DelSig_V_StopConvert(); 
    #endif /* Single sample conversion mode with resolution above 16 bits */
}


/* [] END OF FILE */
