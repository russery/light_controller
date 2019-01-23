#include "mcc_generated_files/mcc.h"
#include "bsp.h"
#include "button_driver.h"

typedef struct button_state {
    uint8_t state_count;
    uint8_t debounce_threshold;
    uint16_t press_time;
    bool state;
} button_state_t;
static button_state_t ButtonState[BUTTON_COUNT] = {
    {0, 10, 0, 0}, // TODO create an initializer to set debounce threshold
};

bool GetButtonState(BUTTON_t button){
    return ButtonState[button].state;
}

uint16_t GetButtonPressTime(BUTTON_t button){
    return ButtonState[button].press_time;
}

void ClearButtonPressTime(BUTTON_t button){
    ButtonState[button].press_time = 0;
}

void DoButtons(void){
    button_state_t *b;
    bool butt_state;
    for(int butt=0; butt<BUTTON_COUNT; butt++){
        b = &ButtonState[butt];
        butt_state = BspIsButtonPressed(butt);
        if(butt_state != b->state) {
            b->state_count++;
        } else {
            b->state_count = (b->state_count > 1) ? (b->state_count - 1) : 0;
            if(butt_state) // Button is pressed
                b->press_time = (b->press_time < 0xFFFF) ? 
                    (b->press_time + 1) : 0xFFFF;
        }
        if(b->state_count >= b->debounce_threshold){
            b->state = butt_state;
            if(!butt_state) // Button is not pressed.
                b->press_time = 0;
        }
    }
}

void TestButtonDriver(void){
    static const uint16_t HOLD_TIME_THRESHOLD_MS = 3000;
    static const BUTTON_t TEST_BUTT = MODE_BUTTON;
    static enum {
                LIGHT_LED,
                GLOW_LED,
                EXIT_TESTS,
    }test_mode;
    
    for(uint16_t i=0; i<60000; i++){ // Loop for 60s
        switch(test_mode){
            case LIGHT_LED:
                BspSetDebugLed(GetButtonState(TEST_BUTT));
                if(GetButtonPressTime(TEST_BUTT) > HOLD_TIME_THRESHOLD_MS){
                    test_mode++;
                    ClearButtonPressTime(TEST_BUTT);
                }
                break;
            case GLOW_LED:
                BspDoGlowDebugLed();
                if(GetButtonPressTime(TEST_BUTT) > HOLD_TIME_THRESHOLD_MS){
                    test_mode++;
                    ClearButtonPressTime(TEST_BUTT);
                }
                break;
            case EXIT_TESTS:
                test_mode = 0;
        }
        DoButtons();
        BspDo1ms();
    }
}