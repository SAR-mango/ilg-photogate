#ifndef ENCODER_H
#define ENCODER_H

#include <Adafruit_seesaw.h>
#include <seesaw_neopixel.h>

struct EncoderData {
  long position = 0;
  bool button_pressed = false;
};

class Encoder {
  const unsigned short ENC_INTERNAL_SWITCH = 24;
  const unsigned short ENC_INTERNAL_NEOPIX = 6;
  const byte ENC_ADDR = 0x36;
  Adafruit_seesaw encoder;
  seesaw_NeoPixel neopixel;
  long encoder_position = 0;

public:
  Encoder(bool enable_neopixel = false);
  EncoderData listen(EncoderData& data);
};

#endif