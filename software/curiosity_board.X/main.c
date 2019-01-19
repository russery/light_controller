/**

*/

#include "mcc_generated_files/mcc.h"
#include "led_driver.h"

void doLed(void);


void main(void){
    // initialize the device
    SYSTEM_Initialize();

    while(1){
        doLed();
    }
}

void doLed(void){
    static uint16_t count = 0;
    static uint8_t index = 0;
    const uint8_t MAX_ONTIME = 25;
    const uint8_t on_time[] = {
        1,3,5,7,9,11,13,14,16,17,19,20,21,22,23,23,24,24,24,25,24,
        24,24,23,23,22,21,20,19,17,16,14,13,11,9,7,5,3,1};
    const uint8_t LEN_ONTIME = sizeof(on_time);
    
    if(TMR0_HasOverflowOccured()){
        TMR0_Reload();
        INTCONbits.TMR0IF = 0; // Clear TMR0 interrupt flag
        count++;
    }
    if(count == on_time[index]){
        LED0_SetLow();
    }
    else if(count > MAX_ONTIME){
        count = 0;
        LED0_SetHigh();
        if(++index >= LEN_ONTIME){
            index = 0;
        }
    }
}