#include "ioMapping_v1.h"

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

void setupTimer1(void) {
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