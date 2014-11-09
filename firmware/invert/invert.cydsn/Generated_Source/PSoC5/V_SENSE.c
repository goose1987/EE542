/*******************************************************************************
* File Name: V_SENSE.c  
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
#include "V_SENSE.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 V_SENSE__PORT == 15 && ((V_SENSE__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: V_SENSE_Write
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
void V_SENSE_Write(uint8 value) 
{
    uint8 staticBits = (V_SENSE_DR & (uint8)(~V_SENSE_MASK));
    V_SENSE_DR = staticBits | ((uint8)(value << V_SENSE_SHIFT) & V_SENSE_MASK);
}


/*******************************************************************************
* Function Name: V_SENSE_SetDriveMode
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
void V_SENSE_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(V_SENSE_0, mode);
}


/*******************************************************************************
* Function Name: V_SENSE_Read
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
*  Macro V_SENSE_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 V_SENSE_Read(void) 
{
    return (V_SENSE_PS & V_SENSE_MASK) >> V_SENSE_SHIFT;
}


/*******************************************************************************
* Function Name: V_SENSE_ReadDataReg
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
uint8 V_SENSE_ReadDataReg(void) 
{
    return (V_SENSE_DR & V_SENSE_MASK) >> V_SENSE_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(V_SENSE_INTSTAT) 

    /*******************************************************************************
    * Function Name: V_SENSE_ClearInterrupt
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
    uint8 V_SENSE_ClearInterrupt(void) 
    {
        return (V_SENSE_INTSTAT & V_SENSE_MASK) >> V_SENSE_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
