#include "ioMapping.h"

void initButton(void) {
    Button_DIR_REG &= ~(1 << Button_DIR_REG_BIT); // set pin direction to input
}
