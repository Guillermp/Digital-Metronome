#include "ioMapping.h"

#define setupTimerMetronome setupTimer1

void modifyMetronomeRate(void) {
    step++;
    if (step >= 5) step = 0;
    cli();
    Metronome_Compare_Reg = values[step];
    Metronome_Counter_Reg = 0;
    sei();
}