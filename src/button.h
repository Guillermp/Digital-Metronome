#include "ioMapping.h"

#define setupTimerButton setupTimer0 //Renaming the particular timer to its purpose
#define Button_COMPA_vect COMP_Interrupt_Timer0

const static int threshold_debouncing = 1000;


struct Button {
    volatile uint8_t debounced_button_value;
    volatile uint16_t counter;
    volatile uint8_t button_pressed;
    volatile uint8_t readBit;
};


volatile struct Button button_up = {0, threshold_debouncing, 0, ButtonUp_Read_REG_BIT };
volatile struct Button button_down = {0, threshold_debouncing, 0, ButtonDown_Read_REG_BIT};


void initButtons(void) {
    ButtonUp_DIR_REG &= ~(1 << ButtonUp_DIR_REG_BIT); // set pin direction to input
    ButtonUp_OUT_REG |= (1 << ButtonUp_OUT_REG_BIT);  // Set the pull-up resistor
    button_up.debounced_button_value = !((ButtonUp_Read_REG & (1 << ButtonUp_Read_REG_BIT)) != 0);

    ButtonDown_DIR_REG &= ~(1 << ButtonDown_DIR_REG_BIT); // set pin direction to input
    ButtonDown_OUT_REG |= (1 << ButtonDown_OUT_REG_BIT);  // Set the pull-up resistor
    button_down.debounced_button_value = !((ButtonDown_Read_REG & (1 << ButtonDown_Read_REG_BIT)) != 0);

    button_up.counter = threshold_debouncing;
    button_down.counter = threshold_debouncing;
}


void readButton(volatile struct Button* butonPtr) {
    uint8_t raw_reading = !((Shared_Button_READ & (1 << butonPtr->readBit)) != 0);
    // If raw reading same as debounced button value, nothing has changed, reset the counter
    if (raw_reading == butonPtr->debounced_button_value) {
        butonPtr->counter = threshold_debouncing;
    }
    else {
        //Decrement the counter
        butonPtr->counter -=  1;
        
        if (butonPtr->counter == 0) {
           
            butonPtr->button_pressed = 1;
            butonPtr->debounced_button_value = raw_reading;
            butonPtr->counter = threshold_debouncing;

        }
    }
    //Serial.println(butonPtr->counter);
    
}

/*
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
    */