/* 
 * Board-specific constants and functions
 */

#ifndef BSP_H
#define	BSP_H

#define LED_BUS_COUNT 2
void BspSetLedPin(uint8_t bus, uint8_t pin, uint8_t state);

typedef enum BUTTON {MODE_BUTTON, BUTTON_COUNT} BUTTON_t; 
#define BUTTON_PRESSED 0
bool BspIsButtonPressed(BUTTON_t button);


void BspSetDebugPin(bool state);
void BspSetDebugLed(bool state);
void BspDoGlowDebugLed(void);

void BspDo1ms(void);

#endif	/* BSP_H */

