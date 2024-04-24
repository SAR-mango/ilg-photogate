#include "Modes.h"

const Mode one_gate_modes[NUM_ONE_GATE_MODES] = {
  {"Single", 0, 11, "milliseconds", &single},
  {"Stopwatch", 0, 22, "milliseconds", &stopwatch},
  {"Pendulum", 65, 0, "milliseconds", &pendulum},
  {"Avg. Time", 65, 11, "milliseconds", &t_avg_1},
  {"Count", 65, 22, "interruptions", &count}
};

const Mode two_gate_modes[NUM_TWO_GATE_MODES] = {
  {"Avg. Time", 0, 11, "milliseconds", &t_avg_2},
  {"Time of Flight", 0, 22, "milliseconds", &time_flight}
};

short mode;