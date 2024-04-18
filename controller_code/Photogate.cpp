#include "Photogate.h"

Photogate::Photogate(unsigned short detect_pin, unsigned short input_pin) {
  this->detect_pin = detect_pin;
  this->input_pin = input_pin;
  pinMode(detect_pin, INPUT);
  pinMode(input_pin, INPUT);
}

bool Photogate::connected() {
  return !digitalRead(detect_pin);
}

GateStatus gate_status;