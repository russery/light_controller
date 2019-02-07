#include "controller_board.X/mcc_generated_files/mcc.h"
#include "bsp.h"


//#define CURIOSITY_BOARD
#define CONTROLLER_BOARD

static uint16_t adc_result_[kAdcChannelCount] = {0};

void BspSetHBridgePin(HBridge_t bus, HBridgeFet_t fet, bool state){
    switch(bus) {
        case kHBridge1:
            switch(fet) {
                case kFet1:
                    if(state)
                        B1FET1_SetHigh();
                    else
                        B1FET1_SetLow();
                    break;
                case kFet2:
                    if(state)
                        B1FET2_SetHigh();
                    else
                        B1FET2_SetLow();
                    break;
                case kFet3:
                    if(state)
                        B1FET3_SetHigh();
                    else
                        B1FET3_SetLow();
                    break;
                case kFet4:
                    if(state)
                        B1FET4_SetHigh();
                    else
                        B1FET4_SetLow();
                    break;
                case kFetCount:
                default:
                    break;
            }
            break;
        default:
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