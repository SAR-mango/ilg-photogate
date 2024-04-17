#include "Modes.h"

const Mode one_gate_modes[NUM_ONE_GATE_MODES] = {
  {"Single", 0, 11},
  {"Stopwatch", 0, 22},
  {"Pendulum", 65, 0},
  {"Avg. Time", 65, 11},
  {"Count", 65, 22}
};

const Mode two_gate_modes[NUM_TWO_GATE_MODES] = {
  {"Average", 0, 11},
  {"Time of Flight", 0, 22}
};

short mode;