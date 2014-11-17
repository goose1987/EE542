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

float K = 7; //K factor

int16 sineLUT[256]={384,389,393,398,403,408,412,417,
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
                    422,417,412,408,403,398,393,389};
                    
//calculate the duty cycle by multiplying the transfer function with the K factor 
double calcDuty(double U1, double U2, double U3, double E0, double E1, double E2, double E3){
    return K*(A1*U1+A2*U2+A3*U3+B0*E0+B1*E1+B2*E2+B3*E3);
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
        
        
        /*
        U[3]=U[2];
        U[2]=U[1];
        U[1]=U[0];
        
        E[3]=E[2];
        E[2]=E[1];
        E[1]=E[0];
        E[0] = sineLUT[sineLUTindex]-buffvolt; //placeholder to calculate current error

        U[0]= calcDuty(U[1], U[2], U[3], E[0], E[1], E[2], E[3]);

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
        */
        
        
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
        //CyDelay(50);//delay
    }
}

/* [] END OF FILE */
