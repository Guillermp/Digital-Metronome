#include "metronome.h"

volatile static uint8_t step = 0;

// Remember that the LED is toggles every timer interrupt so we need to ticks for one tick of the metronome!!!
const static double values[] = {
    7811.5,
    6695.4,
    5858.4,
    5207.3,
    4686.5,
    4260.4,
    3905.3,
    3604.8,
    3347.2,
    3124.0,
    2928.7
};

void initializeMetronomeBPM(void){
    // set the BPM to the initial value of the table
    cli();
    Metronome_Compare_Reg = values[0];
    Metronome_Counter_Reg = 0;
    sei();

}

void increaseMetronomeRate(void) {
    step++;
    if (step >= ARRAY_LEN(values)) step = 0;
    cli();
    Metronome_Compare_Reg = values[step];
    Metronome_Counter_Reg = 0;
    sei();
}

void decreaseMetronomeRate(void) {
    if (step == 0)
        step = ARRAY_LEN(values) - 1;
    else
        step--;
    cli();
    Metronome_Compare_Reg = values[step];
    Metronome_Counter_Reg = 0;
    sei();
}
double getMetronomeBPM(void) {
    double bps = F_clockMetronome/(PrescalerMetronome*(values[step]+1));
    return bps*60;

}