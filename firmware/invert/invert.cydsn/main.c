/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <device.h>

int16 buffvolt=0;
uint8 dataReady=0;

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    CYGlobalIntEnable;
    
    //start LCD
    LCD_Char_1_Start();
    LCD_Char_1_PrintString("Some basic message");
    
    //start voltage ADC
    ADC_SAR_V_Start();
    ADC_SAR_V_IRQ_Enable();
    ADC_SAR_V_StartConvert();
    
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        //LCD_Char_1_PrintString("Hello world");
    }
}

/* [] END OF FILE */
