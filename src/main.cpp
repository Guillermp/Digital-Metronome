#include <Arduino.h>
#include "led.h"
#include "button.h"
#include "metronome.h"
#include "buzzer.h"


// Read the button periodically
ISR(Button_COMPA_vect) {
  //readButton_Up_only();
  readButtonDebounced(&button_up);
  readButtonDebounced(&button_down);
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
    //Serial.println(getMetronomeBPM());


  }
}