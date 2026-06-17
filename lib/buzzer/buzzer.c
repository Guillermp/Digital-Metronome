#include "buzzer.h"

void initBuzzer (void) {
    Buzzer_DIR_REG |= (1 << Buzzer_DIR_REG_BIT);  // set pin direction to output
}