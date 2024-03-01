#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Encoder.h"
#include "Coordinates.h"
#include "Photogate.h"

class Display {
  const unsigned short SCREEN_WIDTH = 128;
  const unsigned short SCREEN_HEIGHT = 32;
  const short OLED_RST = -1;
  const byte SCREEN_ADDR = 0x3C;
  Adafruit_SSD1306 disp;
  Encoder enc;
  EncoderData enc_data;

  Coordinates centerText(String text, unsigned short level);
  void rectAroundText(String text, unsigned short x, unsigned short y);

  public:
  Display(void);
  void initScreen(void);
  void menuSelect(Photogate& gate_1, Photogate& gate_2);
};

#endif