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

int16 sineLUT[512]={0x100,0x103,0x106,0x109,0x10d,0x110,0x113,0x116,
                    0x119,0x11c,0x11f,0x122,0x126,0x129,0x12c,0x12f,
                    0x132,0x135,0x138,0x13b,0x13e,0x141,0x144,0x147,
                    0x14a,0x14d,0x150,0x153,0x156,0x159,0x15c,0x15f,
                    0x162,0x165,0x168,0x16b,0x16d,0x170,0x173,0x176,
                    0x179,0x17b,0x17e,0x181,0x184,0x186,0x189,0x18c,
                    0x18e,0x191,0x193,0x196,0x198,0x19b,0x19d,0x1a0,
                    0x1a2,0x1a5,0x1a7,0x1aa,0x1ac,0x1ae,0x1b1,0x1b3,
                    0x1b5,0x1b7,0x1b9,0x1bc,0x1be,0x1c0,0x1c2,0x1c4,
                    0x1c6,0x1c8,0x1ca,0x1cc,0x1ce,0x1cf,0x1d1,0x1d3,
                    0x1d5,0x1d7,0x1d8,0x1da,0x1dc,0x1dd,0x1df,0x1e0,
                    0x1e2,0x1e3,0x1e5,0x1e6,0x1e7,0x1e9,0x1ea,0x1eb,
                    0x1ed,0x1ee,0x1ef,0x1f0,0x1f1,0x1f2,0x1f3,0x1f4,
                    0x1f5,0x1f6,0x1f7,0x1f8,0x1f8,0x1f9,0x1fa,0x1fa,
                    0x1fb,0x1fc,0x1fc,0x1fd,0x1fd,0x1fe,0x1fe,0x1fe,
                    0x1ff,0x1ff,0x1ff,0x200,0x200,0x200,0x200,0x200,
                    0x200,0x200,0x200,0x200,0x200,0x200,0x1ff,0x1ff,
                    0x1ff,0x1fe,0x1fe,0x1fe,0x1fd,0x1fd,0x1fc,0x1fc,
                    0x1fb,0x1fa,0x1fa,0x1f9,0x1f8,0x1f8,0x1f7,0x1f6,
                    0x1f5,0x1f4,0x1f3,0x1f2,0x1f1,0x1f0,0x1ef,0x1ee,
                    0x1ed,0x1eb,0x1ea,0x1e9,0x1e7,0x1e6,0x1e5,0x1e3,
                    0x1e2,0x1e0,0x1df,0x1dd,0x1dc,0x1da,0x1d8,0x1d7,
                    0x1d5,0x1d3,0x1d1,0x1cf,0x1ce,0x1cc,0x1ca,0x1c8,
                    0x1c6,0x1c4,0x1c2,0x1c0,0x1be,0x1bc,0x1b9,0x1b7,
                    0x1b5,0x1b3,0x1b1,0x1ae,0x1ac,0x1aa,0x1a7,0x1a5,
                    0x1a2,0x1a0,0x19d,0x19b,0x198,0x196,0x193,0x191,
                    0x18e,0x18c,0x189,0x186,0x184,0x181,0x17e,0x17b,
                    0x179,0x176,0x173,0x170,0x16d,0x16b,0x168,0x165,
                    0x162,0x15f,0x15c,0x159,0x156,0x153,0x150,0x14d,
                    0x14a,0x147,0x144,0x141,0x13e,0x13b,0x138,0x135,
                    0x132,0x12f,0x12c,0x129,0x126,0x122,0x11f,0x11c,
                    0x119,0x116,0x113,0x110,0x10d,0x109,0x106,0x103,
                    0x100,0xfd,0xfa,0xf7,0xf3,0xf0,0xed,0xea,
                    0xe7,0xe4,0xe1,0xde,0xda,0xd7,0xd4,0xd1,
                    0xce,0xcb,0xc8,0xc5,0xc2,0xbf,0xbc,0xb9,
                    0xb6,0xb3,0xb0,0xad,0xaa,0xa7,0xa4,0xa1,
                    0x9e,0x9b,0x98,0x95,0x93,0x90,0x8d,0x8a,
                    0x87,0x85,0x82,0x7f,0x7c,0x7a,0x77,0x74,
                    0x72,0x6f,0x6d,0x6a,0x68,0x65,0x63,0x60,
                    0x5e,0x5b,0x59,0x56,0x54,0x52,0x4f,0x4d,
                    0x4b,0x49,0x47,0x44,0x42,0x40,0x3e,0x3c,
                    0x3a,0x38,0x36,0x34,0x32,0x31,0x2f,0x2d,
                    0x2b,0x29,0x28,0x26,0x24,0x23,0x21,0x20,
                    0x1e,0x1d,0x1b,0x1a,0x19,0x17,0x16,0x15,
                    0x13,0x12,0x11,0x10,0xf,0xe,0xd,0xc,
                    0xb,0xa,0x9,0x8,0x8,0x7,0x6,0x6,
                    0x5,0x4,0x4,0x3,0x3,0x2,0x2,0x2,
                    0x1,0x1,0x1,0x0,0x0,0x0,0x0,0x0,
                    0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,
                    0x1,0x2,0x2,0x2,0x3,0x3,0x4,0x4,
                    0x5,0x6,0x6,0x7,0x8,0x8,0x9,0xa,
                    0xb,0xc,0xd,0xe,0xf,0x10,0x11,0x12,
                    0x13,0x15,0x16,0x17,0x19,0x1a,0x1b,0x1d,
                    0x1e,0x20,0x21,0x23,0x24,0x26,0x28,0x29,
                    0x2b,0x2d,0x2f,0x31,0x32,0x34,0x36,0x38,
                    0x3a,0x3c,0x3e,0x40,0x42,0x44,0x47,0x49,
                    0x4b,0x4d,0x4f,0x52,0x54,0x56,0x59,0x5b,
                    0x5e,0x60,0x63,0x65,0x68,0x6a,0x6d,0x6f,
                    0x72,0x74,0x77,0x7a,0x7c,0x7f,0x82,0x85,
                    0x87,0x8a,0x8d,0x90,0x93,0x95,0x98,0x9b,
                    0x9e,0xa1,0xa4,0xa7,0xaa,0xad,0xb0,0xb3,
                    0xb6,0xb9,0xbc,0xbf,0xc2,0xc5,0xc8,0xcb,
                    0xce,0xd1,0xd4,0xd7,0xda,0xde,0xe1,0xe4,
                    0xe7,0xea,0xed,0xf0,0xf3,0xf7,0xfa,0xfd};

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
    
    
    //UART communication 
    UART_1_Start();
    
    
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        //LCD_Char_1_PrintString("Hello world");
        if(ADC_DelSig_V_IsEndConversion(ADC_DelSig_V_RETURN_STATUS))
        {
            buffvolt = ADC_DelSig_V_GetResult16();
            PWM_BUCK_WriteCompare(buffvolt);
            
            LCD_Char_1_Position(1u, 0u);
            LCD_Char_1_PrintInt16(buffvolt);
            UART_1_WriteTxData(buffvolt);
        }
        
        //UART_1_PutChar('q');
        //UART_1_WriteTxData('w');
        //UART_1_PutString("are you new?");
        CyDelay(1000);//delay
    }
}

/* [] END OF FILE */
