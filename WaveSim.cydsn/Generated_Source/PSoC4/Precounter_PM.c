/*******************************************************************************
* File Name: Precounter_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Precounter.h"

static Precounter_BACKUP_STRUCT Precounter_backup;


/*******************************************************************************
* Function Name: Precounter_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Precounter_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_Sleep(void)
{
    if(0u != (Precounter_BLOCK_CONTROL_REG & Precounter_MASK))
    {
        Precounter_backup.enableState = 1u;
    }
    else
    {
        Precounter_backup.enableState = 0u;
    }

    Precounter_Stop();
    Precounter_SaveConfig();
}


/*******************************************************************************
* Function Name: Precounter_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Precounter_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Precounter_Wakeup(void)
{
    Precounter_RestoreConfig();

    if(0u != Precounter_backup.enableState)
    {
        Precounter_Enable();
    }
}


/* [] END OF FILE */
