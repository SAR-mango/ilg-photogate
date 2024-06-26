#include "Programs.h"

volatile unsigned long microseconds_1 = 0;
volatile unsigned long microseconds_2 = 0;

void setupInterrupts(Photogate& gate_1, Photogate& gate_2, TriggerConfig& trig_conf) {
  detachInterrupt(digitalPinToInterrupt(gate_1.input_pin));
  detachInterrupt(digitalPinToInterrupt(gate_2.input_pin));
  switch (trig_conf.tm_1) {
    case TM_RISING:
      attachInterrupt(digitalPinToInterrupt(gate_1.input_pin), ISR_getMicros1, RISING);
      break;
    case TM_FALLING:
      attachInterrupt(digitalPinToInterrupt(gate_1.input_pin), ISR_getMicros1, FALLING);
      break;
    case TM_CHANGE:
      attachInterrupt(digitalPinToInterrupt(gate_1.input_pin), ISR_getMicros1, CHANGE);
      break;
    default:
      break;
  }
  switch (trig_conf.tm_2) {
    case TM_RISING:
      attachInterrupt(digitalPinToInterrupt(gate_2.input_pin), ISR_getMicros2, RISING);
      break;
    case TM_FALLING:
      attachInterrupt(digitalPinToInterrupt(gate_2.input_pin), ISR_getMicros2, FALLING);
      break;
    case TM_CHANGE:
      attachInterrupt(digitalPinToInterrupt(gate_2.input_pin), ISR_getMicros2, CHANGE);
      break;
    default:
      break;
  }
}

void ISR_getMicros1() {
  microseconds_1 = micros();
}

void ISR_getMicros2() {
  microseconds_2 = micros();
}

unsigned long single() {
  volatile unsigned long* time_ptr = getGateVar();
  volatile unsigned long time_1 = *time_ptr;
  while (time_1 == *time_ptr) {}
  time_1 = *time_ptr;
  while (time_1 == *time_ptr) {}
  return *time_ptr - time_1;
}
unsigned long stopwatch() {
  volatile unsigned long* time_ptr = getGateVar();
  *time_ptr = micros();
  volatile unsigned long time_1 = *time_ptr;
  while (time_1 == *time_ptr) {}
  return *time_ptr - time_1;
}
unsigned long pendulum() {
  // unsigned long* time_ptr = getGateVar();
  // unsigned long time_1 = *time_ptr;
  // Serial.println(*time_ptr);
  // while (time_1 == *time_ptr) {}
  // Serial.println(*time_ptr);
  // unsigned long temp_period = *time_ptr - time_1;
  // time_1 = *time_ptr;
  // while (time_1 == *time_ptr) {}
  // Serial.println("num 3");
  // temp_period += (*time_ptr - time_1);
  // period += temp_period;
  // period /= n;
  // n += 1.0;
}
unsigned long t_avg_1() {
}
unsigned long count() {
}

unsigned long t_avg_2() {
}
unsigned long time_flight() {
}

volatile unsigned long* getGateVar() {
  if (gate_status == GATE1) {
    return &microseconds_1;
  }
  return &microseconds_2;
}