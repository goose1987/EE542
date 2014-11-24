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
//extern uint8 dataReady;
extern int16 sineLUT[256];
extern int16 sineLUTindex;

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
    
    PWM_BUCK_WriteCompare(sineLUT[sineLUTindex]-370);
    
    sineLUTindex++;
    if(sineLUTindex>=256){
        sineLUTindex=0;
        Control_Reg_1_Write(~Control_Reg_1_Read());
    }
    
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
