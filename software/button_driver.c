#include "controller_board.X/mcc_generated_files/mcc.h"
#include "bsp.h"
#include "button_driver.h"

typedef struct button_state {
    uint8_t state_count;
    uint8_t debounce_threshold;
    uint16_t press_time;
    bool state;
} button_state_t;
static button_state_t ButtonState[kButtonCount] = {
    {0, 10, 0, 0}, // TODO create an initializer to set debounce threshold
};

bool GetButtonState(Button_t button){
    return ButtonState[button].state;
}

uint16_t GetButtonPressTime(Button_t button){
    return ButtonState[button].press_time;
}

void ClearButtonPressTime(Button_t button){
    ButtonState[button].press_time = 0;
}

void DoButtons(void){
    button_state_t *b;
    bool butt_state;
    for(int butt=0; butt<kButtonCount; butt++){
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
    static const uint16_t kHoldTimeThresholdMs = 3000;
    static const Button_t kTestButt = kModeButton;
    static enum {
                kLightLed,
                kGlowLed,
                kRestartTest,
    } test_mode;
    
    for(uint16_t i=0; i<60000; i++){ // Loop for 60s
        switch(test_mode){
            case kLightLed:
                BspSetDebugLed(GetButtonState(kTestButt));
                if(GetButtonPressTime(kTestButt) > kHoldTimeThresholdMs){
                    test_mode++;
                    ClearButtonPressTime(kTestButt);
                }
                break;
            case kGlowLed:
                BspDoGlowDebugLed();
                if(GetButtonPressTime(kTestButt) > kHoldTimeThresholdMs){
                    test_mode++;
                    ClearButtonPressTime(kTestButt);
                }
                break;
            case kRestartTest:
                test_mode = 0;
        }
        DoButtons();
        BspDo1ms();
    }
}