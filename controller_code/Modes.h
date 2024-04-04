#ifndef MODES_H
#define MODES_H
#include <Arduino.h>

struct Mode {
  String name;
  short x;
  short y;
  String d1;
  String d2;
  String d3;
};

extern Mode one_gate_modes[5];
extern Mode two_gate_modes[2];

#endif