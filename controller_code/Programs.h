#ifndef PROGRAMS_H
#define PROGRAMS_H

#include "Photogate.h"
#include "Encoder.h"

extern volatile unsigned long microseconds_1;
extern volatile unsigned long microseconds_2;

enum TrigMode {TM_RISING, TM_FALLING, TM_CHANGE, TM_NONE};
struct TriggerConfig {
  TrigMode tm_1;
  TrigMode tm_2;
};

void setupInterrupts(Photogate& gate_1, Photogate& gate_2, TriggerConfig& trig_conf);
void ISR_getMicros1();
void ISR_getMicros2();

unsigned long single();
unsigned long stopwatch();
unsigned long pendulum();
unsigned long t_avg_1();
unsigned long count();

unsigned long t_avg_2();
unsigned long time_flight();

volatile unsigned long* getGateVar();

#endif