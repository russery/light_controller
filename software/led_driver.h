/* 
 * 
 */

#ifndef LED_DRIVER_H
#define	LED_DRIVER_H

#include <stdint.h>
#include <stdbool.h>

void InitializeLeds(void);
void SetGlobalBrightness(uint8_t brightness_percent);
void SetMaxBrightness(uint8_t bus, uint8_t brightness_percent);
void SetPhaseBrightness(uint8_t bus, uint8_t phase, uint8_t brightness_percent);
void DoLeds(void);

void TestLedDriver(void);

#endif	/* LED_DRIVER_H */

