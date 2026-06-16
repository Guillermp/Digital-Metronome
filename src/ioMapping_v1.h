// ---- Board version 1 --- //
#include <avr/io.h>
#include <avr/interrupt.h>

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


// Registers and bits for the digital INPUT needed for the Button
#define Button_OUT_REG PORTB
#define Button_DIR_REG DDRB 

#define Button_OUT_REG_BIT  PORTB1
#define Button_DIR_REG_BIT DDB1 // PB1 which is D9 in the Arduino Uno board


#define Metronome_Compare_Reg OCR1A
#define Metronome_Counter_Reg TCNT1

// Timer related code
// Function to setup the timer for this hardware
// Setup timer 0 to trigger an interrupt once per ms
void setupTimer0(void) {
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0  = 0;

    // Compare value (8-bit timer → max 255)
    OCR0A = 249;

    // CTC mode (Clear Timer on Compare Match)
    TCCR0A |= (1 << WGM01);

    // Enable Compare Match A interrupt
    TIMSK0 |= (1 << OCIE0A);

    // Prescaler = 64
    TCCR0B |= (1 << CS01) | (1 << CS00);
}

#define COMP_Interrupt_Timer0 TIMER0_COMPA_vect

static inline void setupTimer1(void) {
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
    // Compare target count (16-bit timer → max 65535)
    OCR1A = 15624;

    // Timer setup to compare mode
    TCCR1B |= (1 << WGM12);

    // Setup Compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Set prescale to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
}

#define COMP_Interrupt_Timer1 TIMER1_COMPA_vect
#define Prescaler_Timer1 1024 // Make sure is consistent
#define F_clock_Timer1 16000000 // Make sure is consistent