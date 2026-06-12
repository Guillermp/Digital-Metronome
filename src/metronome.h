#include "ioMapping.h"

#define setupTimerMetronome setupTimer1

volatile uint8_t step = 0;

// 
const uint16_t values[] = {
    15624,
    7812,
    3906,
    1953,
    976
};
void modifyMetronomeRate(void) {
    step++;
    if (step >= 5) step = 0;
    cli();
    Metronome_Compare_Reg = values[step];
    Metronome_Counter_Reg = 0;
    sei();
}