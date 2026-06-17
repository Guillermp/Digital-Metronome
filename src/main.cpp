#include <Arduino.h>
#include "led.h"
#include "button.h"
#include "metronome.h"
#include "buzzer.h"


// Read the button periodically
ISR(Button_COMPA_vect) {
  //readButton_Up_only();
  readButton(&button_up);
  readButton(&button_down);
}

// Metronome
ISR(Metronome_COMPA_vect) {
  //Toggle LED and the Buzzer
  Shared_OUT_REG ^= (1 << LED_OUT_REG_BIT) | (1 << Buzzer_OUT_REG_BIT); 
}

int main() {

  // Setup
  initButtons();
  initLED();
  initBuzzer ();
  sei();
  setupTimerButton();
  setupTimerMetronome();
  initializeMetronomeBPM();
  //Serial.begin(9600);

  // loop
  while(true){

    cli();
    button_up.debounced_button_value = 0;
    button_down.debounced_button_value = 0;
    sei();

    
    if (button_up.button_pressed == 1) {
        cli();
        button_up.button_pressed = 0;
        sei();
        increaseMetronomeRate();
        //Serial.println("Incresed the rate");
    }
    if (button_down.button_pressed == 1) {
        cli();
        button_down.button_pressed = 0;
        sei();
        decreaseMetronomeRate();
        //Serial.println("Decreased the rate");
    }

  }
}