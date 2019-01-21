
#include "mcc_generated_files/mcc.h"
#include "bsp.h"
#include "led_driver.h"

typedef struct {
    LED_MODE_t mode;
    uint8_t max_on_percent; // 0-100%
    uint8_t active_led;
    uint8_t led_on_percent[2];
} bus_state_t;
static bus_state_t LedBus[LED_BUS_COUNT];

void setLed(uint8_t bus, uint8_t led, uint8_t state);


void InitializeLeds(void){
    for(int i=0; i<LED_BUS_COUNT; i++)
        LedBus[i].mode = OFF;
    //TODO initialize rest of state struct.
}

void SetMode(uint8_t bus, LED_MODE_t mode){
    // TODO check inputs for sanity.
    LedBus[bus].mode = mode;
}

void SetBrightness(uint8_t bus, uint8_t brightness_percent){
    // TODO check inputs for sanity.
    LedBus[bus].max_on_percent = brightness_percent;
}

void DoLeds(void){
    bus_state_t *bus_p;
    static const uint8_t CYCLE_MS = 10;
    static uint16_t count_ms = 0;
    
    for(int bus=0; bus<LED_BUS_COUNT; bus++){
        bus_p = &(LedBus[bus]);
        if(count_ms >= CYCLE_MS) {
            BspSetLedPin(bus, 0, 0);  // Turn off both LEDs.
            BspSetLedPin(bus, 1, 0);
            bus_p->active_led = bus_p->active_led ^ 0x01; // Switch active LED.
        }
        switch(bus_p->mode) {
           case OFF:
               // Don't need to do anything, both LEDs already off.
               break;
           case STEADY:
               if((count_ms*100 / CYCLE_MS) <
                       bus_p->max_on_percent)
                   BspSetLedPin(bus, bus_p->active_led, 1);
               else
                   BspSetLedPin(bus, bus_p->active_led, 0);
               break;
           case GLOW:
               ;
               break;
        }
    }
    if(++count_ms > CYCLE_MS)
        count_ms = 0;  // Reset cycle count.
}

void TestLedDriver(void){
    static uint16_t test_counter = 0;
    static uint8_t test_state = 0;
    static const uint8_t TEST_STATE_MAX = 11;
    static uint8_t active_bus = 1;
    static uint8_t brightness = 0;
    
    if(++test_counter > 250){ // Advance state every 250ms.
        test_counter = 0;
        switch(test_state){
        case 0:
            SetMode(active_bus,OFF);
            break;
        case 1:
            SetMode(active_bus,STEADY);
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            brightness += 10;
            SetBrightness(active_bus,brightness);
            break;
        case TEST_STATE_MAX:
            brightness = 0;
            SetMode(active_bus,STEADY);
            SetBrightness(0,100);
            //if(++active_bus >= LED_BUS_COUNT)
            //    active_bus = 0;
            break;
        }
        if(++test_state > TEST_STATE_MAX)
            test_state = 0;
    }
}