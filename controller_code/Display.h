#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

struct Coords {
  unsigned short x = 0;
  unsigned short y = 0;
};

class Display {
  const unsigned short SCREEN_WIDTH = 128;
  const unsigned short SCREEN_HEIGHT = 32;
  const short OLED_RST = -1;
  const byte SCREEN_ADDR = 0x3C;
  Adafruit_SSD1306 disp;
  Coords centerText // todo: write fn to center text

  public:
  Display(void);
  void initScreen(void);
  void menuSelect(void);
};

#endif