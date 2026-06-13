#pragma once
// ---- Using the ATmega328P ---- //
// ---- Use a compiler flag to choose the board version --- //
#ifdef COMPILING_FOR_V1
  #include "ioMapping_v1.h"

#elif defined(COMPILING_FOR_V2)
  #include "ioMapping_v2.h"

#else
  #error "No I/O map selected for the board. What is your target?"
  
#endif





