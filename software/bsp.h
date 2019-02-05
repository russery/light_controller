/* 
 * Board-specific constants and functions
 */

#ifndef BSP_H
#define	BSP_H

#define LED_BUS_COUNT 2
void BspSetLedPin(uint8_t bus, uint8_t pin, uint8_t state);

typedef enum Button {kModeButton, kPowerButton, kButtonCount} Button_t; 
#define kButtonPressed 0
bool BspIsButtonPressed(Button_t button);


void BspSetDebugPin(bool state);
void BspSetDebugLed(bool state);
void BspDoGlowDebugLed(void);


typedef enum AdcChannel {kMicChannel, kLightChannel,
        kAdcChannelCount} AdcChannel_t;


void BspDo1ms(void);

#endif	/* BSP_H */

