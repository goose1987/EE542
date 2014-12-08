/*******************************************************************************
* File Name: DFB_1.c
* Version 1.20
*
* Description:
*  This file provides the API source code for the DFB component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "DFB_1.h"

static void DFB_1_LoadReg32(reg32 regAddress[], const uint32 source[], uint8 count);
static void DFB_1_ZeroReg32(reg32 regAddress[], uint8 count);

uint8 DFB_1_initVar = 0u;


/*******************************************************************************
* Function Name: DFB_1_LoadReg32
********************************************************************************
* 
* Summary:
*  This function loads initial values/data to appropriate registers.
*
* Parameters:
*  reg32 regAddress[]: register address;
*  const uint32 source[]: data for load;
*  uint8 count: number of 32-bit registers for load.
*
* Return:
*  None.
*
* Note:
*  Data loads starts from "regAddress" address and affects on "count" numbers of
*  successive registers.
*
*******************************************************************************/
static void DFB_1_LoadReg32(reg32 regAddress[], const uint32 source[], uint8 count)
{
    uint8 i = 0u;
    
    while (count > 0u)
    {
        CY_SET_REG32(& regAddress[i], source[i]);
        count--;
        i++;
    }
}


/*******************************************************************************
* Function Name: DFB_1_ZeroReg32
********************************************************************************
* 
* Summary:
*  This function zeroize registers.
*
* Parameters:
*  reg32 regAddress[]: register address;
*  uint8 count: number of 32-bit registers for zeroing.
*
* Return:
*  None.
*
* Note:
*  Zeroing starts from "regAddress" address and affects on "count" numbers of
*  successive registers.
*
*******************************************************************************/
static void DFB_1_ZeroReg32(reg32 regAddress[], uint8 count)
{
    uint8 i = 0u;
    
    while (count > 0u)
    {
        CY_SET_REG32(& regAddress[i], 0u);
        count--;
        i++;
    }
}


/*******************************************************************************
* Function Name: DFB_1_Init
********************************************************************************
* 
* Summary:
*  This function initializes or restores default the DFB component configuration
*  provided with customizer:
*   powers on DFB(PM_ACT_CFG), power on the RAM(DFB_RAM_EN),
*   moves CSA/CSB/FSM/DataA/DataB/ACU data to the DFB ram using an 8051/ARM
*   core,
*   changes RAM DIR to DFB,
*   sets interrupt mode,
*   sets DMA mode,
*   sets DSI outputs,
*   clears all semaphore bits an pending interrupts.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  All registers will be reset to their initial values. This will reinitializes
*  the component. This function turns off Run bit and enables power to the DFB
*  block.
*  Program loading takes ~6 ms.
*
*******************************************************************************/
void DFB_1_Init(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Powers on DFB block */
    DFB_1_PM_ACT_CFG_REG |= DFB_1_PM_ACT_MSK;
    /* Enables DFB block in Alternate Active (Standby) mode */
    DFB_1_PM_STBY_CFG_REG |= DFB_1_PM_STBY_MSK;

    CyExitCriticalSection(enableInterrupts);

    /* Turns off Run Bit */
    DFB_1_CR_REG &= (uint8) (~DFB_1_RUN_MASK);
    /* Powers up the DFB RAMS */
    DFB_1_RAM_EN_REG = DFB_1_RAM_DIR_BUS;
    /* Puts DFB RAM on the bus */
    DFB_1_RAM_DIR_REG = DFB_1_RAM_DIR_BUS;

    /* Clears all DFB RAM */
    DFB_1_ZeroReg32(DFB_1_DA_RAM_PTR, DFB_1_DA_RAM_SIZE);
    DFB_1_ZeroReg32(DFB_1_DB_RAM_PTR, DFB_1_DB_RAM_SIZE);
    DFB_1_ZeroReg32(DFB_1_CSA_RAM_PTR, DFB_1_CSA_RAM_SIZE);
    DFB_1_ZeroReg32(DFB_1_CSB_RAM_PTR, DFB_1_CSB_RAM_SIZE);
    DFB_1_ZeroReg32(DFB_1_ACU_RAM_PTR, DFB_1_ACU_RAM_SIZE);
    DFB_1_ZeroReg32(DFB_1_CFSM_RAM_PTR, DFB_1_CFSM_RAM_SIZE);

    /* Writes DFB RAMs */
    /* Control Store RAMs */
    #if (DFB_1_OPTIMIZE_ASSEMBLY)
        DFB_1_LoadReg32(DFB_1_CSA_RAM_PTR, DFB_1_cstoreA,
                                    DFB_1_CSA_RAM_SIZE_CUR);
        DFB_1_LoadReg32(DFB_1_CSB_RAM_PTR, DFB_1_cstoreB,
                                    DFB_1_CSB_RAM_SIZE_CUR);
    #else
        DFB_1_LoadReg32(DFB_1_CSA_RAM_PTR, DFB_1_control,
                                    DFB_1_CSA_RAM_SIZE_CUR);
        DFB_1_LoadReg32(DFB_1_CSB_RAM_PTR, DFB_1_control,
                                    DFB_1_CSB_RAM_SIZE_CUR);
    #endif /* DFB_1_OPTIMIZE_ASSEMBLY */

    /* Loads initial data to Data RAMs */
    DFB_1_LoadReg32(DFB_1_DA_RAM_PTR, DFB_1_data_a, DFB_1_DA_RAM_SIZE_CUR);
    DFB_1_LoadReg32(DFB_1_DB_RAM_PTR, DFB_1_data_b, DFB_1_DB_RAM_SIZE_CUR);
    /* Loads initial data to ACU RAM */
    DFB_1_LoadReg32(DFB_1_ACU_RAM_PTR, DFB_1_acu, DFB_1_ACU_RAM_SIZE_CUR);
    /* Loads initial data to CFSM RAM */
    DFB_1_LoadReg32(DFB_1_CFSM_RAM_PTR, DFB_1_cfsm,
                                DFB_1_CFSM_RAM_SIZE_CUR);

    /* Takes DFB RAM off the bus */
    DFB_1_RAM_DIR_REG = DFB_1_RAM_DIR_DFB;

    /* Sets up interrupt and DMA events */
    DFB_1_SetInterruptMode(DFB_1_INIT_INTERRUPT_MODE);
    DFB_1_SetDMAMode(DFB_1_INIT_DMA_MODE);

    /* Sets up internal signals, which will be mapped to the DSI outputs */
    DFB_1_SetOutput1Source(DFB_1_INIT_OUT1_SOURCE);
    DFB_1_SetOutput2Source(DFB_1_INIT_OUT2_SOURCE);

    /* Clears any pending interrupts and semaphore bits */
    DFB_1_SR_REG = 0xFFu;
}


/*******************************************************************************
* Function Name: DFB_1_Enable
********************************************************************************
*
* Summary:
*  This function enables the DFB hardware block, sets the DFB run bit and powers
*  on the DFB block.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_Enable(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Powers on DFB block */
    DFB_1_PM_ACT_CFG_REG |= DFB_1_PM_ACT_MSK;
    /* Enables DFB block in Alternate Active (Standby) mode */
    DFB_1_PM_STBY_CFG_REG |= DFB_1_PM_STBY_MSK;

    CyExitCriticalSection(enableInterrupts);
    
    /* Powers up the DFB RAMS */
    DFB_1_RAM_EN_REG = DFB_1_RAM_DIR_BUS;
    /* Turns on Run Bit */
    DFB_1_CR_REG |= DFB_1_RUN_MASK;
}


/*******************************************************************************
* Function Name: DFB_1_Start
********************************************************************************
*
* Summary:
*  This function initializes and enables the DFB component using the DFB_Init()
*  and DFB_Enable() functions.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  DFB_1_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void DFB_1_Start(void) 
{
    if (DFB_1_initVar == 0u)
    {
        DFB_1_Init();
        DFB_1_initVar = 1u;
    }

    DFB_1_Enable();
}


/*******************************************************************************
* Function Name: DFB_1_Stop
********************************************************************************
*
* Summary:
*  This function turns off the run bit. If DMA control is used to feed the
*  channels, function allows arguments to turn off one of the TD channels off.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Side Effects:
*  Disables power to the DFB Core.
*
*******************************************************************************/
void DFB_1_Stop(void) 
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    /* Powers off DFB */
    DFB_1_PM_ACT_CFG_REG &= (uint8) (~DFB_1_PM_ACT_MSK);
    /* Disables DFB block in Alternate Active (Standby) mode */
    DFB_1_PM_STBY_CFG_REG &= (uint8) (~DFB_1_PM_STBY_MSK);

    CyExitCriticalSection(enableInterrupts);

    /* Turns off Run Bit */
    DFB_1_CR_REG &= (uint8) (~DFB_1_RUN_MASK);
}


/*******************************************************************************
* Function Name: DFB_1_Pause
********************************************************************************
*
* Summary:
*  This function pauses DFB and enables writing to the DFB RAM:
*   turns off the Run bit,
*   connects the DFB RAM to the data bus,
*   clears the DFB run bit and passes the control of all DFB RAMs onto bus.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_Pause(void) 
{
     /* Turns off Run Bit */
    DFB_1_CR_REG &= (uint8) (~DFB_1_RUN_MASK);
     /* Puts DFB RAM on the bus */
    DFB_1_RAM_DIR_REG = DFB_1_RAM_DIR_BUS;
}


/*******************************************************************************
* Function Name: DFB_1_Resume
********************************************************************************
*
* Summary:
*  This function disables writing to the DFB RAM, clear any pending interrupts,
*  disconnects the DFB RAM from the data bus, and runs the DFB.
*  It passes the control of all DFB RAM to the DFB and then sets the run bit.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_Resume(void) 
{
    /* Takes DFB RAM off the bus */
    DFB_1_RAM_DIR_REG = DFB_1_RAM_DIR_DFB;
    /* Clears any pending interrupts */
    DFB_1_SR_REG = 0xFFu;
    /* Turns on Run Bit */
    DFB_1_CR_REG |= DFB_1_RUN_MASK;
}


/*******************************************************************************
* Function Name: DFB_1_SetCoherency
********************************************************************************
*
* Summary:
*  This function sets the coherency key to low/mid/high byte based on the
*  coherencyKey parameter that is passed to the DFB.
*  Function allows you to select which of the 3 bytes of each of the STAGEA,
*  STAGEB, HOLDA and HOLDB will be used as the Key Coherency Byte. Coherency
*  refers to the HW added to this block to protect against malfunctions of the
*  block in cases where register fields are wider than the bus access, leaving
*  intervals in time when fields are partially written/read (incoherent). The
*  Key Coherency Byte is the SW's way of telling the HW which byte of the field
*  will be written/read last when an update to the field is desired. When the
*  Key byte is written/read, the field is flagged coherent. If any other byte
*  is written or read, the field is flagged incoherent.
*
* Parameters:
*  uint8 coherencyKeyByte: specifies bits in the DFB Coherency Register.
*   Sets the Key Coherency Byte of the Staging A register
*    Define                             Description
*     DFB_1_STGA_KEY_LOW      Key Byte is low byte.
*     DFB_1_STGA_KEY_MID      Key Byte is med byte.
*     DFB_1_STGA_KEY_HIGH     Key Byte is high byte.
*   Sets the Key Coherency Byte of the Staging B register
*    Define                             Description
*     DFB_1_STGB_KEY_LOW      Key Byte is low byte.
*     DFB_1_STGB_KEY_MID      Key Byte is med byte.
*     DFB_1_STGB_KEY_HIGH     Key Byte is high byte.
*   Sets the Key Coherency Byte of the Holding A register
*    Define                             Description
*     DFB_1_HOLDA_KEY_LOW     Key Byte is low byte.
*     DFB_1_HOLDA_KEY_MID     Key Byte is med byte.
*     DFB_1_HOLDA_KEY_HIGH    Key Byte is high byte.
*   Sets the Key Coherency Byte of the Holding B register
*    Define                             Description
*     DFB_1_HOLDB_KEY_LOW     Key Byte is low byte.
*     DFB_1_HOLDB_KEY_MID     Key Byte is med byte.
*     DFB_1_HOLDB_KEY_HIGH    Key Byte is high byte.
*
* Return:
*  None.
*
* Note:
*  Default key byte configuration for Staging A and B, and Holding A and B
*  registers is high byte.
*
* Side Effects:
*  Coherency affects data loading using the LoadInputValue() function and
*  data retrieval using the GetOutputValue() function.
*
*******************************************************************************/
void DFB_1_SetCoherency(uint8 coherencyKeyByte) 
{
    DFB_1_COHER_REG = coherencyKeyByte;
}


/*******************************************************************************
* Function Name: DFB_1_SetDalign
********************************************************************************
*
* Summary:
*  This feature allows 9- to 16-bit input and output samples to travel as 16-bit
*  values on the AHB bus. These bits when set high cause an 8-bit shift in the
*  data to all access of the corresponding Staging and Holding registers.
*  Because the DFB datapath is inherently MSB aligned, it is convenient to the
*  System SW to align values on bits 23:8 of the Staging and Holding register
*  to bits 15:0 of the bus. A read of this register produces the last value
*  written to this register.
*
* Parameters:
*  uint8 dalignKeyByte: specifies bits in the DFB Data Alignment Register.
*   Shifts the write left by a byte.
*    Define                               Description
*     DFB_1_STGA_DALIGN_LOW     Writes normally.
*     DFB_1_STGA_DALIGN_HIGH    Writes shifted left by 8-bits.
*   Shifts the write left by a byte.
*    Define                               Description
*     DFB_1_STGB_DALIGN_LOW     Writes normally.
*     DFB_1_STGB_DALIGN_HIGH    Writes shifted left by 8-bits.
*   Shifts the read right by a byte.
*    Define                               Description
*     DFB_1_HOLDA_DALIGN_LOW     Reads normally.
*     DFB_1_HOLDA_DALIGN_HIGH    Reads shifted right by 8-bits.
*   Shifts the read right by a byte.
*    Define                               Description
*     DFB_1_HOLDB_DALIGN_LOW     Reads normally.
*     DFB_1_HOLDB_DALIGN_HIGH    Reads shifted right by 8-bits.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_SetDalign(uint8 dalignKeyByte) 
{
    DFB_1_DALIGN_REG = dalignKeyByte;
}


/*******************************************************************************
* Function Name: DFB_1_LoadDataRAMA
********************************************************************************
*
* Summary:
*  This function loads data to DFB RAM A memory.
*
* Parameters:
*  const int32 ptr[]: pointer on data source for load;
*  uint32     addr[]: start address for loading the data in DFB RAM A;
*  uint8        size: number of data words to load.
*
* Return:
*  DFB_1_SUCCESS - Loading data is successful.
*  DFB_1_ADDRESS_OUT_OF_RANGE - error code, indicates that the
*  address is out of range.
*  DFB_1_DATA_OUT_OF_RANGE - error code, indicates a data overflow
*  error.
*
* Side Effects:
*  This API doesn't stop the DFB if it is already started. Hence, recommended
*  method is to call Init() API, then LoadDataRAMA() API and then Enable() API.
*
*******************************************************************************/
uint8 DFB_1_LoadDataRAMA(const int32 ptr[], uint32 addr[], uint8 size)
     
{
    uint8 result = DFB_1_SUCCESS;
    uint8 i = 0u;

    if (((& addr[0u]) < DFB_1_DA_RAM_PTR) || ((& addr[0u]) > DFB_1_DA_RAM_LAST_ELEM_PTR))
    {
        result = DFB_1_ADDRESS_OUT_OF_RANGE;
    }
    else if ((size == 0u) || ((& addr[size - 1u]) > DFB_1_DA_RAM_LAST_ELEM_PTR))
    {
        result = DFB_1_DATA_OUT_OF_RANGE;
    }
    else
    {
        /* Puts DFB RAM on the bus */
        DFB_1_RAM_DIR_REG |= DFB_1_RAM_DPA_DIR;
        while (size > 0u)
        {
            CY_SET_REG32((reg32 *) (& addr[i]), (uint32) ptr[i]);
            size--;            
            i++;
        }
        /* Takes DFB RAM off the bus */
        DFB_1_RAM_DIR_REG &= (uint8) (~DFB_1_RAM_DPA_DIR);
    }

    return (result);
}


/*******************************************************************************
* Function Name: DFB_1_LoadDataRAMB
********************************************************************************
*
* Summary:
*  This function loads data to DFB RAM B memory.
*
* Parameters:
*  const int32 ptr[]: pointer on data source for load;
*  uint32     addr[]: start addres for loading the data in DFB RAM B;
*  uint8        size: number of data words to load.
*
* Return:
*  DFB_1_SUCCESS - Loading data is successful.
*  DFB_1_ADDRESS_OUT_OF_RANGE - error code, indicates that the
*  address is out of range.
*  DFB_1_DATA_OUT_OF_RANGE - error code, indicates data overflow
*  error.
*
* Side Effects:
*  This API doesn't stop the DFB if it is already started. Hence, recommended
*  method is to call Init() API, then LoadDataRAMB() API and then Enable() API.
*
*******************************************************************************/
uint8 DFB_1_LoadDataRAMB(const int32 ptr[], uint32 addr[], uint8 size)
     
{
    uint8 result = DFB_1_SUCCESS;
    uint8 i = 0u;

    if (((& addr[0u]) < DFB_1_DB_RAM_PTR) || ((& addr[0u]) > DFB_1_DB_RAM_LAST_ELEM_PTR))
    {
        result = DFB_1_ADDRESS_OUT_OF_RANGE;
    }
    else if ((size == 0u) || ((& addr[size - 1u]) > DFB_1_DB_RAM_LAST_ELEM_PTR))
    {
        result = DFB_1_DATA_OUT_OF_RANGE;
    }
    else
    {
        /* Puts DFB RAM on the bus */
        DFB_1_RAM_DIR_REG |= DFB_1_RAM_DPB_DIR;
        while (size > 0u)
        {
            CY_SET_REG32((reg32 *) (& addr[i]), (uint32) ptr[i]);
            size--;
            i++;
        }
        /* Takes DFB RAM off the bus */
        DFB_1_RAM_DIR_REG &= (uint8) (~DFB_1_RAM_DPB_DIR);
    }

    return (result);
}


/*******************************************************************************
* Function Name: DFB_1_LoadInputValue
********************************************************************************
*
* Summary:
*  This function loads input value in selected channel.
*
* Parameters:
*  channel: Use either DFB_1_CHANNEL_A (1) or
*           DFB_1_CHANNEL_B (0) asarguments to the function;
*  sample: The 24-bit, right justified input sample.
*
* Return:
*  None.
*
* Note:
*  The write order is important. When the high byte is loaded, the DFB sets
*  the input ready bit. Pay attention to byte order if coherency or data
*  alignment is changed.
*
*******************************************************************************/
void DFB_1_LoadInputValue(uint8 channel, int32 sample) 
{
    uint32 value;

    value = (uint32) sample;

    /* Writes the STAGE-"H" reg last as it signals a complete wrote to the DFB.*/
    if (channel == DFB_1_CHANNEL_A)
    {
        DFB_1_STAGEA_REG  = (uint8) value;
        DFB_1_STAGEAM_REG = (uint8) (value >> 8u);
        DFB_1_STAGEAH_REG = (uint8) (value >> 16u);
    }
    else if (channel == DFB_1_CHANNEL_B)
    {
        DFB_1_STAGEB_REG  = (uint8) value;
        DFB_1_STAGEBM_REG = (uint8) (value >> 8u);
        DFB_1_STAGEBH_REG = (uint8) (value >> 16u);
    }
    else
    {
        /* No value is loaded on bad channel input */
    }
}


/*******************************************************************************
* Function Name: DFB_1_GetOutputValue
********************************************************************************
*
* Summary:
*  This function gets the value from one of the DFB Output Holding Registers.
*
* Parameters:
*  channel: Use either DFB_1_CHANNEL_A (1) or
*           DFB_1_CHANNEL_B (0) as arguments to the function.
*
* Return:
*  The current output value in the chosen channel's holding register. This is
*  a 24-bit number packed into the least-significant 3 bytes of the output word
*  or 0xFF000000 for invalid channel numbers
*
* Note:
*  Because of the architecture of the DFB, any value read from the Holding A or
*  B registers will be MSB aligned unless shifted otherwise by the Datapath
*  shifter. Pay attention to byte order if coherency or data alignment is
*  changed.
*
*******************************************************************************/
int32 DFB_1_GetOutputValue(uint8 channel) 
{
    uint8 data0;
    uint8 data1;
    uint8 data2;
    uint8 data3;
    uint32 output;

    /* Reads the HOLD-"H" reg last as it signals a complete read to the DFB.*/
    if (channel == DFB_1_CHANNEL_A)
    {
        data0 = DFB_1_HOLDA_REG;
        data1 = DFB_1_HOLDAM_REG;
        data2 = DFB_1_HOLDAH_REG;
        data3 = ((data2 & 0x80u) == 0x80u) ? 0xFFu : 0x00u;
    }
    else if (channel == DFB_1_CHANNEL_B)
    {
        data0 = DFB_1_HOLDB_REG;
        data1 = DFB_1_HOLDBM_REG;
        data2 = DFB_1_HOLDBH_REG;
        data3 = ((data2 & 0x80u) == 0x80u) ? 0xFFu : 0x00u;
    }
    else
    {
        data0 = 0x00u;
        data1 = 0x00u;
        data2 = 0x00u;
        data3 = 0xFFu;
    }

    output = ((((((uint32) data3 << 8u) | data2) << 8u) | data1) << 8u) | data0;

    return ((int32) output);
}


/*******************************************************************************
* Function Name: DFB_1_SetInterruptMode
********************************************************************************
*
* Summary:
*  This function assigns the events which will trigger a DFB interrupt to be
*  triggered.
*
* Parameters:
*  events: Bits [0:5] of events represent the events that trigger DFB
*          interrupts.
*    Define                    Description
*     DFB_1_HOLDA    Interrupt is generated each time new valid data
*                               is written into the output Holding register A;
*     DFB_1_HOLDB    Interrupt is generated each time new valid data
*                               is written into the output Holding register B;
*     DFB_1_SEMA0    Interrupt is generated each time a '1' is
*                               written into the semaphore register bit 0;
*     DFB_1_SEMA1    Interrupt is generated each time a '1' is
*                               written into the semaphore register bit 1;
*     DFB_1_SEMA2    Interrupt is generated each time a '1' is
*                               written into the semaphore register bit 2.
*
* Return:
*  None.
*
* Note:
*  Do not configure semaphore 0 and semaphore 1 for both a DMA request and for
*  an interrupt event. This is because, after one clock cycle, the system
*  automatically clears any semaphore that triggered a DMA request.
*
*******************************************************************************/
void DFB_1_SetInterruptMode(uint8 events) 
{
    DFB_1_INT_CTRL_REG = events & DFB_1_EVENT_MASK;
}


/*******************************************************************************
* Function Name: DFB_1_GetInterruptSource
********************************************************************************
*
* Summary:
*  This function looks at the DFB_1_SR register to see which
*  interrupt sources have been triggered.
*
* Parameters:
*  None.
*
* Return:
*  uint8 value in which bits [0:5] of represent the events that triggered the
*  DFB interrupt.
*    Define                    Description
*     DFB_1_HOLDA    Holding register A is a source of the current
*                               interrupt;
*     DFB_1_HOLDB    Holding register B is a source of the current
*                               interrupt;
*     DFB_1_SEMA0    Semaphore register bit 0 is a source of the
*                               current interrupt;
*     DFB_1_SEMA1    Semaphore register bit 1 is a source of the
*                               current interrupt;
*     DFB_1_SEMA2    Semaphore register bit 2 is a source of the
*                               current interrupt.
*
*******************************************************************************/
uint8 DFB_1_GetInterruptSource(void) 
{
    /* Shifts the event bits down to [0:5] */
    return ((uint8) (DFB_1_SR_REG >> DFB_1_SR_EVENT_SHIFT));
}


/*******************************************************************************
* Function Name: DFB_1_ClearInterrupt
********************************************************************************
*
* Summary:
*  This function clears the interrupt request.
*
* Parameters:
*  interruptMask: Mask of interrupts to clear.
*    Define                    Description
*     DFB_1_HOLDA    Clear interrupt from Holding register A.
*                               (Reading the Holding register A also clears this
*                                bit);
*     DFB_1_HOLDB    Clear interrupt from Holding register B.
*                               (Reading the Holding register B also clears this
*                                bit);
*     DFB_1_SEMA0    Clear interrupt from semaphore register bit 0;
*     DFB_1_SEMA1    Clear interrupt from semaphore register bit 1;
*     DFB_1_SEMA2    Clear interrupt from semaphore register bit 2.
*
* Return:
*  None.
*
* Note:
*  Clearing semaphore interrupts also clears semaphore bits.
*
*******************************************************************************/
void DFB_1_ClearInterrupt(uint8 interruptMask) 
{
    DFB_1_SR_REG &= (uint8) (interruptMask << DFB_1_SR_EVENT_SHIFT);
}


/*******************************************************************************
* Function Name: DFB_1_SetDMAMode
********************************************************************************
*
* Summary:
*  This function assigns the events that trigger a DMA request for the DFB.
*  Two different DMA requests that can be triggered.
*
* Parameters:
*  events: A set of 4 bits which configure what event, if any, triggers a DMA
*          request for the DFB.
*   DMA Request 1:
*    Define                                 Description
*    DFB_1_DMAREQ1_DISABLED       No request will be generated;
*    DFB_1_DMAREQ1_HOLDA          Output value ready in the holding
                                             register on channel A;
*    DFB_1_DMAREQ1_SEM0           Semaphore 0;
*    DFB_1_DMAREQ1_SEM1           Sempahore 1.
*   DMA Request 2:
*    Define                                 Description
*    DFB_1_DMAREQ2_DISABLED       No request will be generated;
*    DFB_1_DMAREQ2_HOLDB          Output value ready in the holding
                                             register on channel B;
*    DFB_1_DMAREQ2_SEM0           Semaphore 0;
*    DFB_1_DMAREQ2_SEM1           Sempahore 1.
*
* Return:
*  None.
*
* Note:
*  Do not configure semaphore 0 and semaphore 1 for both a DMA request and for
*  an interrupt event. This is because, after one clock cycle, the system
*  automatically clears any semaphore that triggered a DMA request.
*
*******************************************************************************/
void DFB_1_SetDMAMode(uint8 events) 
{
    DFB_1_DMA_CTRL_REG = events & DFB_1_DMA_CTRL_MASK;
}


/*******************************************************************************
* Function Name: DFB_1_SetSemaphore
********************************************************************************
*
* Summary:
*  This function sets semaphores specified with a 1.
*
* Parameters:
*  mask: mask specifying the bits to set.
*    Define                          Description
*     DFB_1_SEMAPHORE0     Semaphore 0;
*     DFB_1_SEMAPHORE1     Semaphore 1;
*     DFB_1_SEMAPHORE2     Semaphore 2.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_SetSemaphores(uint8 mask) 
{
    DFB_1_SEM_REG = (uint8) ((mask & DFB_1_SEM_MASK) << DFB_1_SEM_ENABLE_SHIFT) |
                                 DFB_1_SEM_MASK;
}


/*******************************************************************************
*  Function Name: DFB_1_GetSempahores
********************************************************************************
*
* Summary:
*  This function checks the current status of the DFB semaphores and return that
*  value.
*
* Parameters:
*  None.
*
* Return:
*  uint8 value between 0 and 7 where bit 0 represents semaphore 0 and so on.
*    Define                          Description
*     DFB_1_SEMAPHORE0     Semaphore 0;
*     DFB_1_SEMAPHORE1     Semaphore 1;
*     DFB_1_SEMAPHORE2     Semaphore 2.
*
*******************************************************************************/
uint8 DFB_1_GetSemaphores(void) 
{
    /* Masked the valide bits in case the reserved bits in SEM_REG [4 and 7] get used for something */
    return (DFB_1_SEM_REG & DFB_1_SEM_MASK);
}


/*******************************************************************************
*  Function Name: DFB_1_ClearSemaphore
********************************************************************************
*
* Summary:
*  This function clears semaphore bits specified with a 1.
*
* Parameters:
*  mask: mask specifying the bits to clear.
*    Define                          Description
*     DFB_1_SEMAPHORE0     Semaphore 0;
*     DFB_1_SEMAPHORE1     Semaphore 1;
*     DFB_1_SEMAPHORE2     Semaphore 2.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_ClearSemaphores(uint8 mask) 
{
    /* Writes the semaphore register: Clears the semaphores masked */
    DFB_1_SEM_REG = (uint8) ((mask & DFB_1_SEM_MASK) << DFB_1_SEM_ENABLE_SHIFT);
}


/*******************************************************************************
* Function Name: DFB_1_SetOutput1Source
********************************************************************************
*
* Summary:
*  This function allows you to choose which internal signal will be mapped to
*  the DSI output 1.
*
* Parameters:
*  source: internal signal which is mapped to the output global signal 1.
*   Signal                      Description
*    DFB_1_DFB_RUN    DFB RUN Bit. This is the same bit as the RUN
*                                bit in the DFB_CR register.
*    DFB_1_SEM0       Semaphore Bit 0.
*    DFB_1_SEM1       Semaphore Bit 1.
*    DFB_1_DFB_INTR   DFB Interrupt. This is the same signal as the
*                                primary DFB Interrupt output signal.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_SetOutput1Source(uint8 source) 
{
    DFB_1_DSI_CTRL_REG = (DFB_1_DSI_CTRL_REG & DFB_1_DFB_GBL1_OUT_MASK) | source;
}


/*******************************************************************************
* Function Name: DFB_1_SetOutput2Source
********************************************************************************
*
* Summary:
*  This function allows you to choose which internal signal will be mapped to
*  the DSI output 2.
*
* Parameters:
*  source: internal signal which is mapped to the output global signal 2.
*   Signal                      Description
*    DFB_1_SEM2       Semaphore Bit 2.
*    DFB_1_DPSIGN     Datapath Sign. This signal asserts anytime the
*                                 output of the ALU in the Datapath unit is
*                                 negative. It will remain high for each cycle
*                                 this condition is true.
*    DFB_1_DPTHRESH   Datapath Threshold Crossed. This signal
*                                 asserts anytime the threshold of 0 is crossed
*                                 in the ALU when one of the following
*                                 instructions is executing: TDECA, TSUBA,
*                                 TSUBB, TADDABSA, TADDABSB. It will remain high
*                                 for each cycle this condition is true.
*    DFB_1_DPEQ       Datapath ALU=0. This signal asserts high when
*                                 the output of the ALU in the Datapath unit
*                                 equals 0 and one of the following ALU commands
*                                 is executing: TDECA, TSUBA, TSUBB, TADDABSA,
*                                 TADDABSB. It will remain high for each cycle
*                                 this condition is true.
*
* Return:
*  None.
*
*******************************************************************************/
void DFB_1_SetOutput2Source(uint8 source) 
{
    DFB_1_DSI_CTRL_REG = (DFB_1_DSI_CTRL_REG & DFB_1_DFB_GBL2_OUT_MASK) | source;
}


/* [] END OF FILE */
