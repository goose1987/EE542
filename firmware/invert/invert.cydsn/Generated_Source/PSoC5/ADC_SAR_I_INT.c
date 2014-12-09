/*******************************************************************************
* File Name: ADC_SAR_I_INT.c
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

#include "ADC_SAR_I.h"


/******************************************************************************
* Custom Declarations and Variables
* - add user inlcude files, prototypes and variables between the following
*   #START and #END tags
******************************************************************************/
/* `#START ADC_SYS_VAR`  */
extern int16 buffamp;
extern int16 sineLUTindex;
extern uint32 varray[32];
extern uint32 iarray[32];
/* `#END`  */


#if(ADC_SAR_I_IRQ_REMOVE == 0u)


    /******************************************************************************
    * Function Name: ADC_SAR_I_ISR
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
    CY_ISR( ADC_SAR_I_ISR )
    {
        /************************************************************************
        *  Custom Code
        *  - add user ISR code between the following #START and #END tags
        *************************************************************************/
          /* `#START MAIN_ADC_ISR`  */
            buffamp=ADC_SAR_I_GetResult16();
            iarray[sineLUTindex>>3]=buffamp<<12;
          /* `#END`  */

    }

#endif   /* End ADC_SAR_I_IRQ_REMOVE */

/* [] END OF FILE */
