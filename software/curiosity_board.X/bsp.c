
#include "mcc_generated_files/mcc.h"
#include "bsp.h"

void BspSetLedPin(uint8_t bus, uint8_t pin, uint8_t state){
    if((bus >= LED_BUS_COUNT) || (pin >= 2))
        return;
    switch(bus){
        case 0:
            if(pin == 0){
                if(state == 0)
                    LED_Drive0_SetLow();
                else
                    LED_Drive0_SetHigh();
            } else {
                if(state == 0)
                    LED_Drive1_SetLow();
                else
                    LED_Drive1_SetHigh();
            }
        case 1:
            if(pin == 0){
                if(state == 0)
                    LED_Drive2_SetLow();
                else
                    LED_Drive2_SetHigh();
            } else {
                if(state == 0)
                    LED_Drive3_SetLow();
                else
                    LED_Drive3_SetHigh();
            }
    }
}
