/* 
 * Board-specific constants and functions
 */

#ifndef BSP_H
#define	BSP_H

#define kHBridgeCount 1
typedef enum HBridge {kHBridge1=0} HBridge_t;
typedef enum HBridgeFet {kFet1, kFet2, kFet3, kFet4, kFetCount} HBridgeFet_t;
void BspSetHBridgePin(HBridge_t bus, HBridgeFet_t fet, bool state);

typedef enum Button {kModeButton, kPowerButton, kButtonCount} Button_t; 
#define kButtonPressed 0
bool BspIsButtonPressed(Button_t button);

void BspWriteDebugByteAndWait(unsigned char bug);

typedef enum AdcChannel {kMicChannel, kLightChannel,
        kAdcChannelCount} AdcChannel_t;
uint16_t BspGetAdcValue(AdcChannel_t channel);

void BspSetRFTimerISR(void (* handle)(void));
#define BspGetRfPinState() REMOTE_GetValue()

void BspDo1ms(void);

#endif	/* BSP_H */

