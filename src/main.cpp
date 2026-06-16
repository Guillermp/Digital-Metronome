#include <Arduino.h>
#include "led.h"
#include "button.h"
#include "metronome.h"
#include "buzzer.h"


// Read the button periodically
ISR(Button_COMPA_vect) {
  //readButton_Up_only();
  readButton(&debounced_button_value_Up, ButtonUp_Read_REG_BIT, &button_event_Up, &counterUp);
  readButton(&debounced_button_value_Down, ButtonDown_Read_REG_BIT, &button_event_Down, &counterDown);
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
  Serial.begin(9600);

  // loop
  while(true){

    cli();
    debounced_button_value_Up = 0;
    debounced_button_value_Down = 0;
    sei();

    
    if (button_event_Up == 1) {
        cli();
        button_event_Up = 0;
        sei();
        increaseMetronomeRate();
        Serial.println("Incresed the rate");
    }
    if (button_event_Down == 1) {
        cli();
        button_event_Down = 0;
        sei();
        decreaseMetronomeRate();
    }

  }
}