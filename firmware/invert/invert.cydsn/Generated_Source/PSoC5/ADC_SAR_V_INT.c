/*******************************************************************************
* File Name: ADC_SAR_V_INT.c
* Version 2.0
*
*  Description:
*    This file contains the code that operates during the ADC_SAR interrupt
*    service routine.
*
*   Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_SAR_V.h"


/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */
extern int16 buffvolt;
extern uint8 dataReady;
/* `#END`  */


#if(ADC_SAR_V_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: ADC_SAR_V_ISR
    *******************************************************************************
    *
    * Summary:
    *  Handle Interrupt Service Routine.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  No.
    *
    ******************************************************************************/
    CY_ISR( ADC_SAR_V_ISR )
    {
        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
          /* `#START MAIN_ADC_ISR`  */
          
          //get converted result
          //move result to buffer
          buffvolt=ADC_SAR_V_GetResult16();
          dataReady=1;
          
          //exit interrupt

          /* `#END`  */

    }

#endif   /* End ADC_SAR_V_IRQ_REMOVE */

/* [] END OF FILE */
