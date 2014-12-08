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
#include <math.h>

#define DFB_ONE (0x7FFFFFu)
 
void DMA_Init(void);
//void Matrix_Print(uint16 Mass[ROW][COLUMN]) CYREENTRANT;

uint8 dma_stga_in_channel;
uint8 dma_stga_in_td;
uint8 dma_stga_out_channel;
uint8 dma_stga_out_td;
uint8 dma_ack_channel, dma_ack_td;

    
    /* Variable declarations for DMA_OUT_A */
/* Move these variable declarations to the top of the function */

uint8 DMA_OUT_A_Chan;
uint8 DMA_OUT_A_TD[1];

/* DMA Configuration for DMA_OUT_A */
    #define DMA_OUT_A_BYTES_PER_BURST 127
    #define DMA_OUT_A_REQUEST_PER_BURST 0
    #define DMA_OUT_A_SRC_BASE (CYDEV_SRAM_BASE)
    #define DMA_OUT_A_DST_BASE (CYDEV_SRAM_BASE)

int16 buffvolt=0;
uint8 dataReady=0;

int16 * sinptr;
int16 sineLUTindex=0;

char recbyte=0;


uint32 varray[8];
//uint32 varray[4]={0x30000,0x30000,0x30000,0x30000};
//uint32 varray[1]={0x300000};
uint32 rmsvolt;
int16 varridx=0;

float K = 33; //K factor

//making everything int16 by multiplying the k factor


//Output array
int32 U[4] ={0,0,0,0};
    
//error array
int32 E[4]={0,0,0,0};
                  
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


/*******************************************************************************/
CY_ISR(isr_DFB_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_DFB_Interrupt` */
    
   //uint32 qur=DFB_1_GetOutputValue(1);
   rmsvolt=sqrt(DFB_1_GetOutputValue(1)>>3);
   DFB_1_Stop();
   //CyGlobalIntDisable;
   //DFB_1_Start();
   //DFB_1_ClearSemaphores(DFB_1_SEM1);
   
   //LCD_Char_1_Position(1, 0);
        //LCD_Char_1_PrintInt16(E[0]);
        //LCD_Char_1_PrintString(tstr);
        
        //LCD_Char_1_Position(1u,0u);
        
        //qur=sqrt(qur);
        //LCD_Char_1_PrintInt16(qur>>16);
        //LCD_Char_1_PrintInt16(qur);
        
        //LCD_Char_1_PutChar(' ');
        //LCD_Char_1_PrintInt16(buffvolt);
        
        //DFB_1_SetSemaphores(DFB_1_SEM1);
        
     //CyGlobalIntEnable;   
        
    /* `#END` */
}

CY_ISR(isr_spark_drq_Interrupt)
{
    /*  Place your Interrupt code here. */
    /* `#START isr_spark_drq_Interrupt` */
        //DFB_1_SetSemaphores(DFB_1_SEM1);
        int recbyte=UART_1_GetChar();
        //UART_1_PutChar(0x10);
        
        if(recbyte=='V'){
            UART_1_PutChar((rmsvolt>>8));
            UART_1_PutChar(rmsvolt);
            //UART_1_PutChar((0x12AF>>8));
            //UART_1_PutChar(0xAF);
        }
    /* `#END` */
}

void main()
{
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    
    //char tstr[16];
    
    //counter
   
    Counter_2_Start();

    //clock

    Clock_2_Enable();
    Clock_LUT_Enable();
    
    
    
    isr_DFB_Start();
    isr_spark_drq_Start();
    
    //start LCD
    LCD_Char_1_Start();
    //LCD_Char_1_PrintString("changed message");
    
    //start voltage ADC
    ADC_DelSig_V_IRQ_Enable();
    ADC_DelSig_V_Start();
    ADC_DelSig_V_StartConvert();
    
    //start pwm
    PWM_BUCK_Start();
    

    
    DFB_1_Start();
    DFB_1_SetCoherency(DFB_1_STGA_KEY_MID | DFB_1_STGB_KEY_MID | DFB_1_HOLDA_KEY_MID | DFB_1_HOLDB_KEY_MID);	
    
    //DFB_1_SetCoherency(DFB_1_STGA_KEY_LOW | DFB_1_STGB_KEY_LOW | DFB_1_HOLDA_KEY_LOW | DFB_1_HOLDB_KEY_LOW);	
    DMA_Init();
    //DFB_1_LoadDataRAMA(&scalar, (uint32 *)DFB_1_DA_RAM_PTR, 1u);
    //DFB_1_LoadInputValue(1, 0x1FFFFF);
    CyDelay(300);
    DFB_1_SetSemaphores(DFB_1_SEM1);
    //unfolder register
    Control_Reg_1_Write(0);
    
    //UART communication 
    UART_1_Start();
    
    //sinptr = sineLUT;

    //CyDelay(5000);//delay
    
    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
    
    
    
    for(;;)
    {
        
        
        //LCD_Char_1_Position(1u, 0u);
        //LCD_Char_1_PrintInt16(E[0]);
        //LCD_Char_1_PrintString(tstr);
        
        LCD_Char_1_Position(1u,0u);
        
        //qur=sqrt(qur);
        LCD_Char_1_PrintInt16(buffvolt);
        LCD_Char_1_PutChar(' ');
        //LCD_Char_1_PrintInt16(varray[0]);
        LCD_Char_1_PrintInt16(rmsvolt>>16);
        LCD_Char_1_PrintInt16(rmsvolt);
        
        DFB_1_Init();
        DFB_1_Enable();
        CyDelay(100);//delay
        
        DFB_1_SetSemaphores(DFB_1_SEM1);
        
    }
}


/********************************************************************************
* Function Name: DMA_Init
*******************************************************************************
*
* Summary:
*  This function performs DMA_IN_A and DMA_OUT_A initialization.
*
* Parameters:
*	void
*
* Return:
*	void
*
*******************************************************************************/
void DMA_Init(void)
{	
    /* DMA_IN_A */
    dma_stga_in_td = CyDmaTdAllocate();
    
    dma_stga_in_channel = DMA_IN_A_DmaInitialize(4u, 0u, HI16((uint32)&varray[0u]), HI16((uint32)DFB_1_STAGEA_PTR));
    CyDmaTdSetConfiguration(dma_stga_in_td, 32u, DMA_INVALID_TD, (DMA_IN_A__TD_TERMOUT_EN |
                                                                                    TD_INC_SRC_ADR));
    
	CyDmaTdSetAddress(dma_stga_in_td, LO16((uint32)&varray[0u]), LO16((uint32)DFB_1_STAGEA_PTR));
	CyDmaChSetInitialTd(dma_stga_in_channel, dma_stga_in_td);
	CyDmaChEnable(dma_stga_in_channel, 1u);
	
    


    
    DMA_OUT_A_Chan = DMA_OUT_A_DmaInitialize(DMA_OUT_A_BYTES_PER_BURST, DMA_OUT_A_REQUEST_PER_BURST, 
        HI16(DMA_OUT_A_SRC_BASE), HI16(DMA_OUT_A_DST_BASE));
    DMA_OUT_A_TD[0] = CyDmaTdAllocate();
    CyDmaTdSetConfiguration(DMA_OUT_A_TD[0], 4, DMA_INVALID_TD, TD_INC_SRC_ADR | TD_INC_DST_ADR);
    CyDmaTdSetAddress(DMA_OUT_A_TD[0], LO16((uint32)DFB_1_HOLDA_PTR), LO16((uint32)rmsvolt));
    CyDmaChSetInitialTd(DMA_OUT_A_Chan, DMA_OUT_A_TD[0]);
    CyDmaChEnable(DMA_OUT_A_Chan, 1);
    /* DMA_OUT_A */
    /*
    dma_stga_out_td = CyDmaTdAllocate();
    #if (CY_PSOC3)
	dma_stga_out_channel = DMA_OUT_A_DmaInitialize(2u, 1u, HI16(CYDEV_SRAM_BASE), HI16(CYDEV_SRAM_BASE));
    CyDmaTdSetConfiguration(dma_stga_out_td, (COLUMN * ROW * 2u), DMA_INVALID_TD, (DMA_OUT_A__TD_TERMOUT_EN | 
                                                                                    TD_SWAP_EN | TD_INC_DST_ADR));    
	#elif (CY_PSOC5)
    dma_stga_out_channel = DMA_OUT_A_DmaInitialize(2u, 1u, HI16((uint32)DFB_HOLDA_PTR), HI16((uint32)&OutMass[0u][0u]));	
    CyDmaTdSetConfiguration(dma_stga_out_td, (COLUMN * ROW * 2u), DMA_INVALID_TD, (DMA_OUT_A__TD_TERMOUT_EN | 
                                                                                   TD_INC_DST_ADR));
    #endif	
    CyDmaTdSetAddress(dma_stga_out_td, LO16((uint32)DFB_HOLDA_PTR), LO16((uint32)&OutMass[0u][0u]));
	CyDmaChSetInitialTd(dma_stga_out_channel, dma_stga_out_td);
	CyDmaChEnable(dma_stga_out_channel, 1u);
    */
}