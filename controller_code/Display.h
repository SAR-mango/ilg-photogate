#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Encoder.h"
#include "Photogate.h"
#include "Modes.h"

enum GateStatus {BOTH, ONE, NONE};

class Display {
  const unsigned short SCREEN_WIDTH = 128;
  const unsigned short SCREEN_HEIGHT = 32;
  const unsigned short CHAR_WIDTH = 6;
  const unsigned short CHAR_HEIGHT = 8;
  const short OLED_RST = -1;
  const byte SCREEN_ADDR = 0x3C;
  Adafruit_SSD1306 disp;
  Encoder enc;
  GateStatus gate_status;

  void centeredText(String text, unsigned short level = 5);
  void boxedText(String text, short x, short y);
  GateStatus checkGates(Photogate& gate_1, Photogate& gate_2);
  void displayOptions();
  short getSelectedMode(EncoderData data);
  bool modeConfScreen();

  public:
  Display(void);
  void initScreen(void);
  void modeSelect(Photogate& gate_1, Photogate& gate_2);
};

#endif