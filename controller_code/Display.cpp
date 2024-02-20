#include "Display.h"

Display::Display(void) {
  disp = display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);
  disp.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR));
  disp.clearDisplay();
}

