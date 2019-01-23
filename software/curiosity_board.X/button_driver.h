/* 
 * Handle pushbutton inputs, providing access to button state and duration
 * of presses.
 */

#ifndef BUTTON_DRIVER_H
#define	BUTTON_DRIVER_H

bool GetButtonState(BUTTON_t button);
uint16_t GetButtonPressTime(BUTTON_t button);
void ClearButtonPressTime(BUTTON_t button);
void DoButtons(void);

void TestButtonDriver(void);


#endif	/* BUTTON_DRIVER_H */

