#include "button.h"
#include "metronome.h"


volatile struct Button button_up = {0, THRESHOLD_DEBOUNCING, ButtonUp_Read_REG_BIT, &increaseMetronomeRate};
volatile struct Button button_down = {0, THRESHOLD_DEBOUNCING, ButtonDown_Read_REG_BIT, &decreaseMetronomeRate};


void initButtons(void) {
    ButtonUp_DIR_REG &= ~(1 << ButtonUp_DIR_REG_BIT); // set pin direction to input
    ButtonUp_OUT_REG |= (1 << ButtonUp_OUT_REG_BIT);  // Set the pull-up resistor
    button_up.debounced_button_state = !((ButtonUp_Read_REG & (1 << ButtonUp_Read_REG_BIT)) != 0);

    ButtonDown_DIR_REG &= ~(1 << ButtonDown_DIR_REG_BIT); // set pin direction to input
    ButtonDown_OUT_REG |= (1 << ButtonDown_OUT_REG_BIT);  // Set the pull-up resistor
    button_down.debounced_button_state = !((ButtonDown_Read_REG & (1 << ButtonDown_Read_REG_BIT)) != 0);

    button_up.counter = THRESHOLD_DEBOUNCING;
    button_down.counter = THRESHOLD_DEBOUNCING;
}


uint8_t debouncing_logic(uint8_t raw_reading, volatile struct Button* buttonPtr) {

    // If raw reading same as debounced button value, nothing has changed, reset the counter
     if (raw_reading == buttonPtr->debounced_button_state) {
        buttonPtr->counter = THRESHOLD_DEBOUNCING;
    }
    else {
        //Decrement the counter
        buttonPtr->counter -=  1;
        
        if (buttonPtr->counter == 0) {
           
            //buttonPtr->button_pressed = 1;
            buttonPtr->debounced_button_state = raw_reading;
            buttonPtr->counter = THRESHOLD_DEBOUNCING;

            //If the debounced value is pressed
            if (buttonPtr->debounced_button_state == 1) {
                buttonPtr->fptr(); // Increase or decrese the BPM of the metronome
            }

        }
        
    }

}

void readButtonDebounced(volatile struct Button* buttonPtr) {
    uint8_t raw_reading = !((Shared_Button_READ & (1 << buttonPtr->readBit)) != 0);
    
    debouncing_logic(raw_reading, buttonPtr);
    
}