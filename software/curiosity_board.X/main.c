/**

*/


#include "mcc_generated_files/mcc.h"

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    while (1)
    {
        while(!TMR0_HasOverflowOccured());
        TMR0_Reload();
        INTCONbits.TMR0IF = 0; // Clear TMR0 interrupt flag
        LED0_Toggle();
    }
}