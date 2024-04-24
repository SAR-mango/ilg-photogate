#ifndef PROGRAMS_H
#define PROGRAMS_H

#include "Photogate.h"

extern volatile unsigned long microseconds_1;
extern volatile unsigned long microseconds_2;

void setupInterrupts(Photogate& gate_1, Photogate& gate_2);
void ISR_getMicros1();
void ISR_getMicros2();

unsigned long single();
unsigned long stopwatch();
unsigned long pendulum();
unsigned long t_avg_1();
unsigned long count();

unsigned long t_avg_2();
unsigned long time_flight();

#endif