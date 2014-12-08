/*******************************************************************************
* File Name: DFB_1.h
* Version 1.20
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the DFB Component.
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

#if !defined(CY_DFB_DFB_1_H) /* DFB Header File */
#define CY_DFB_DFB_1_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component DFB_v1_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

extern uint8 DFB_1_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define DFB_1_OPTIMIZE_ASSEMBLY      (0u)
#define DFB_1_INIT_INTERRUPT_MODE    (1u)
#define DFB_1_INIT_DMA_MODE          (1u)
#define DFB_1_INIT_OUT1_SOURCE       (2u)
#define DFB_1_INIT_OUT2_SOURCE       (0u)

/* Sizes of current DFB program */
#define DFB_1_DA_RAM_SIZE_CUR        (0x01u)
#define DFB_1_DB_RAM_SIZE_CUR        (0x01u)
#define DFB_1_CSA_RAM_SIZE_CUR       (0x07u)
#define DFB_1_CSB_RAM_SIZE_CUR       (0x07u)
#define DFB_1_CFSM_RAM_SIZE_CUR      (0x04u)
#define DFB_1_ACU_RAM_SIZE_CUR       (0x01u)


/***************************************
*     Data Types Definitions
***************************************/

#if (DFB_1_OPTIMIZE_ASSEMBLY)
    extern const uint32 CYCODE DFB_1_cstoreA[DFB_1_CSA_RAM_SIZE_CUR];
    extern const uint32 CYCODE DFB_1_cstoreB[DFB_1_CSB_RAM_SIZE_CUR];
#else
    extern const uint32 CYCODE DFB_1_control[DFB_1_CSA_RAM_SIZE_CUR];
#endif /* DFB_1_OPTIMIZE_ASSEMBLY */

extern const uint32 CYCODE DFB_1_data_a[DFB_1_DA_RAM_SIZE_CUR];
extern const uint32 CYCODE DFB_1_data_b[DFB_1_DB_RAM_SIZE_CUR];
extern const uint32 CYCODE DFB_1_cfsm[DFB_1_CFSM_RAM_SIZE_CUR];
extern const uint32 CYCODE DFB_1_acu[DFB_1_ACU_RAM_SIZE_CUR];

/* Sleep Mode API Support */
typedef struct
{
    uint8  enableState;
} DFB_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void   DFB_1_Init(void) ;
void   DFB_1_Enable(void) ;
void   DFB_1_Start(void) ;
void   DFB_1_Stop(void) ;
void   DFB_1_Pause(void) ;
void   DFB_1_Resume(void) ;
void   DFB_1_SetCoherency(uint8 coherencyKeyByte) ;
void   DFB_1_SetDalign(uint8 dalignKeyByte) ;
uint8  DFB_1_LoadDataRAMA(const int32 ptr[], uint32 addr[], uint8 size)
        ;
uint8  DFB_1_LoadDataRAMB(const int32 ptr[], uint32 addr[], uint8 size)
        ;
void   DFB_1_LoadInputValue(uint8 channel, int32 sample)
        ;
int32  DFB_1_GetOutputValue(uint8 channel) ;
void   DFB_1_SetInterruptMode(uint8 events) ;
uint8  DFB_1_GetInterruptSource(void) ;
void   DFB_1_ClearInterrupt(uint8 interruptMask) ;
void   DFB_1_SetDMAMode(uint8 events) ;
void   DFB_1_SetSemaphores(uint8 mask) ;
uint8  DFB_1_GetSemaphores(void) ;
void   DFB_1_ClearSemaphores(uint8 mask) ;
void   DFB_1_SetOutput1Source(uint8 source) ;
void   DFB_1_SetOutput2Source(uint8 source) ;
void   DFB_1_Sleep(void) ;
void   DFB_1_Wakeup(void) ;
void   DFB_1_SaveConfig(void) ;
void   DFB_1_RestoreConfig(void) ;

/* Macros */
#define DFB_1_ClearInterruptSource(event) \
do { \
    DFB_1_SR_REG = (uint8) (((event) & DFB_1_EVENT_MASK) << DFB_1_SR_EVENT_SHIFT); \
} while (0)


/***************************************
*           API Constants
***************************************/

/* Channel Definitions */
#define DFB_1_CHANNEL_A              (1u)
#define DFB_1_CHANNEL_B              (0u)

/* Sizes of DFB memories */
#define DFB_1_DA_RAM_SIZE            (0x80u)
#define DFB_1_DB_RAM_SIZE            (0x80u)
#define DFB_1_CSA_RAM_SIZE           (0x40u)
#define DFB_1_CSB_RAM_SIZE           (0x40u)
#define DFB_1_CFSM_RAM_SIZE          (0x40u)
#define DFB_1_ACU_RAM_SIZE           (0x10u)

#define DFB_1_SUCCESS                (CYRET_SUCCESS)
#define DFB_1_DATA_OUT_OF_RANGE      (0xFEu)
#define DFB_1_ADDRESS_OUT_OF_RANGE   (0xFFu)


/***************************************
*             Registers
***************************************/

/* RAM memory map offsets */
#define DFB_1_DA_RAM_REG             (* (reg32 *) (DFB_1_DFB__DPA_SRAM_DATA))
#define DFB_1_DA_RAM_PTR             (  (reg32 *) (DFB_1_DFB__DPA_SRAM_DATA))
#define DFB_1_DB_RAM_REG             (* (reg32 *) (DFB_1_DFB__DPB_SRAM_DATA))
#define DFB_1_DB_RAM_PTR             (  (reg32 *) (DFB_1_DFB__DPB_SRAM_DATA))
#define DFB_1_CSA_RAM_REG            (* (reg32 *) (DFB_1_DFB__CSA_SRAM_DATA))
#define DFB_1_CSA_RAM_PTR            (  (reg32 *) (DFB_1_DFB__CSA_SRAM_DATA))
#define DFB_1_CSB_RAM_REG            (* (reg32 *) (DFB_1_DFB__CSB_SRAM_DATA))
#define DFB_1_CSB_RAM_PTR            (  (reg32 *) (DFB_1_DFB__CSB_SRAM_DATA))
#define DFB_1_CFSM_RAM_REG           (* (reg32 *) (DFB_1_DFB__FSM_SRAM_DATA))
#define DFB_1_CFSM_RAM_PTR           (  (reg32 *) (DFB_1_DFB__FSM_SRAM_DATA))
#define DFB_1_ACU_RAM_REG            (* (reg32 *) (DFB_1_DFB__ACU_SRAM_DATA))
#define DFB_1_ACU_RAM_PTR            (  (reg32 *) (DFB_1_DFB__ACU_SRAM_DATA))

#define DFB_1_SEM_REG                (* (reg8 *) DFB_1_DFB__SEMA)
#define DFB_1_SEM_PTR                (  (reg8 *) DFB_1_DFB__SEMA)
#define DFB_1_CR_REG                 (* (reg8 *) DFB_1_DFB__CR)
#define DFB_1_CR_PTR                 (  (reg8 *) DFB_1_DFB__CR)
#define DFB_1_SR_REG                 (* (reg8 *) DFB_1_DFB__SR)
#define DFB_1_SR_PTR                 (  (reg8 *) DFB_1_DFB__SR)
#define DFB_1_INT_CTRL_REG           (* (reg8 *) DFB_1_DFB__INT_CTRL)
#define DFB_1_INT_CTRL_PTR           (  (reg8 *) DFB_1_DFB__INT_CTRL)
#define DFB_1_DMA_CTRL_REG           (* (reg8 *) DFB_1_DFB__DMA_CTRL)
#define DFB_1_DMA_CTRL_PTR           (  (reg8 *) DFB_1_DFB__DMA_CTRL)
#define DFB_1_RAM_DIR_REG            (* (reg8 *) DFB_1_DFB__RAM_DIR)
#define DFB_1_RAM_DIR_PTR            (  (reg8 *) DFB_1_DFB__RAM_DIR)

#define DFB_1_DALIGN_REG             (* (reg8 *) DFB_1_DFB__DALIGN)
#define DFB_1_DALIGN_PTR             (  (reg8 *) DFB_1_DFB__DALIGN)
#define DFB_1_DSI_CTRL_REG           (* (reg8 *) DFB_1_DFB__DSI_CTRL)
#define DFB_1_DSI_CTRL_PTR           (  (reg8 *) DFB_1_DFB__DSI_CTRL)
#define DFB_1_HOLDA_REG              (* (reg8 *) DFB_1_DFB__HOLDA)
#define DFB_1_HOLDA_PTR              (  (reg8 *) DFB_1_DFB__HOLDA)
#define DFB_1_HOLDAH_REG             (* (reg8 *) DFB_1_DFB__HOLDAH)
#define DFB_1_HOLDAH_PTR             (  (reg8 *) DFB_1_DFB__HOLDAH)
#define DFB_1_HOLDAM_REG             (* (reg8 *) DFB_1_DFB__HOLDAM)
#define DFB_1_HOLDAM_PTR             (  (reg8 *) DFB_1_DFB__HOLDAM)
#define DFB_1_HOLDB_REG              (* (reg8 *) DFB_1_DFB__HOLDB)
#define DFB_1_HOLDB_PTR              (  (reg8 *) DFB_1_DFB__HOLDB)
#define DFB_1_HOLDBH_REG             (* (reg8 *) DFB_1_DFB__HOLDBH)
#define DFB_1_HOLDBH_PTR             (  (reg8 *) DFB_1_DFB__HOLDBH)
#define DFB_1_HOLDBM_REG             (* (reg8 *) DFB_1_DFB__HOLDBM)
#define DFB_1_HOLDBM_PTR             (  (reg8 *) DFB_1_DFB__HOLDBM)
#define DFB_1_PM_ACT_CFG_REG         (* (reg8 *) DFB_1_DFB__PM_ACT_CFG)
#define DFB_1_PM_ACT_CFG_PTR         (  (reg8 *) DFB_1_DFB__PM_ACT_CFG)
#define DFB_1_PM_STBY_CFG_REG        (* (reg8 *) DFB_1_DFB__PM_STBY_CFG)
#define DFB_1_PM_STBY_CFG_PTR        (  (reg8 *) DFB_1_DFB__PM_STBY_CFG)
#define DFB_1_RAM_EN_REG             (* (reg8 *) DFB_1_DFB__RAM_EN)
#define DFB_1_RAM_EN_PTR             (  (reg8 *) DFB_1_DFB__RAM_EN)
#define DFB_1_STAGEA_REG             (* (reg8 *) DFB_1_DFB__STAGEA)
#define DFB_1_STAGEA_PTR             (  (reg8 *) DFB_1_DFB__STAGEA)
#define DFB_1_STAGEAH_REG            (* (reg8 *) DFB_1_DFB__STAGEAH)
#define DFB_1_STAGEAH_PTR            (  (reg8 *) DFB_1_DFB__STAGEAH)
#define DFB_1_STAGEAM_REG            (* (reg8 *) DFB_1_DFB__STAGEAM)
#define DFB_1_STAGEAM_PTR            (  (reg8 *) DFB_1_DFB__STAGEAM)
#define DFB_1_STAGEB_REG             (* (reg8 *) DFB_1_DFB__STAGEB)
#define DFB_1_STAGEB_PTR             (  (reg8 *) DFB_1_DFB__STAGEB)
#define DFB_1_STAGEBH_REG            (* (reg8 *) DFB_1_DFB__STAGEBH)
#define DFB_1_STAGEBH_PTR            (  (reg8 *) DFB_1_DFB__STAGEBH)
#define DFB_1_STAGEBM_REG            (* (reg8 *) DFB_1_DFB__STAGEBM)
#define DFB_1_STAGEBM_PTR            (  (reg8 *) DFB_1_DFB__STAGEBM)
#define DFB_1_COHER_REG              (* (reg8 *) DFB_1_DFB__COHER)
#define DFB_1_COHER_PTR              (  (reg8 *) DFB_1_DFB__COHER)

#define DFB_1_DA_RAM_LAST_ELEM_PTR   (  (reg32 *) (DFB_1_DFB__DPB_SRAM_DATA - 4u))
#define DFB_1_DB_RAM_LAST_ELEM_PTR   (  (reg32 *) (DFB_1_DFB__CSA_SRAM_DATA - 4u))


/***************************************
*       Register Constants
***************************************/

#define DFB_1_PM_ACT_MSK             (DFB_1_DFB__PM_ACT_MSK)
#define DFB_1_PM_STBY_MSK            (DFB_1_DFB__PM_STBY_MSK)

#define DFB_1_RUN_MASK               (0x01u)
#define DFB_1_CORECLK_DISABLE        (0x04u)
#define DFB_1_RAM_DIR_BUS            (0x3Fu)
#define DFB_1_RAM_DIR_DFB            (0x00u)
#define DFB_1_RAM_DPA_DIR            (0x10u)
#define DFB_1_RAM_DPB_DIR            (0x20u)

/* Mask for bits within DFB Coherency Register */
#define DFB_1_STGA_KEY_SHIFT         (0x00u)
#define DFB_1_STGB_KEY_SHIFT         (0x02u)
#define DFB_1_HOLDA_KEY_SHIFT        (0x04u)
#define DFB_1_HOLDB_KEY_SHIFT        (0x06u)

#define DFB_1_STGA_KEY_LOW           ((uint8) (0x00u << DFB_1_STGA_KEY_SHIFT))
#define DFB_1_STGA_KEY_MID           ((uint8) (0x01u << DFB_1_STGA_KEY_SHIFT))
#define DFB_1_STGA_KEY_HIGH          ((uint8) (0x02u << DFB_1_STGA_KEY_SHIFT))
#define DFB_1_STGB_KEY_LOW           ((uint8) (0x00u << DFB_1_STGB_KEY_SHIFT))
#define DFB_1_STGB_KEY_MID           ((uint8) (0x01u << DFB_1_STGB_KEY_SHIFT))
#define DFB_1_STGB_KEY_HIGH          ((uint8) (0x02u << DFB_1_STGB_KEY_SHIFT))
#define DFB_1_HOLDA_KEY_LOW          ((uint8) (0x00u << DFB_1_HOLDA_KEY_SHIFT))
#define DFB_1_HOLDA_KEY_MID          ((uint8) (0x01u << DFB_1_HOLDA_KEY_SHIFT))
#define DFB_1_HOLDA_KEY_HIGH         ((uint8) (0x02u << DFB_1_HOLDA_KEY_SHIFT))
#define DFB_1_HOLDB_KEY_LOW          ((uint8) (0x00u << DFB_1_HOLDB_KEY_SHIFT))
#define DFB_1_HOLDB_KEY_MID          ((uint8) (0x01u << DFB_1_HOLDB_KEY_SHIFT))
#define DFB_1_HOLDB_KEY_HIGH         ((uint8) (0x02u << DFB_1_HOLDB_KEY_SHIFT))

/* Mask for bits within DFB Data Alignment Register */
#define DFB_1_STGA_DALIGN_SHIFT      (0x00u)
#define DFB_1_STGB_DALIGN_SHIFT      (0x01u)
#define DFB_1_HOLDA_DALIGN_SHIFT     (0x02u)
#define DFB_1_HOLDB_DALIGN_SHIFT     (0x03u)

#define DFB_1_STGA_DALIGN_LOW        ((uint8) (0x00u << DFB_1_STGA_DALIGN_SHIFT))
#define DFB_1_STGA_DALIGN_HIGH       ((uint8) (0x01u << DFB_1_STGA_DALIGN_SHIFT))
#define DFB_1_STGB_DALIGN_LOW        ((uint8) (0x00u << DFB_1_STGB_DALIGN_SHIFT))
#define DFB_1_STGB_DALIGN_HIGH       ((uint8) (0x01u << DFB_1_STGB_DALIGN_SHIFT))
#define DFB_1_HOLDA_DALIGN_LOW       ((uint8) (0x00u << DFB_1_HOLDA_DALIGN_SHIFT))
#define DFB_1_HOLDA_DALIGN_HIGH      ((uint8) (0x01u << DFB_1_HOLDA_DALIGN_SHIFT))
#define DFB_1_HOLDB_DALIGN_LOW       ((uint8) (0x00u << DFB_1_HOLDB_DALIGN_SHIFT))
#define DFB_1_HOLDB_DALIGN_HIGH      ((uint8) (0x01u << DFB_1_HOLDB_DALIGN_SHIFT))

/* Mask for bits within DFB Interrupt Control and Status Registers */
#define DFB_1_SEM_MASK               (0x07u)
#define DFB_1_SEM_ENABLE_SHIFT       (0x04u)
#define DFB_1_EVENT_MASK             (0x1Fu)
#define DFB_1_SR_EVENT_SHIFT         (0x03u)

#define DFB_1_HOLDA_SHIFT            (0x00u)
#define DFB_1_HOLDB_SHIFT            (0x01u)
#define DFB_1_SEMA0_SHIFT            (0x02u)
#define DFB_1_SEMA1_SHIFT            (0x03u)
#define DFB_1_SEMA2_SHIFT            (0x04u)

#define DFB_1_HOLDA                  ((uint8) (0x01u << DFB_1_HOLDA_SHIFT))
#define DFB_1_HOLDB                  ((uint8) (0x01u << DFB_1_HOLDB_SHIFT))
#define DFB_1_SEMA0                  ((uint8) (0x01u << DFB_1_SEMA0_SHIFT))
#define DFB_1_SEMA1                  ((uint8) (0x01u << DFB_1_SEMA1_SHIFT))
#define DFB_1_SEMA2                  ((uint8) (0x01u << DFB_1_SEMA2_SHIFT))

/* Mask for bits within DFB DMAREQ Control Register */
#define DFB_1_DMA_CTRL_MASK          (0x0Fu)
#define DFB_1_DMAREQ1_DISABLED       (0x00u)
#define DFB_1_DMAREQ1_HOLDA          (0x01u)
#define DFB_1_DMAREQ1_SEM0           (0x02u)
#define DFB_1_DMAREQ1_SEM1           (0x03u)
#define DFB_1_DMAREQ2_DISABLED       (0x00u)
#define DFB_1_DMAREQ2_HOLDB          (0x04u)
#define DFB_1_DMAREQ2_SEM0           (0x08u)
#define DFB_1_DMAREQ2_SEM1           (0x0Cu)

/* Mask for bits within DFB Semaphore Register */
#define DFB_1_SEMAPHORE0             (0x01u)
#define DFB_1_SEMAPHORE1             (0x02u)
#define DFB_1_SEMAPHORE2             (0x04u)

/* Mask for bits within Global Control Register */
#define DFB_1_DFB_RUN                (0x00u)
#define DFB_1_SEM0                   (0x01u)
#define DFB_1_SEM1                   (0x02u)
#define DFB_1_DFB_INTR               (0x03u)
#define DFB_1_SEM2                   (0x00u)
#define DFB_1_DPSIGN                 (0x04u)
#define DFB_1_DPTHRESH               (0x08u)
#define DFB_1_DPEQ                   (0x0Cu)
#define DFB_1_DFB_GBL1_OUT_MASK      (0xFCu)
#define DFB_1_DFB_GBL2_OUT_MASK      (0xF3u)

#endif /* End DFB Header File */


/* [] END OF FILE */

