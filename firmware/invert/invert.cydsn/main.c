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

int16 * sinptr;
int16 sineLUTindex=0;

char recbyte=0;

float A1=0.09305911;
float A2=0.75486969;
float A3=0.15207120;

float B0=4.93296886;
float B1=-1.63710219;
float B2=-4.38245164;
float B3=2.18761941;

int16 sineLUT[512]={150,152,154,156,157,159,161,163,
                    165,167,168,170,172,174,176,177,
                    179,181,183,185,186,188,190,192,
                    194,195,197,199,201,202,204,206,
                    207,209,211,212,214,216,217,219,
                    221,222,224,226,227,229,230,232,
                    233,235,236,238,239,241,242,244,
                    245,247,248,249,251,252,253,255,
                    256,257,259,260,261,262,264,265,
                    266,267,268,269,270,272,273,274,
                    275,276,277,278,279,280,281,281,
                    282,283,284,285,286,286,287,288,
                    289,289,290,291,291,292,292,293,
                    294,294,295,295,296,296,296,297,
                    297,297,298,298,298,299,299,299,
                    299,299,300,300,300,300,300,300,
                    300,300,300,300,300,300,300,299,
                    299,299,299,299,298,298,298,297,
                    297,297,296,296,296,295,295,294,
                    294,293,292,292,291,291,290,289,
                    289,288,287,286,286,285,284,283,
                    282,281,281,280,279,278,277,276,
                    275,274,273,272,270,269,268,267,
                    266,265,264,262,261,260,259,257,
                    256,255,253,252,251,249,248,247,
                    245,244,242,241,239,238,236,235,
                    233,232,230,229,227,226,224,222,
                    221,219,217,216,214,212,211,209,
                    207,206,204,202,201,199,197,195,
                    194,192,190,188,186,185,183,181,
                    179,177,176,174,172,170,168,167,
                    165,163,161,159,157,156,154,152,
                    150};

double calcDuty(double U1, double U2, double U3, double E0, double E1, double E2, double E3){
    return A1*U1+A2*U2+A3*U3+B0*E0+B1*E1+B2*E2+B3*E3;
}


void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    //Type III compensator variables

    
    //Output array
    float U[4] ={0,0,0,0};
    
    //error array
    float E[4]={0,0,0,0};
    
    char tstr[16];

    //clock
    Clock_1_Enable();
    Clock_2_Enable();
    
    //start LCD
    LCD_Char_1_Start();
    LCD_Char_1_PrintString("Some basic message");
    
    //start voltage ADC
    ADC_DelSig_V_IRQ_Enable();
    ADC_DelSig_V_Start();
    //ADC_SAR_V_IRQ_Enable();
    ADC_DelSig_V_StartConvert();
    
    //start pwm
    PWM_BUCK_Start();
    
    PWM_UNFOLD_A_Start();
    PWM_UNFOLD_B_Start();
    
    //UART communication 
    UART_1_Start();
    
    sinptr = sineLUT;
   
    
    //CyDelay(5000);//delay
    
    //CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
        //LCD_Char_1_PrintString("Hello world");
        
        /*
        if(ADC_DelSig_V_IsEndConversion(ADC_DelSig_V_RETURN_STATUS))
        {
            buffvolt = ADC_DelSig_V_GetResult16();
            PWM_BUCK_WriteCompare(buffvolt);
            
            LCD_Char_1_Position(1u, 0u);
            LCD_Char_1_PrintInt16(buffvolt);
            UART_1_WriteTxData(buffvolt);
        }
        */
        
        PWM_BUCK_WriteCompare(sineLUT[sineLUTindex]);
        sineLUTindex++;
        if(sineLUTindex>=249){
            sineLUTindex=0;
        }
        
        
        
        U[3]=U[2];
        U[2]=U[1];
        U[1]=U[0];
        
        E[3]=E[2];
        E[2]=E[1];
        E[1]=E[0];
        E[0] = sineLUT[0]-buffvolt; //placeholder to calculate current error
        //need to multiply it with K factor
        U[0]= calcDuty(U[1], U[2], U[3], E[0], E[1], E[2], E[3]);
        //K factor is 7
        recbyte=UART_1_GetChar();
        if(recbyte=='V'){
            UART_1_PutChar((buffvolt>>8));
            UART_1_PutChar(buffvolt);
        }
        
        sprintf(tstr, "%+1.4f", B2);
        LCD_Char_1_Position(1u, 0u);
        //LCD_Char_1_PrintInt16(A1);
        LCD_Char_1_PrintString(tstr);
        
        LCD_Char_1_Position(1u,8u);
        LCD_Char_1_PrintInt16(sineLUT[sineLUTindex]);
        
        
        
        /*
        PWM_BUCK_WriteCompare(sineLUT[sineLUTindex]); 
        sineLUTindex++;
        if(sineLUTindex>511){
            sineLUTindex=0;
        };
        */
        
        
        //UART_1_PutChar('q');
        //UART_1_WriteTxData('w');
        //UART_1_PutString("are you new?");
        CyDelay(50);//delay
    }
}

/* [] END OF FILE */
