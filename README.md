# Metronome Project

## Introduction

This repo provides the implementation of a digital metronome using the ATmega328p independent of the board configuration. To choose a particular version of the board, with the particular choice of input and output ports set a compiler flag as shown in the `ioMapping.h` file.

> Side Note: an implementation using the NUCLEO-F401RE can be found in the folder `Implementation on NUCLEO-F401RE`.

Required hardware:
- Button: To change the BPM of the metronome.
- LED: Shows the metronome's pulse.
- Buzzer **(to be implemented in the future)**: to create the click of the metronome.
- Display **(to be implemented in the future)**: displays the current BPM of the metronome.

![image](Digital_Metronome_Architecture.png) 

*Figure 1: Digital Metronome Architecture*

Interesting features of the implementation:
- Button Debouncing: Using a timer to periodically check the status of the button. If a certain number of samples agree that the button was pressed then the event *"button_pressed"* is aknowledged.
- Metronome tick according to a timer.
- Now the user can choose between the following BPM's by pressing the button: [60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160].

## Using the Arduino Uno (ATmega328P)

Hardware interface specified in the ioMapping_v1.h and ioMapping.h files. 

Ex for the version 1 of the board (`ioMapping_v1.h`)
Required hardware:
- Button: Pin D9, which corresponds to the pin PB1 in the microcontroller. The timer 0 requests checking the reading periodically.
- LED: Pin D13, which corresponds to the pin PB5 in the microcontroller. The timer 1 requests a toggle of the LED.
- Buzzer **(to implemented in the future)**: to be determined.
- Display **(to implemented in the future)**: to be determined.

### Usage
Set the compiler flag in the `platformio.ini` before building the project with the following:

```
build_flags = -DCOMPILING_FOR_V1
``` 
