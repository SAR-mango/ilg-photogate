#include "Modes.h"

const Mode one_gate_modes[num_one_gate_modes] = {
  {"Single", 0, 11, "Records time between", "one interruption", "and the next."},
  {"Stopwatch", 0, 22, "a", "b", "c"},
  {"Pendulum", 65, 0, "a", "b", "c"},
  {"Avg. Time", 65, 11, "a", "b", "c"},
  {"Count", 65, 22, "a", "b", "c"}
};

const Mode two_gate_modes[num_two_gate_modes] = {
  {"Average", 0, 11, "a", "b", "c"},
  {"Time of Flight", 0, 22, "a", "b", "c"}
};

short mode;