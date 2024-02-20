#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display {
  const unsigned short SCREEN_WIDTH = 128;
  const unsigned short SCREEN_HEIGHT = 32;
  const short OLED_RST = -1;
  const unsigned byte SCREEN_ADDR = 0x3C;
  Adafruit_SSD1306 disp;

  public:
  Display(void);
  void initScreen(void);
  void menuSelect(void);
};