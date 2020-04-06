/**

*/

#include "controller_board.X/mcc_generated_files/mcc.h"
#include "bsp.h"
#include "led_driver.h"
#include "button_driver.h"
#include "light_sense.h"
#include "microphone.h"
#include "rf_receive.h"


void main(void){
    // initialize the device
    SYSTEM_Initialize();
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    InitializeRf();
    InitializeLeds();
    printf("Started up successfully!");

    TestRfReceive();
    //TestButtonDriver();
    
    while(1){
        //TestLedDriver();
        //TestMicrophone();
        //TestLightSense();
        //DoButtons();
        //DoLeds();
        DoRfReceive();
        BspDo1ms(); // Main loop should execute on a 1ms loop.
    }
}
