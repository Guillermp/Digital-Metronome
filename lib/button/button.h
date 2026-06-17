#pragma once
#include "ioMapping.h"

#ifdef __cplusplus
extern "C" {
#endif

#define setupTimerButton setupTimer0 //Renaming the particular timer to its purpose
#define Button_COMPA_vect COMP_Interrupt_Timer0

#define THRESHOLD_DEBOUNCING 1000

struct Button {
    volatile uint8_t debounced_button_state;
    volatile uint16_t counter;
    volatile uint8_t readBit;
    volatile void (*fptr)(void);
};


extern volatile struct Button button_up;
extern volatile struct Button button_down;

void initButtons(void);
uint8_t debouncing_logic(uint8_t raw_reading, volatile struct Button* buttonPtr);
void readButtonDebounced(volatile struct Button* buttonPtr);

#ifdef __cplusplus
}
#endif