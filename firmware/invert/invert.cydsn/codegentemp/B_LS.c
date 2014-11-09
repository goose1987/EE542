/*******************************************************************************
* File Name: B_LS.c  
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
#include "B_LS.h"

/* APIs are not generated for P15[7:6] on PSoC 5 */
#if !(CY_PSOC5A &&\
	 B_LS__PORT == 15 && ((B_LS__MASK & 0xC0) != 0))


/*******************************************************************************
* Function Name: B_LS_Write
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
void B_LS_Write(uint8 value) 
{
    uint8 staticBits = (B_LS_DR & (uint8)(~B_LS_MASK));
    B_LS_DR = staticBits | ((uint8)(value << B_LS_SHIFT) & B_LS_MASK);
}


/*******************************************************************************
* Function Name: B_LS_SetDriveMode
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
void B_LS_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(B_LS_0, mode);
}


/*******************************************************************************
* Function Name: B_LS_Read
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
*  Macro B_LS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 B_LS_Read(void) 
{
    return (B_LS_PS & B_LS_MASK) >> B_LS_SHIFT;
}


/*******************************************************************************
* Function Name: B_LS_ReadDataReg
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
uint8 B_LS_ReadDataReg(void) 
{
    return (B_LS_DR & B_LS_MASK) >> B_LS_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(B_LS_INTSTAT) 

    /*******************************************************************************
    * Function Name: B_LS_ClearInterrupt
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
    uint8 B_LS_ClearInterrupt(void) 
    {
        return (B_LS_INTSTAT & B_LS_MASK) >> B_LS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif /* CY_PSOC5A... */

    
/* [] END OF FILE */
