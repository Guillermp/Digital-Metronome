#include "metronome.h"

volatile static uint8_t step = 0;

// Compare values for timer 1 to achieve the desired BPMs (check the documentation)
const static double values[] = {
    15624,
    13392,
    11718,
    10416,
    9374,
    8522,
    7812,
    7211,
    6695,
    6249,
    5858
};

void initializeMetronomeBPM(void){
    // set the BPM to the initial value of the table
    cli();
    step = 0;
    Metronome_Compare_Reg = values[0];
    Metronome_Counter_Reg = 0;
    sei();

}

// Pure logic functions
uint8_t step_increase(uint8_t current_step, uint8_t array_len) {
    current_step++;
    if (current_step >= array_len) current_step = 0;
    return current_step;
}

uint8_t step_decrease(uint8_t current_step, uint8_t array_len) {
    if (current_step == 0)
        return array_len - 1;
    return current_step - 1;
}

void increaseMetronomeRate(void) {
    step = step_increase(step, ARRAY_LEN(values));
    cli();
    Metronome_Compare_Reg = values[step];
    Metronome_Counter_Reg = 0;
    sei();
}

void decreaseMetronomeRate(void) {
    step = step_decrease(step, ARRAY_LEN(values));
    cli();
    Metronome_Compare_Reg = values[step];
    Metronome_Counter_Reg = 0;
    sei();
}
double getMetronomeBPM(void) {
    double bps = F_clockMetronome/(PrescalerMetronome*(values[step]+1));
    return bps*60;

}