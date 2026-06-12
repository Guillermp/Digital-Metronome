// ---- Using the Arduino Uno Board --- //

// I need to define the port and the register in the port that I should write to to configure the pin I want to use for the LED
#define LED_PORT 1
#define LED_PIN 5 // PB5 which is D13 in the arduino
#define Button_PORT LED_PORT
#define Button_PIN 1 // PB1 which is D9
#define Metronome_Compare_Reg OCR1A
#define Metronome_Counter_Reg TCNT1

// Timer related code

// Function to setup the timer for this hardware

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

volatile uint8_t step = 0;

const uint16_t values[] = {
    15624,
    7812,
    3906,
    1953,
    976
};

