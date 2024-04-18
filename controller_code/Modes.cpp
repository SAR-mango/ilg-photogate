#include "Modes.h"
#include "Programs.h"

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

volatile unsigned long microseconds_1;
volatile unsigned long microseconds_2;

void setupInterrupts(Photogate& gate_1, Photogate& gate_2) {
  if (gate_status == GATE1) {
    attachInterrupt(digitalPinToInterrupt(gate_1.input_pin), ISR_getMicros1, RISING);
  }
  else if (gate_status == GATE2) {
    attachInterrupt(digitalPinToInterrupt(gate_2.input_pin), ISR_getMicros2, RISING);
  }
  else {
    attachInterrupt(digitalPinToInterrupt(gate_1.input_pin), ISR_getMicros1, RISING);
    attachInterrupt(digitalPinToInterrupt(gate_2.input_pin), ISR_getMicros2, RISING);
  }
}

void ISR_getMicros1() {
  microseconds_1 = micros();
}

void ISR_getMicros2() {
  microseconds_2 = micros();
}