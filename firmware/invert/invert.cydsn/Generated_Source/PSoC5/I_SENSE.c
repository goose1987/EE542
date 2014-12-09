/*******************************************************************************
* File Name: I_SENSE.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "I_SENSE.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 I_SENSE__PORT == 15 && ((I_SENSE__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: I_SENSE_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None
*  
*******************************************************************************/
void I_SENSE_Write(uint8 value) 
{
    uint8 staticBits = (I_SENSE_DR & (uint8)(~I_SENSE_MASK));
    I_SENSE_DR = staticBits | ((uint8)(value << I_SENSE_SHIFT) & I_SENSE_MASK);
}


/*******************************************************************************
* Function Name: I_SENSE_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  None
*
*******************************************************************************/
void I_SENSE_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(I_SENSE_0, mode);
}


/*******************************************************************************
* Function Name: I_SENSE_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro I_SENSE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 I_SENSE_Read(void) 
{
    return (I_SENSE_PS & I_SENSE_MASK) >> I_SENSE_SHIFT;
}


/*******************************************************************************
* Function Name: I_SENSE_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 I_SENSE_ReadDataReg(void) 
{
    return (I_SENSE_DR & I_SENSE_MASK) >> I_SENSE_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(I_SENSE_INTSTAT) 

    /*******************************************************************************
    * Function Name: I_SENSE_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 I_SENSE_ClearInterrupt(void) 
    {
        return (I_SENSE_INTSTAT & I_SENSE_MASK) >> I_SENSE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
