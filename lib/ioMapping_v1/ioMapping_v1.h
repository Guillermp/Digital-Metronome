// ---- Board version 1 --- //
#include <avr/io.h>
#include <avr/interrupt.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

// Registers and bits for the digital OUTPUT needed for the LED
#define LED_OUT_REG PORTB
#define LED_DIR_REG DDRB

#define LED_OUT_REG_BIT  PORTB5
#define LED_DIR_REG_BIT DDB5 // PB5 which is D13 in the Arduino Uno board

// Registers and bits for the digital OUTPUT needed for the Buzzer
#define Buzzer_OUT_REG PORTB
#define Buzzer_DIR_REG DDRB

#define Buzzer_OUT_REG_BIT  PORTB0
#define Buzzer_DIR_REG_BIT DDB0 // PB0 which is D8 in the Arduino Uno board


// Registers and bits for the digital INPUT needed for the Buttons
// For the button that increases the BPM of the Metornome
#define ButtonUp_OUT_REG PORTB
#define ButtonUp_DIR_REG DDRB 

#define ButtonUp_OUT_REG_BIT PORTB1
#define ButtonUp_DIR_REG_BIT DDB1 // PB1 which is D9 in the Arduino Uno board

#define ButtonUp_Read_REG PINB
#define ButtonUp_Read_REG_BIT PINB1


// For the button that decreases the BPM of the Metornome
#define ButtonDown_OUT_REG PORTB
#define ButtonDown_DIR_REG DDRB 

#define ButtonDown_OUT_REG_BIT PORTB2
#define ButtonDown_DIR_REG_BIT DDB2 // PB1 which is D9 in the Arduino Uno board

#define ButtonDown_Read_REG PINB
#define ButtonDown_Read_REG_BIT PINB2


#define Metronome_Compare_Reg OCR1A
#define Metronome_Counter_Reg TCNT1

/*
static const uint8_t portLED = _SFR_IO_ADDR(LED_OUT_REG);
static const uint8_t portBuzzer = _SFR_IO_ADDR(Buzzer_OUT_REG);
static_assert(portLED == portBuzzer, "Choose the same port for the LED and the Buzzer");
*/
#define Shared_OUT_REG LED_OUT_REG

/*
static const uint8_t ReadButtonUp = _SFR_IO_ADDR(ButtonUp_Read_REG);
static const uint8_t ReadButtonDown = _SFR_IO_ADDR(ButtonDown_Read_REG);
static_assert(portLED == portBuzzer, "Choose the same port for the Buttons");
*/

#define Shared_Button_READ ButtonDown_Read_REG
// Timer related code
// Function to setup the timer for this hardware
// Setup timer 0 to trigger an interrupt once per ms
void setupTimer0(void);

#define COMP_Interrupt_Timer0 TIMER0_COMPA_vect

void setupTimer1(void);

#define COMP_Interrupt_Timer1 TIMER1_COMPA_vect
#define Prescaler_Timer1 1024 // Make sure is consistent
#define F_clock_Timer1 16000000 // Make sure is consistent

#ifdef __cplusplus
}
#endif