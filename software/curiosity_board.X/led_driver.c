
#include "mcc_generated_files/mcc.h"
#include "bsp.h"
#include "led_driver.h"

typedef struct {
    uint8_t max_on_percent; // 0-100%
    uint8_t active_phase;
    uint8_t phase_on_percent[2];
} bus_state_t;
static bus_state_t LedBus[LED_BUS_COUNT];

void InitializeLeds(void){
    SetGlobalBrightness(0);  // Start with LEDs off.
    for(int bus=0; bus<LED_BUS_COUNT; bus++)
        SetMaxBrightness(bus, 100);
        
    //TODO initialize rest of state struct.
}

void SetGlobalBrightness(uint8_t brightness_percent){
    for(int bus=0; bus<LED_BUS_COUNT; bus++){
        SetPhaseBrightness(bus, 0, brightness_percent);
        SetPhaseBrightness(bus, 1, brightness_percent);
    }
}

void SetMaxBrightness(uint8_t bus, uint8_t brightness_percent){
    // TODO check inputs for sanity.
    LedBus[bus].max_on_percent = brightness_percent;
}

void SetPhaseBrightness(uint8_t bus, uint8_t phase, uint8_t brightness_percent){
    bus_state_t *bus_p = &LedBus[bus];
    if(brightness_percent > bus_p->max_on_percent)
        bus_p->phase_on_percent[phase] = bus_p->max_on_percent;
    else
        bus_p->phase_on_percent[phase] = brightness_percent;
}

void DoLeds(void){
    bus_state_t *bus_p;
    static const uint8_t CYCLE_MS = 10;
    static uint8_t count_ms = 0;
    uint8_t cycle_percent;
    
    cycle_percent = (uint8_t)( ((uint16_t)count_ms*100) / CYCLE_MS);
    for(int bus=0; bus<LED_BUS_COUNT; bus++){
        bus_p = &(LedBus[bus]);
        if(cycle_percent >= 100) {
            BspSetLedPin(bus, 0, 0);  // Turn off both LEDs.
            BspSetLedPin(bus, 1, 0);
            bus_p->active_phase = bus_p->active_phase ^ 0x01; // Switch phases.
        }
        if(cycle_percent <= bus_p->phase_on_percent[bus_p->active_phase])
            BspSetLedPin(bus, bus_p->active_phase, 1);
        else
            BspSetLedPin(bus, bus_p->active_phase, 0);
    }
    if(++count_ms > CYCLE_MS)
        count_ms = 0;  // Reset cycle count.
}

bool testWait(uint16_t max_counter){
    static uint16_t test_counter = 0;
    if(++test_counter > max_counter) {
        test_counter = 0;
        return true;
    }
    return false;
}

void TestLedDriver(void){    
    typedef enum test_state_enum {
            SWEEP_BRIGHTNESS_UP,
            SWEEP_BRIGHTNESS_DOWN,
            SWEEP_PHASE_BRIGHTNESS_UP,
            TEST_STATE_MAX,
    } test_state_t;
    static test_state_t test_state = 0;
    static uint8_t active_bus = 0;
    static uint8_t brightness = 0;
    
    switch(test_state){
    case SWEEP_BRIGHTNESS_UP:
        SetGlobalBrightness(brightness);
        if(testWait(10))
            brightness++;
        if(brightness > 100){
            test_state++;
        }
        break;
    case SWEEP_BRIGHTNESS_DOWN:
        SetGlobalBrightness(brightness);
        if(testWait(10))
            brightness--;
        if(brightness <= 0){
            test_state++;
        }
        break;
    case SWEEP_PHASE_BRIGHTNESS_UP:
        SetPhaseBrightness(active_bus, 0, brightness);
        SetPhaseBrightness(active_bus, 1, 100-brightness);
        if(testWait(10))
            brightness++;
        if(brightness > 100){
            brightness = 0;
            test_state++;
        }
        break;
    // TODO Test SetMaxBrightness()
    case TEST_STATE_MAX:
        if(++active_bus >= LED_BUS_COUNT)
            active_bus = 0;
        test_state = 0;
    }
}