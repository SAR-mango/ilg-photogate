#include "Modes.h"

Mode one_gate_modes[5] = {
  {"Single", 0, 11, "a", "b", "c"},
  {"Stopwatch", 0, 22, "a", "b", "c"},
  {"Pendulum", 65, 0, "a", "b", "c"},
  {"Continuous", 65, 11, "a", "b", "c"},
  {"Count", 65, 22, "a", "b", "c"}
};

Mode two_gate_modes[2] = {
  {"Average", 0, 11, "a", "b", "c"},
  {"Time of Flight", 0, 22, "a", "b", "c"}
};