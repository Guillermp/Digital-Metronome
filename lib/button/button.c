#include "button.h"
#define THRESHOLD_DEBOUNCING 1000

volatile struct Button button_up = {0, THRESHOLD_DEBOUNCING, 0, ButtonUp_Read_REG_BIT };
volatile struct Button button_down = {0, THRESHOLD_DEBOUNCING, 0, ButtonDown_Read_REG_BIT};


void initButtons(void) {
    ButtonUp_DIR_REG &= ~(1 << ButtonUp_DIR_REG_BIT); // set pin direction to input
    ButtonUp_OUT_REG |= (1 << ButtonUp_OUT_REG_BIT);  // Set the pull-up resistor
    button_up.debounced_button_value = !((ButtonUp_Read_REG & (1 << ButtonUp_Read_REG_BIT)) != 0);

    ButtonDown_DIR_REG &= ~(1 << ButtonDown_DIR_REG_BIT); // set pin direction to input
    ButtonDown_OUT_REG |= (1 << ButtonDown_OUT_REG_BIT);  // Set the pull-up resistor
    button_down.debounced_button_value = !((ButtonDown_Read_REG & (1 << ButtonDown_Read_REG_BIT)) != 0);

    button_up.counter = THRESHOLD_DEBOUNCING;
    button_down.counter = THRESHOLD_DEBOUNCING;
}


void readButton(volatile struct Button* buttonPtr) {
    uint8_t raw_reading = !((Shared_Button_READ & (1 << buttonPtr->readBit)) != 0);
    // If raw reading same as debounced button value, nothing has changed, reset the counter
    if (raw_reading == buttonPtr->debounced_button_value) {
        buttonPtr->counter = THRESHOLD_DEBOUNCING;
    }
    else {
        //Decrement the counter
        buttonPtr->counter -=  1;
        
        if (buttonPtr->counter == 0) {
           
            buttonPtr->button_pressed = 1;
            buttonPtr->debounced_button_value = raw_reading;
            buttonPtr->counter = THRESHOLD_DEBOUNCING;

        }
    }
    //Serial.println(buttonPtr->counter);
    
}