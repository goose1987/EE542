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
    //CYGlobalIntEnable;
    
    //clock
    Clock_1_Enable();
    
    //start LCD
    LCD_Char_1_Start();
    LCD_Char_1_PrintString("Some basic message");
    
    //start voltage ADC
    ADC_DelSig_V_Start();
    //ADC_SAR_V_IRQ_Enable();
    ADC_DelSig_V_StartConvert();
    
    //start pwm
    
    PWM_BUCK_Start();
    
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        //LCD_Char_1_PrintString("Hello world");
        if(ADC_DelSig_V_IsEndConversion(ADC_DelSig_V_RETURN_STATUS))
        {
            buffvolt = ADC_DelSig_V_GetResult16();
            PWM_BUCK_WriteCompare(buffvolt);
            //LCD_Char_1_Position(1u, 0u);
            //LCD_Char_1_PrintInt16(buffvolt);
        }
        
       
        
    }
}

/* [] END OF FILE */
