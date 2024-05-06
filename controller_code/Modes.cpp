#include "Modes.h"

const Mode one_gate_modes[NUM_ONE_GATE_MODES] = {
  {"Single", 0, 11, &single, false},
  {"Stopwatch", 0, 22, &stopwatch, false},
  {"Pendulum", 65, 0, &pendulum, true},
  {"Avg. Time", 65, 11, &t_avg_1, true},
  {"Count", 65, 22, &count, true}
};

const Mode two_gate_modes[NUM_TWO_GATE_MODES] = {
  {"Avg. Time", 0, 11, &t_avg_2, true},
  {"Time of Flight", 0, 22, &time_flight, false}
};

short mode;