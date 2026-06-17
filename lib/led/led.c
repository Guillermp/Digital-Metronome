#include "led.h"

void initLED(void) {
    LED_DIR_REG |= (1 << LED_DIR_REG_BIT);  // set pin direction to output
}

void turnOnLED(void) {
    LED_OUT_REG |= (1 << LED_OUT_REG_BIT);  // drive pin high
}

void turnOffLED(void) {
    LED_OUT_REG &= ~(1 << LED_OUT_REG_BIT); // drive pin low
}

void toggleLED(void) {
    LED_OUT_REG ^= (1 << LED_OUT_REG_BIT);  // toggle LED
}