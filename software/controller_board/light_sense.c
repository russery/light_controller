#include "controller_board.X/mcc_generated_files/mcc.h"
#include "bsp.h"
#include "light_sense.h"

#define LIGHT_AVG_COUNT 256
#define LIGHT_LVL_NOT_INIT 0xFF
static uint8_t LightLevel = LIGHT_LVL_NOT_INIT;

uint8_t GetLightSense(void){
    uint16_t new_light = BspGetAdcValue(kLightChannel);
    new_light = (new_light >> 2);  // Convert 10-bit result to 8 bit.
    if(LightLevel == LIGHT_LVL_NOT_INIT) {
        LightLevel = (uint8_t)new_light;
    } else {
        int16_t diff = (int16_t)new_light - LightLevel;
        LightLevel = (uint8_t)(new_light);
                //((int32_t)LightLevel * LIGHT_AVG_COUNT + diff ) /
                //LIGHT_AVG_COUNT);
    }
    return LightLevel;
}

void TestLightSense(void){
    //BspWriteDebugByteAndWait(GetLightSense());
}