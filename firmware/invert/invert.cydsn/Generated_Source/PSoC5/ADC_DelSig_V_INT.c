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

/*
extern float A1;
extern float A2;
extern float A3;

extern float B0;
extern float B1;
extern float B2;
extern float B3;
extern float K;

int16 A1 = 3;
int16 A2 = 25;
int16 A3 = 5;

int16 B0 = 163;
int16 B1 = -54;
int16 B2 = -145;
int16 B3 = 72;
*/
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
    if (buffvolt < 0) {
        buffvolt = 0;
    }
    
    //U[3]=U[2];
    //U[2]=U[1];
   // U[1]=U[0];
    
    //E[3]=E[2];
    //E[2]=E[1];
    //E[1]=E[0];
    E[0] = sineLUT[sineLUTindex]-190-buffvolt; 

    //E[0] = sineLUTindex-buffvolt;

    //U[0]= calcDuty(U[1], U[2], U[3], E[0], E[1], E[2], E[3]);
   // U[0] = K*(A1*U[1]+A2*U[2]+A3*U[3]+B0*E[0]+B1*E[1]+B2*E[2]+B3*E[3]);
    //U[0] = (A1*U[1]+A2*U[2]+A3*U[3]+B0*E[0]+B1*E[1]+B2*E[2]+B3*E[3]);
    //U[0] = B0*E[0]+B1*E[1];
    
    //integral .6 and .16
    U[1] += E[0]*.22;
    //calculating PI output
    U[0] = E[0]*.008+U[1];
    
    //PWM_BUCK_WriteCompare(sineLUT[sineLUTindex]-370);
    
    if (U[0] > 398) {
        U[0]=398;
    } else if (U[0] < 0) {
        U[0]=0;
    }
    
    PWM_BUCK_WriteCompare(U[0]);
    
    //sineLUTindex = 25;

    /*
    LCD_Char_1_Position(0, 0);
    LCD_Char_1_PutChar('E');
    LCD_Char_1_PrintNumber(E[0]);
    LCD_Char_1_PutChar(' ');
    LCD_Char_1_PutChar('O');
    LCD_Char_1_PrintNumber(U[0]);
    LCD_Char_1_PutChar(' ');
    LCD_Char_1_PutChar(' ');
    
    LCD_Char_1_Position(1, 0);
    LCD_Char_1_PutChar('B');
    LCD_Char_1_PrintNumber(buffvolt);
    LCD_Char_1_PutChar(' ');
    LCD_Char_1_PutChar('R');
    LCD_Char_1_PrintNumber(sineLUT[sineLUTindex]-370);
    LCD_Char_1_PutChar(' ');
    LCD_Char_1_PutChar(' ');
    LCD_Char_1_PutChar(' ');
    LCD_Char_1_PutChar(' ');
    
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
