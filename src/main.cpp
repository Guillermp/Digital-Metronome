#include <Arduino.h>
#include "led.h"
#include "button.h"
#include "metronome.h"
#include "buzzer.h"


// Read the button periodically
ISR(Button_COMPA_vect) {
  readButton();
}

// Metronome
ISR(Metronome_COMPA_vect) {
  LED_OUT_REG ^= (1 << LED_OUT_REG_BIT); //Toggle LED
  Buzzer_OUT_REG ^= (1 << Buzzer_OUT_REG_BIT); //Toggle Buzzer
}

int main() {

  // Setup
  initButton();
  initLED();
  initBuzzer ();
  sei();
  setupTimerButton();
  setupTimerMetronome();
  initializeMetronomeBPM();

  // loop
  while(true){

    // If the button is pressed then modify the blinking rate
    cli();
    uint8_t button = debounced_button_value;
    debounced_button_value = 0;
    sei();

    if (button_event == 1) {
        button_event = 0;
        modifyMetronomeRate(); // Modifies the rate of the metronome
    }

  }
}