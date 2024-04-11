#ifndef PHOTOGATE_H
#define PHOTOGATE_H

#include <Arduino.h>

class Photogate {
  unsigned short detect_pin = 0;
  unsigned short input_pin = 0;

  public:
  Photogate(unsigned short detect_pin, unsigned short input_pin);
  bool connected();
};

#endif