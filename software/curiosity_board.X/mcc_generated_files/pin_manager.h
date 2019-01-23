/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16F1619
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LED_Drive0 aliases
#define LED_Drive0_TRIS                 TRISAbits.TRISA2
#define LED_Drive0_LAT                  LATAbits.LATA2
#define LED_Drive0_PORT                 PORTAbits.RA2
#define LED_Drive0_WPU                  WPUAbits.WPUA2
#define LED_Drive0_OD                   ODCONAbits.ODA2
#define LED_Drive0_ANS                  ANSELAbits.ANSA2
#define LED_Drive0_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED_Drive0_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED_Drive0_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED_Drive0_GetValue()           PORTAbits.RA2
#define LED_Drive0_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED_Drive0_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED_Drive0_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LED_Drive0_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LED_Drive0_SetPushPull()        do { ODCONAbits.ODA2 = 0; } while(0)
#define LED_Drive0_SetOpenDrain()       do { ODCONAbits.ODA2 = 1; } while(0)
#define LED_Drive0_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define LED_Drive0_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set LED0 aliases
#define LED0_TRIS                 TRISAbits.TRISA5
#define LED0_LAT                  LATAbits.LATA5
#define LED0_PORT                 PORTAbits.RA5
#define LED0_WPU                  WPUAbits.WPUA5
#define LED0_OD                   ODCONAbits.ODA5
#define LED0_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED0_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED0_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED0_GetValue()           PORTAbits.RA5
#define LED0_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED0_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED0_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define LED0_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define LED0_SetPushPull()        do { ODCONAbits.ODA5 = 0; } while(0)
#define LED0_SetOpenDrain()       do { ODCONAbits.ODA5 = 1; } while(0)

// get/set LED_Drive2 aliases
#define LED_Drive2_TRIS                 TRISBbits.TRISB4
#define LED_Drive2_LAT                  LATBbits.LATB4
#define LED_Drive2_PORT                 PORTBbits.RB4
#define LED_Drive2_WPU                  WPUBbits.WPUB4
#define LED_Drive2_OD                   ODCONBbits.ODB4
#define LED_Drive2_ANS                  ANSELBbits.ANSB4
#define LED_Drive2_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LED_Drive2_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LED_Drive2_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define LED_Drive2_GetValue()           PORTBbits.RB4
#define LED_Drive2_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define LED_Drive2_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define LED_Drive2_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define LED_Drive2_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define LED_Drive2_SetPushPull()        do { ODCONBbits.ODB4 = 0; } while(0)
#define LED_Drive2_SetOpenDrain()       do { ODCONBbits.ODB4 = 1; } while(0)
#define LED_Drive2_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define LED_Drive2_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set LED_Drive3 aliases
#define LED_Drive3_TRIS                 TRISBbits.TRISB6
#define LED_Drive3_LAT                  LATBbits.LATB6
#define LED_Drive3_PORT                 PORTBbits.RB6
#define LED_Drive3_WPU                  WPUBbits.WPUB6
#define LED_Drive3_OD                   ODCONBbits.ODB6
#define LED_Drive3_ANS                  ANSELBbits.ANSB6
#define LED_Drive3_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define LED_Drive3_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define LED_Drive3_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define LED_Drive3_GetValue()           PORTBbits.RB6
#define LED_Drive3_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define LED_Drive3_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define LED_Drive3_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define LED_Drive3_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define LED_Drive3_SetPushPull()        do { ODCONBbits.ODB6 = 0; } while(0)
#define LED_Drive3_SetOpenDrain()       do { ODCONBbits.ODB6 = 1; } while(0)
#define LED_Drive3_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define LED_Drive3_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set DEBUG aliases
#define DEBUG_TRIS                 TRISBbits.TRISB7
#define DEBUG_LAT                  LATBbits.LATB7
#define DEBUG_PORT                 PORTBbits.RB7
#define DEBUG_WPU                  WPUBbits.WPUB7
#define DEBUG_OD                   ODCONBbits.ODB7
#define DEBUG_ANS                  ANSELBbits.ANSB7
#define DEBUG_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define DEBUG_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define DEBUG_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define DEBUG_GetValue()           PORTBbits.RB7
#define DEBUG_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define DEBUG_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define DEBUG_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define DEBUG_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define DEBUG_SetPushPull()        do { ODCONBbits.ODB7 = 0; } while(0)
#define DEBUG_SetOpenDrain()       do { ODCONBbits.ODB7 = 1; } while(0)
#define DEBUG_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define DEBUG_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set MODE_BTTN aliases
#define MODE_BTTN_TRIS                 TRISCbits.TRISC4
#define MODE_BTTN_LAT                  LATCbits.LATC4
#define MODE_BTTN_PORT                 PORTCbits.RC4
#define MODE_BTTN_WPU                  WPUCbits.WPUC4
#define MODE_BTTN_OD                   ODCONCbits.ODC4
#define MODE_BTTN_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define MODE_BTTN_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define MODE_BTTN_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define MODE_BTTN_GetValue()           PORTCbits.RC4
#define MODE_BTTN_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define MODE_BTTN_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define MODE_BTTN_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define MODE_BTTN_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define MODE_BTTN_SetPushPull()        do { ODCONCbits.ODC4 = 0; } while(0)
#define MODE_BTTN_SetOpenDrain()       do { ODCONCbits.ODC4 = 1; } while(0)

// get/set LED_Drive1 aliases
#define LED_Drive1_TRIS                 TRISCbits.TRISC5
#define LED_Drive1_LAT                  LATCbits.LATC5
#define LED_Drive1_PORT                 PORTCbits.RC5
#define LED_Drive1_WPU                  WPUCbits.WPUC5
#define LED_Drive1_OD                   ODCONCbits.ODC5
#define LED_Drive1_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define LED_Drive1_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define LED_Drive1_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define LED_Drive1_GetValue()           PORTCbits.RC5
#define LED_Drive1_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define LED_Drive1_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define LED_Drive1_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define LED_Drive1_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define LED_Drive1_SetPushPull()        do { ODCONCbits.ODC5 = 0; } while(0)
#define LED_Drive1_SetOpenDrain()       do { ODCONCbits.ODC5 = 1; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/