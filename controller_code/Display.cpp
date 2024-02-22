#include "Display.h"

Display::Display(void) {
  disp = {SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST};
  disp.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR);
  disp.clearDisplay();
}

void Display::initScreen(void) {
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setTextColor(SSD1306_WHITE);
  disp.setCursor(21,0); // todo: use center text fn
  disp.println(F("ILG Photogate"));
  disp.setCursor(15,20);
  disp.println(F("Software Rev. 1.0"));
  disp.display();
}