#ifndef MODES_H
#define MODES_H

#include <Arduino.h>

struct Mode {
  String name;
  unsigned short x;
  unsigned short y;
  String d1;
  String d2;
  String d3;

};

const unsigned short NUM_ONE_GATE_MODES = 5;
const unsigned short NUM_TWO_GATE_MODES = 2;

extern const Mode one_gate_modes[NUM_ONE_GATE_MODES];
extern const Mode two_gate_modes[NUM_TWO_GATE_MODES];

extern short mode;

#endif