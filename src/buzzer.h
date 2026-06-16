#include "ioMapping.h"

void initBuzzer () {
    Buzzer_DIR_REG |= (1 << Buzzer_DIR_REG_BIT);  // set pin direction to output
}
