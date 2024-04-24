#include "Programs.h"

volatile unsigned long microseconds_1 = 0;
volatile unsigned long microseconds_2 = 0;

void setupInterrupts(Photogate& gate_1, Photogate& gate_2) {
  detachInterrupt(digitalPinToInterrupt(gate_1.input_pin));
  detachInterrupt(digitalPinToInterrupt(gate_2.input_pin));
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

unsigned long single() {
  if (gate_status == GATE1) {
    Serial.println(microseconds_1);
    unsigned long time_1 = microseconds_1;
    while (microseconds_1 == time_1) {}
    Serial.println(microseconds_1);
    time_1 = microseconds_1;
    while (microseconds_1 == time_1) {}
    Serial.println(microseconds_1 - time_1);
    return microseconds_1 - time_1;
  }
  else {
  }
}
unsigned long stopwatch() {
}
unsigned long pendulum() {
}
unsigned long t_avg_1() {
}
unsigned long count() {
}

unsigned long t_avg_2() {
}
unsigned long time_flight() {
}