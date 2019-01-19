/**
   CWG Generated Driver File
 
   @Company
     Microchip Technology Inc.
 
   @File Name
     cwg.c
 
   @Summary
     This is the generated driver implementation file for the CWG driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs
 
   @Description
     This source file provides implementations for driver APIs for CWG.
     Generation Information :
         Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
         Device            :  PIC16F1619
         Driver Version    :  2.11
     The generated drivers are tested against the following:
         Compiler          :  XC8 1.45 or later
         MPLAB             :  MPLAB X 4.15
 */ 

 /*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
 
 /**
   Section: Included Files
 */

#include <xc.h>
#include "cwg.h"

/**
  Section: CWG APIs
*/

void CWG_Initialize(void)
{
    // Set the CWG to the options selected in PIC10 / PIC12 / PIC16 / PIC18 MCUs

	// CWG1POLA non inverted; CWG1POLC non inverted; CWG1POLB non inverted; CWG1POLD non inverted; 
	CWG1CON1 = 0x00;

	// CWG1DBR 0; 
	CWG1DBR = 0x00;

	// CWG1DBF 0; 
	CWG1DBF = 0x00;

	// CWG1SHUTDOWN No Auto-shutdown; CWG1REN disabled; CWG1LSBD tri-stated; CWG1LSAC tri-stated; 
	CWG1AS0 = 0x14;

	// CWG1C1AS disabled; CWG1INAS disabled; CWG1C2AS disabled; CWG1TMR4AS disabled; CWG1TMR2AS disabled; CWG1TMR6AS disabled; 
	CWG1AS1 = 0x00;

	// CWG1STRD disabled; CWG1STRB enabled; CWG1STRC disabled; CWG1STRA enabled; CWG1OVRD low; CWG1OVRA low; CWG1OVRB high; CWG1OVRC low; 
	CWG1OCON0 = 0x23;

	// CWG1CS FOSC; 
	CWG1CLKCON = 0x00;

	// CWG1IS PWM3_OUT; 
	CWG1ISM = 0x09;

	// CWG1LD Buffer_not_loaded; CWG1EN enabled; CWG1MODE Sync Steering mode; 
	CWG1CON0 = 0x81;

}


void CWG_AutoShutdownEventSet()
{
    CWG1AS0bits.CWG1SHUTDOWN = 1;
}

void CWG_AutoShutdownEventClear()
{
    CWG1AS0bits.CWG1SHUTDOWN = 0;
}


/**
 End of File
*/