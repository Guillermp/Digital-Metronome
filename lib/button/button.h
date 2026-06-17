#pragma once
#include "ioMapping.h"

#ifdef __cplusplus
extern "C" {
#endif

#define setupTimerButton setupTimer0 //Renaming the particular timer to its purpose
#define Button_COMPA_vect COMP_Interrupt_Timer0

struct Button {
    volatile uint8_t debounced_button_value;
    volatile uint16_t counter;
    volatile uint8_t button_pressed;
    volatile uint8_t readBit;
};


extern volatile struct Button button_up;
extern volatile struct Button button_down;

void initButtons(void);
void readButton(volatile struct Button* buttonPtr);

#ifdef __cplusplus
}
#endif