/* 
 * 
 */

#ifndef LED_DRIVER_H
#define	LED_DRIVER_H

#include <stdint.h>
#include <stdbool.h>


typedef enum led_mode_t {OFF, STEADY, GLOW} LED_MODE_t;

void InitializeLeds(void);
void SetMode(uint8_t led_ind, LED_MODE_t mode);
void SetBrightness(uint8_t bus, uint8_t brightness_percent);
void DoLeds(void);

void TestLedDriver(void);

#endif	/* LED_DRIVER_H */

