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

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Char_1_Start();
    LCD_Char_1_PrintString("Some basic message");
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        //LCD_Char_1_PrintString("Hello world");
    }
}

/* [] END OF FILE */
