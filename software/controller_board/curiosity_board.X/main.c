/**

*/

#include "mcc_generated_files/mcc.h"
#include "bsp.h"
#include "led_driver.h"
#include "button_driver.h"
#include "microphone.h"

void do1ms(void);


void main(void){
    // initialize the device
    SYSTEM_Initialize();

    InitializeLeds();
    
    TestButtonDriver();
    
    while(1){
        TestLedDriver();
        TestMicrophone();
        DoButtons();
        DoLeds();
        BspDoGlowDebugLed();
        BspDo1ms(); // Main loop should execute on a 1ms loop.
    }
}
