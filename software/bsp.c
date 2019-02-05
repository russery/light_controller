#include "controller_board.X/mcc_generated_files/mcc.h"
#include "bsp.h"


//#define CURIOSITY_BOARD
#define CONTROLLER_BOARD

static uint16_t adc_result_[kAdcChannelCount] = {0};

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
            break;
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
            break;
    }
}

bool BspIsButtonPressed(Button_t button){
    if(button > kButtonCount)
        return false;
    switch(button){
        case kModeButton:
            return (bool)(MODE_BTTN_GetValue() == kButtonPressed);
#ifdef CONTROLLER_BOARD
//        case kPowerButton:
//            return (bool)PWR_BTTN_GetValue();
#endif
        default:
            return false;
    }
}

void BspSetDebugPin(bool state){
    if(state)
        DEBUG_SetHigh();
    else
        DEBUG_SetLow();
}

void BspSetDebugLed(bool state){
#ifdef CURIOSITY_BOARD
    if(!state){ // Inverted operation, 0 = lit
        LED0_SetLow();
    } else {
        LED0_SetHigh();
    }
#endif
}

void BspDoGlowDebugLed(void){
    static uint16_t count = 0;
    static uint8_t index = 0;
    static const uint8_t MAX_ONTIME = 25;
    static const uint8_t ON_TIME[] = {
        1,3,5,7,9,11,13,14,16,17,19,20,21,22,23,23,24,24,24,25,24,
        24,24,23,23,22,21,20,19,17,16,14,13,11,9,7,5,3,1};
    static const uint8_t LEN_ONTIME = sizeof(ON_TIME);
    count++;
    if(count == ON_TIME[index]){
        BspSetDebugLed(0);
    }
    else if(count > MAX_ONTIME){
        count = 0;
        BspSetDebugLed(1);
        if(++index >= LEN_ONTIME){
            index = 0;
        }
    }
}

void BspDo1ms(void){
    while(!TMR0_HasOverflowOccured());
#ifdef CURIOSITY_BOARD
    TMR0_Reload();
    INTCONbits.TMR0IF = 0; // Clear TMR0 interrupt flag
#endif
#ifdef CONTROLLER_BOARD
    TMR0_Reload(0xF9); // 1ms reload
    PIR0bits.TMR0IF = 0;
#endif
}

uint16_t BspGetAdcValue(AdcChannel_t channel){
    return adc_result_[channel];
}

void BspDoAdc(void){
    static AdcChannel_t current_channel = 0;
    
    static enum {kStartConversion, kWaitConversion} adc_stage;
    
    switch(adc_stage) {
        case kStartConversion:    
            switch(current_channel){
                case kMicChannel:
                    ADC_SelectChannel(MIC);
                    break;
                // TODO Other channels
            }
            ADC_StartConversion();
            adc_stage++;
            break;
        case kWaitConversion:
            if(ADC_IsConversionDone()) {
                adc_result_[current_channel] = ADC_GetConversionResult();
                current_channel = (++current_channel == kAdcChannelCount) ?
                    0 : current_channel;
                adc_stage = kStartConversion;
            } else {
                break;
            }
    }
}