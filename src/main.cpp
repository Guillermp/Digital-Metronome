#include <Arduino.h>
#include "led.h"
#include "button.h"

// Read the button periodically
ISR(TIMER0_COMPA_vect) {
  readButton();
}

// Metronome
ISR(TIMER1_COMPA_vect) {
  toggleLED();  
}

int main() {

  // Setup
  initButton();
  initLED();
  sei();
  setupTimer();
  setupTimerMetronome();

  // loop
  while(true){

    // If the button is pressed then modify the blinking rate
    cli();
    uint8_t button = debounced_button_value;
    //printf("lol %i", button);
    debounced_button_value = 0;
    sei();

    if (button_event == 1) {
        button_event = 0;
        modifyMetronomeRate(); // Modifies the rate of the metronome
    }
    

    /*
    turnOnLED();
    delay(1000);
    turnOffLED();
    delay(1000);
    */
  }
}