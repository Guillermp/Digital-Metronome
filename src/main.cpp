#include <Arduino.h>
#include "led.h"
#include "button.h"

ISR(TIMER1_COMPA_vect) {
  toggleLED();  
}

void setup() {
  initButton();
  initLED();
  sei();
  setupTimer();

}

void loop() {
  /*
  turnOnLED();
  delay(1000);
  turnOffLED();
  delay(1000);
  */

}