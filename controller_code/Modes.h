#ifndef MODES_H
#define MODES_H

#include "Photogate.h"

struct Mode {
  String name;
  unsigned short x;
  unsigned short y;
};

const unsigned short NUM_ONE_GATE_MODES = 5;
const unsigned short NUM_TWO_GATE_MODES = 2;

extern const Mode one_gate_modes[NUM_ONE_GATE_MODES];
extern const Mode two_gate_modes[NUM_TWO_GATE_MODES];

extern short mode;

extern volatile unsigned long microseconds_1;
extern volatile unsigned long microseconds_2;

void setupMode(Photogate& gate_1, Photogate& gate_2);
void ISR_getMicros1();
void ISR_getMicros2();

#endif