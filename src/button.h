#include "ioMapping.h"
const int threshold_debouncing = 3000;
volatile uint8_t debounced_button_value = 0;
volatile int counter = threshold_debouncing;
volatile uint8_t button_event = 0;

void initButton(void) {
    Button_DIR_REG &= ~(1 << Button_DIR_REG_BIT); // set pin direction to input
    Button_OUT_REG |= (1 << Button_OUT_REG_BIT);  // Set the pull-up resistor
    debounced_button_value = !((PINB & (1 << PINB1)) != 0);
    counter = threshold_debouncing;
}

void readButton(void) {
    uint8_t raw_reading = !((PINB & (1 << PINB1)) != 0);
    // If raw reading same as debounced button value, nothing has changed, reset the counter
    if (raw_reading == debounced_button_value) {
        counter = threshold_debouncing;
    }
    else {
        //Decrement the counter
        counter --;
        if (counter == 0) {
           
            button_event = 1;
            
            debounced_button_value = raw_reading;
            counter = threshold_debouncing;

        }
    }
}