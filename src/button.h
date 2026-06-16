#include "ioMapping.h"

#define setupTimerButton setupTimer0 //Renaming the particular timer to its purpose
#define Button_COMPA_vect COMP_Interrupt_Timer0

const static int threshold_debouncing = 200;
volatile uint8_t debounced_button_value_Up = 0; // is_pressed?
volatile uint8_t debounced_button_value_Down = 0;  // is_pressed?
volatile uint16_t counterUp = threshold_debouncing;
volatile uint16_t counterDown = threshold_debouncing;
volatile uint8_t button_event_Up = 0;
volatile uint8_t button_event_Down = 0;

/*
struct Button {
    volatile uint8_t debounced_button_value;
    volatile uint16_t counter;
    volatile uint8_t button_event;
};


struct Button button_up = {0,0,0};
*/

void initButtons(void) {
    ButtonUp_DIR_REG &= ~(1 << ButtonUp_DIR_REG_BIT); // set pin direction to input
    ButtonUp_OUT_REG |= (1 << ButtonUp_OUT_REG_BIT);  // Set the pull-up resistor
    debounced_button_value_Up = !((ButtonUp_Read_REG & (1 << ButtonUp_Read_REG_BIT)) != 0);

    ButtonDown_DIR_REG &= ~(1 << ButtonDown_DIR_REG_BIT); // set pin direction to input
    ButtonDown_OUT_REG |= (1 << ButtonDown_OUT_REG_BIT);  // Set the pull-up resistor
    debounced_button_value_Down = !((ButtonDown_Read_REG & (1 << ButtonDown_Read_REG_BIT)) != 0);

    counterUp = threshold_debouncing;
    counterDown = threshold_debouncing;
}


void readButton(volatile uint8_t *debounced_button_value, uint8_t Read_REG_BIT, volatile uint8_t* button_event, volatile uint16_t* counter ) {
    uint8_t raw_reading = !((ButtonUp_Read_REG & (1 << Read_REG_BIT)) != 0);
    // If raw reading same as debounced button value, nothing has changed, reset the counter
    if (raw_reading == *debounced_button_value) {
        *counter = threshold_debouncing;
    }
    else {
        //Decrement the counter
        *counter -=  1;
        
        if (*counter == 0) {
           
            *button_event = 1;
            
            *debounced_button_value = raw_reading;
            *counter = threshold_debouncing;

        }
    }
    Serial.println(*counter);
    
}


void readButton_Up_only(void) {
    
    uint8_t raw_reading = !((ButtonUp_Read_REG & (1 << ButtonUp_Read_REG_BIT)) != 0);
    
    // If raw reading same as debounced button value, nothing has changed, reset the counter
    if (raw_reading == debounced_button_value_Up) {
        counterUp = threshold_debouncing;
        
    }
    else {
        //Decrement the counter
        counterUp --;
        if (counterUp == 0) {
           
            button_event_Up = 1;
            
            debounced_button_value_Up = raw_reading;
            counterUp = threshold_debouncing;

        }
    }
    Serial.println(counterUp);
}