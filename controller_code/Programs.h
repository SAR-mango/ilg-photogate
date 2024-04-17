#ifndef PROGRAMS_H
#define PROGRAMS_H

#include <Arduino.h>
#include "Modes.h"
#include "Photogate.h"

void setupMode(Photogate& gate_1, Photogate& gate_2);
long getMillis();

#endif