#include "Programs.h"

void setupMode(Photogate& gate_1, Photogate& gate_2) {
  if (mode < NUM_ONE_GATE_MODES) {
    if (gate_1.connected()) {
      attachInterrupt(digitalPinToInterrupt(gate_1.input_pin), getMillis, RISING);
    }
    else {
      attachInterrupt(digitalPinToInterrupt(gate_2.input_pin), getMillis, RISING);
    }
  }
  else {
    //set up 2 gate modes
  }
}

long getMillis() {
  Serial.println(millis());
}