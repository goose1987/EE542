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
/*
float A1=0.09305911;
float A2=0.75486969;
float A3=0.15207120;

float B0=4.93296886;
float B1=-1.63710219;
float B2=-4.38245164;
float B3=2.18761941;

float A1=0.09;
float A2=0.75;
float A3=0.15;

float B0=4.93;
float B1=-1.64;
float B2=-4.38;
float B3=2.19;
*/

float K = 33; //K factor

//making everything int16 by multiplying the k factor


//Output array
int32 U[4] ={0,0,0,0};
    
//error array
int32 E[4]={0,0,0,0};

/*int16 sineLUT[256]={384,389,393,398,403,408,412,417,
                    422,426,431,436,440,445,450,454,
                    459,464,468,473,477,482,486,491,
                    495,500,504,509,513,518,522,527,
                    531,535,540,544,548,552,557,561,
                    565,569,573,577,581,585,589,593,
                    597,601,605,609,613,617,620,624,
                    628,631,635,638,642,645,649,652,
                    656,659,662,665,669,672,675,678,
                    681,684,687,690,692,695,698,701,
                    703,706,708,711,713,716,718,720,
                    723,725,727,729,731,733,735,737,
                    739,741,742,744,746,747,749,750,
                    751,753,754,755,756,758,759,760,
                    761,762,762,763,764,765,765,766,
                    766,767,767,767,768,768,768,768,
                    768,768,768,768,768,767,767,767,
                    766,766,765,765,764,763,762,762,
                    761,760,759,758,756,755,754,753,
                    751,750,749,747,746,744,742,741,
                    739,737,735,733,731,729,727,725,
                    723,720,718,716,713,711,708,706,
                    703,701,698,695,692,690,687,684,
                    681,678,675,672,669,665,662,659,
                    656,652,649,645,642,638,635,631,
                    628,624,620,617,613,609,605,601,
                    597,593,589,585,581,577,573,569,
                    565,561,557,552,548,544,540,535,
                    531,527,522,518,513,509,504,500,
                    495,491,486,482,477,473,468,464,
                    459,454,450,445,440,436,431,426,
                    422,417,412,408,403,398,393,389};*/
                  
int16 sineLUT[256] = {200,202,205,207,210,212,215,217,
220,222,224,227,229,232,234,237,
239,241,244,246,249,251,253,256,
258,260,263,265,267,270,272,274,
277,279,281,283,286,288,290,292,
294,296,299,301,303,305,307,309,
311,313,315,317,319,321,323,325,
327,329,331,332,334,336,338,340,
341,343,345,347,348,350,351,353,
355,356,358,359,361,362,364,365,
366,368,369,370,372,373,374,375,
376,378,379,380,381,382,383,384,
385,386,387,387,388,389,390,391,
391,392,393,393,394,395,395,396,
396,397,397,397,398,398,398,399,
399,399,399,400,400,400,400,400,
400,400,400,400,400,400,399,399,
399,399,398,398,398,397,397,397,
396,396,395,395,394,393,393,392,
391,391,390,389,388,387,387,386,
385,384,383,382,381,380,379,378,
376,375,374,373,372,370,369,368,
366,365,364,362,361,359,358,356,
355,353,351,350,348,347,345,343,
341,340,338,336,334,332,331,329,
327,325,323,321,319,317,315,313,
311,309,307,305,303,301,299,296,
294,292,290,288,286,283,281,279,
277,274,272,270,267,265,263,260,
258,256,253,251,249,246,244,241,
239,237,234,232,229,227,224,222,
220,217,215,212,210,207,205,202};
//calculate the duty cycle by multiplying the transfer function with the K factor 
//double calcDuty(double U1, double U2, double U3, double E0, double E1, double E2, double E3){
//    return K*(A1*U1+A2*U2+A3*U3+B0*E0+B1*E1+B2*E2+B3*E3);
//}

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    
    char tstr[16];

    //clock

    Clock_2_Enable();
    Clock_4_Enable();
    
    Counter_1_Start();
    isr_LUT_Start();
    
    //start LCD
    LCD_Char_1_Start();
    //LCD_Char_1_PrintString("changed message");
    
    //start voltage ADC
    ADC_DelSig_V_IRQ_Enable();
    ADC_DelSig_V_Start();
    //ADC_SAR_V_IRQ_Enable();
    ADC_DelSig_V_StartConvert();
    
    //start pwm
    PWM_BUCK_Start();
    
    //unfolder register
    Control_Reg_1_Write(0);
    
    //UART communication 
    UART_1_Start();
    
    sinptr = sineLUT;

    //CyDelay(5000);//delay
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
        /* Place your application code here. */
    
        

        recbyte=UART_1_GetChar();
        if(recbyte=='V'){
            UART_1_PutChar((buffvolt>>8));
            UART_1_PutChar(buffvolt);
        }
             
        //sprintf(tstr, "%1.4lf", U[0]);
        LCD_Char_1_Position(1, 0);
        //LCD_Char_1_PrintInt16(E[0]);
        //LCD_Char_1_PrintString(tstr);
        
        //LCD_Char_1_Position(1u,0u);
        LCD_Char_1_PrintInt16(buffvolt);

 
        //CyDelay(5);//delay
    }
}