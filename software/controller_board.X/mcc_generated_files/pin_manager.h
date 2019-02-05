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
        Device            :  PIC16F18345
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

// get/set LIGHT aliases
#define LIGHT_TRIS                 TRISBbits.TRISB4
#define LIGHT_LAT                  LATBbits.LATB4
#define LIGHT_PORT                 PORTBbits.RB4
#define LIGHT_WPU                  WPUBbits.WPUB4
#define LIGHT_OD                   ODCONBbits.ODCB4
#define LIGHT_ANS                  ANSELBbits.ANSB4
#define LIGHT_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define LIGHT_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define LIGHT_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define LIGHT_GetValue()           PORTBbits.RB4
#define LIGHT_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define LIGHT_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define LIGHT_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define LIGHT_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define LIGHT_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define LIGHT_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define LIGHT_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define LIGHT_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set MODE_BTTN aliases
#define MODE_BTTN_TRIS                 TRISBbits.TRISB5
#define MODE_BTTN_LAT                  LATBbits.LATB5
#define MODE_BTTN_PORT                 PORTBbits.RB5
#define MODE_BTTN_WPU                  WPUBbits.WPUB5
#define MODE_BTTN_OD                   ODCONBbits.ODCB5
#define MODE_BTTN_ANS                  ANSELBbits.ANSB5
#define MODE_BTTN_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define MODE_BTTN_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define MODE_BTTN_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define MODE_BTTN_GetValue()           PORTBbits.RB5
#define MODE_BTTN_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define MODE_BTTN_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define MODE_BTTN_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define MODE_BTTN_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define MODE_BTTN_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define MODE_BTTN_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define MODE_BTTN_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define MODE_BTTN_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set PWR_BTTN aliases
#define PWR_BTTN_TRIS                 TRISBbits.TRISB6
#define PWR_BTTN_LAT                  LATBbits.LATB6
#define PWR_BTTN_PORT                 PORTBbits.RB6
#define PWR_BTTN_WPU                  WPUBbits.WPUB6
#define PWR_BTTN_OD                   ODCONBbits.ODCB6
#define PWR_BTTN_ANS                  ANSELBbits.ANSB6
#define PWR_BTTN_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define PWR_BTTN_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define PWR_BTTN_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define PWR_BTTN_GetValue()           PORTBbits.RB6
#define PWR_BTTN_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define PWR_BTTN_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define PWR_BTTN_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define PWR_BTTN_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define PWR_BTTN_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define PWR_BTTN_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define PWR_BTTN_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define PWR_BTTN_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set MIC aliases
#define MIC_TRIS                 TRISBbits.TRISB7
#define MIC_LAT                  LATBbits.LATB7
#define MIC_PORT                 PORTBbits.RB7
#define MIC_WPU                  WPUBbits.WPUB7
#define MIC_OD                   ODCONBbits.ODCB7
#define MIC_ANS                  ANSELBbits.ANSB7
#define MIC_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define MIC_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define MIC_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define MIC_GetValue()           PORTBbits.RB7
#define MIC_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define MIC_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define MIC_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define MIC_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define MIC_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define MIC_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define MIC_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define MIC_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set LED_Drive1 aliases
#define LED_Drive1_TRIS                 TRISCbits.TRISC3
#define LED_Drive1_LAT                  LATCbits.LATC3
#define LED_Drive1_PORT                 PORTCbits.RC3
#define LED_Drive1_WPU                  WPUCbits.WPUC3
#define LED_Drive1_OD                   ODCONCbits.ODCC3
#define LED_Drive1_ANS                  ANSELCbits.ANSC3
#define LED_Drive1_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define LED_Drive1_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define LED_Drive1_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define LED_Drive1_GetValue()           PORTCbits.RC3
#define LED_Drive1_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define LED_Drive1_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define LED_Drive1_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define LED_Drive1_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define LED_Drive1_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define LED_Drive1_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define LED_Drive1_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define LED_Drive1_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set LED_Drive2 aliases
#define LED_Drive2_TRIS                 TRISCbits.TRISC4
#define LED_Drive2_LAT                  LATCbits.LATC4
#define LED_Drive2_PORT                 PORTCbits.RC4
#define LED_Drive2_WPU                  WPUCbits.WPUC4
#define LED_Drive2_OD                   ODCONCbits.ODCC4
#define LED_Drive2_ANS                  ANSELCbits.ANSC4
#define LED_Drive2_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define LED_Drive2_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define LED_Drive2_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define LED_Drive2_GetValue()           PORTCbits.RC4
#define LED_Drive2_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define LED_Drive2_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define LED_Drive2_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define LED_Drive2_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define LED_Drive2_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define LED_Drive2_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define LED_Drive2_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define LED_Drive2_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set LED_Drive3 aliases
#define LED_Drive3_TRIS                 TRISCbits.TRISC5
#define LED_Drive3_LAT                  LATCbits.LATC5
#define LED_Drive3_PORT                 PORTCbits.RC5
#define LED_Drive3_WPU                  WPUCbits.WPUC5
#define LED_Drive3_OD                   ODCONCbits.ODCC5
#define LED_Drive3_ANS                  ANSELCbits.ANSC5
#define LED_Drive3_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define LED_Drive3_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define LED_Drive3_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define LED_Drive3_GetValue()           PORTCbits.RC5
#define LED_Drive3_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define LED_Drive3_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define LED_Drive3_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define LED_Drive3_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define LED_Drive3_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define LED_Drive3_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define LED_Drive3_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define LED_Drive3_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set LED_Drive0 aliases
#define LED_Drive0_TRIS                 TRISCbits.TRISC6
#define LED_Drive0_LAT                  LATCbits.LATC6
#define LED_Drive0_PORT                 PORTCbits.RC6
#define LED_Drive0_WPU                  WPUCbits.WPUC6
#define LED_Drive0_OD                   ODCONCbits.ODCC6
#define LED_Drive0_ANS                  ANSELCbits.ANSC6
#define LED_Drive0_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define LED_Drive0_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define LED_Drive0_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define LED_Drive0_GetValue()           PORTCbits.RC6
#define LED_Drive0_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define LED_Drive0_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define LED_Drive0_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define LED_Drive0_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define LED_Drive0_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define LED_Drive0_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define LED_Drive0_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define LED_Drive0_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set REMOTE aliases
#define REMOTE_TRIS                 TRISCbits.TRISC7
#define REMOTE_LAT                  LATCbits.LATC7
#define REMOTE_PORT                 PORTCbits.RC7
#define REMOTE_WPU                  WPUCbits.WPUC7
#define REMOTE_OD                   ODCONCbits.ODCC7
#define REMOTE_ANS                  ANSELCbits.ANSC7
#define REMOTE_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define REMOTE_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define REMOTE_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define REMOTE_GetValue()           PORTCbits.RC7
#define REMOTE_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define REMOTE_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define REMOTE_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define REMOTE_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define REMOTE_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define REMOTE_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define REMOTE_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define REMOTE_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

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