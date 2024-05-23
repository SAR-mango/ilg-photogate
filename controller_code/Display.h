#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Photogate.h"
#include "Modes.h"

class Display {
  const unsigned short SCREEN_WIDTH = 128;
  const unsigned short SCREEN_HEIGHT = 32;
  const unsigned short CHAR_WIDTH = 6;
  const unsigned short CHAR_HEIGHT = 8;
  const short OLED_RST = -1;
  const byte SCREEN_ADDR = 0x3C;
  Adafruit_SSD1306 disp;
  Encoder enc;
  EncoderData enc_data;

  void centeredText(String text, unsigned short level = 5);
  void boxedText(String text, short x, short y);
  GateStatus checkGates(Photogate& gate_1, Photogate& gate_2);
  void displayOptions();
  short getSelectedMode();
  bool confirmMode();
  void trigSelect(Photogate& gate_1, Photogate& gate_2);

  public:
  Display();
  void initScreen();
  void configure(Photogate& gate_1, Photogate& gate_2);
  void run();
};

#endif