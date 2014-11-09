/*******************************************************************************
* File Name: SPIS_1_INT.c
* Version 2.50
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Slave
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPIS_1.h"

#if (SPIS_1_RXBUFFERSIZE > 4u)

    extern volatile uint8 SPIS_1_RXBUFFER[];
    extern volatile uint8 SPIS_1_rxBufferRead;
    extern volatile uint8 SPIS_1_rxBufferWrite;
    extern volatile uint8 SPIS_1_rxBufferFull;

#endif /* SPIS_1_RXBUFFERSIZE > 4u */

#if (SPIS_1_TXBUFFERSIZE > 4u)

    extern volatile uint8 SPIS_1_TXBUFFER[];
    extern volatile uint8 SPIS_1_txBufferRead;
    extern volatile uint8 SPIS_1_txBufferWrite;
    extern volatile uint8 SPIS_1_txBufferFull;

#endif /* SPIS_1_TXBUFFERSIZE > 4u */

volatile uint8 SPIS_1_swStatusTx = 0u;
volatile uint8 SPIS_1_swStatusRx = 0u;

/* User code required at start of ISR */
/* `#START SPIS_1_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: SPIS_1_TX_ISR
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPIS_1_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  SPIS_1_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  SPIS_1_TXBUFFER[SPIS_1_TXBUFFERSIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPIS_1_TX_ISR)
{
    /* User code required at start of ISR */
    /* `#START SPIS_1_ISR_TX_START` */

    /* `#END` */

    #if((SPIS_1_InternalTxInterruptEnabled) && (SPIS_1_TXBUFFERSIZE > 4u))
        /* Component interrupt service code */

        /* See if TX data buffer is not empty and there is space in TX FIFO */
        while(SPIS_1_txBufferRead != SPIS_1_txBufferWrite)
        {
            SPIS_1_swStatusTx = SPIS_1_GET_STATUS_TX(SPIS_1_swStatusTx);

            if ((SPIS_1_swStatusTx & SPIS_1_STS_TX_FIFO_NOT_FULL) != 0u)
            {
                if(SPIS_1_txBufferFull == 0u)
                {
                   SPIS_1_txBufferRead++;

                    if(SPIS_1_txBufferRead >= SPIS_1_TXBUFFERSIZE)
                    {
                        SPIS_1_txBufferRead = 0u;
                    }
                }
                else
                {
                    SPIS_1_txBufferFull = 0u;
                }

                /* Move data from the Buffer to the FIFO */
                CY_SET_REG8(SPIS_1_TXDATA_PTR,
                    SPIS_1_TXBUFFER[SPIS_1_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        /* If Buffer is empty then disable TX FIFO status interrupt until there is data in the buffer */
        if(SPIS_1_txBufferRead == SPIS_1_txBufferWrite)
        {
            SPIS_1_TX_STATUS_MASK_REG &= ~SPIS_1_STS_TX_FIFO_NOT_FULL;
        }

    #endif /* SPIS_1_InternalTxInterruptEnabled && (SPIS_1_TXBUFFERSIZE > 4u) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPIS_1_ISR_TX_END` */

    /* `#END` */

   }


/*******************************************************************************
* Function Name: SPIS_1_RX_ISR
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPIS_1_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  SPIS_1_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  SPIS_1_RXBUFFER[SPIS_1_RXBUFFERSIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPIS_1_RX_ISR)
{
    #if((SPIS_1_InternalRxInterruptEnabled) && (SPIS_1_RXBUFFERSIZE > 4u))
        uint8 rxData = 0u; 
    #endif /* SPIS_1_InternalRxInterruptEnabled */
    
    /* User code required at start of ISR */
    /* `#START SPIS_1_RX_ISR_START` */

    /* `#END` */

    #if((SPIS_1_InternalRxInterruptEnabled) && (SPIS_1_RXBUFFERSIZE > 4u))
        SPIS_1_swStatusRx = SPIS_1_GET_STATUS_RX(SPIS_1_swStatusRx);

        /* See if RX data FIFO has some data and if it can be moved to the RX Buffer */        
        while((SPIS_1_swStatusRx & SPIS_1_STS_RX_FIFO_NOT_EMPTY) ==
                                                                                SPIS_1_STS_RX_FIFO_NOT_EMPTY)
        {
            rxData = CY_GET_REG8(SPIS_1_RXDATA_PTR);
            
            /* Set next pointer. */
            SPIS_1_rxBufferWrite++;
            if(SPIS_1_rxBufferWrite >= SPIS_1_RXBUFFERSIZE)
            {
                SPIS_1_rxBufferWrite = 0u;
            }

            if(SPIS_1_rxBufferWrite == SPIS_1_rxBufferRead)
            {
                SPIS_1_rxBufferRead++;
                if(SPIS_1_rxBufferRead >= SPIS_1_RXBUFFERSIZE)
                {
                    SPIS_1_rxBufferRead = 0u;
                }
                SPIS_1_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            SPIS_1_RXBUFFER[SPIS_1_rxBufferWrite] = rxData;
                
            SPIS_1_swStatusRx = SPIS_1_GET_STATUS_RX(SPIS_1_swStatusRx);
        }
    #endif /* SPIS_1_InternalRxInterruptEnabled  && (SPIS_1_RXBUFFERSIZE > 4u) */

    /* User code required at end of ISR (Optional) */
    /* `#START SPIS_1_RX_ISR_END` */

    /* `#END` */
    
}

/* [] END OF FILE */
