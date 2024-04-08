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

const unsigned short num_one_gate_modes = 5;
const unsigned short num_two_gate_modes = 2;

extern const Mode one_gate_modes[num_one_gate_modes];
extern const Mode two_gate_modes[num_two_gate_modes];

extern short mode;

#endif