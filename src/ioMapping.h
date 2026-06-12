#pragma once

#ifdef COMPILING_FOR_V1
  #include "ioMapping_v1.h"
  #include <avr/io.h>
  #include <avr/interrupt.h>
#elif defined(COMPILING_FOR_V2)
  #include "ioMapping_v2.h"
  #include <avr/io.h>
  #include <avr/interrupt.h>
#else
  #error "No I/O map selected for the board. What is your target?"
#endif


// Seting MACROS according to the version of the ioMapping file
#define PORT_REG(port)    (port == 1 ? PORTB  : PORTC)
#define PORT_REG_BIT(pin) (pin  == 5 ? PORTB5 : PORTC6)
#define PORT_REG_BIT_button(pin) (pin  == 1 ? PORTB1 : PORTC2)
#define DIR_REG(port)     (port == 1 ? DDRB   : DDRC)
#define DIR_REG_BIT(pin)  (pin  == 5 ? DDB5  : DDC6)
#define DIR_REG_BIT_button(pin) (pin  == 1 ? DDB1 : DDC2)

#define LED_OUT_REG PORT_REG(LED_PORT)
#define LED_DIR_REG DIR_REG(LED_PORT)

#define LED_OUT_REG_BIT  PORT_REG_BIT(LED_PIN)
#define LED_DIR_REG_BIT DIR_REG_BIT(LED_PIN)

#define Button_OUT_REG PORT_REG(Button_PORT)
#define Button_DIR_REG DIR_REG(Button_PORT)

#define Button_OUT_REG_BIT  PORT_REG_BIT_button(Button_PIN)
#define Button_DIR_REG_BIT DIR_REG_BIT_button(Button_PIN)




