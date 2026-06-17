#pragma once
#include "ioMapping.h"

#ifdef __cplusplus
extern "C" {
#endif

#define setupTimerMetronome setupTimer1
#define Metronome_COMPA_vect COMP_Interrupt_Timer1
#define PrescalerMetronome Prescaler_Timer1
#define F_clockMetronome F_clock_Timer1


#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

uint8_t step_increase(uint8_t current_step, uint8_t array_len);
uint8_t step_decrease(uint8_t current_step, uint8_t array_len);

void initializeMetronomeBPM(void);

void increaseMetronomeRate(void);

void decreaseMetronomeRate(void);

double getMetronomeBPM(void);

#ifdef __cplusplus
}
#endif