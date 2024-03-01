#include "Display.h"

Coordinates Display::centerText(String text, unsigned short level) {
  Coordinates coords;
  coords.x = (128 - 6 * text.length()) / 2;
  coords.y = 8 * level;
  return coords;
}

void Display::rectAroundText(String text, unsigned short x, unsigned short y) {
  unsigned short rect_x = x;
  unsigned short rect_y = y;
  unsigned short rect_w;
  unsigned short rect_h;
  disp.getTextBounds(text, x, y, &rect_x, &rect_y, &rect_w, &rect_h);
  disp.drawRect(rect_x, rect_y, rect_w, rect_h, SSD1306_WHITE);
}

Display::Display(void) {
  disp = {SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST};
  disp.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR);
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setTextColor(SSD1306_WHITE);
}

void Display::initScreen(void) {
  disp.clearDisplay();
  Coordinates coords = centerText("ILG Photogate", 0);
  disp.setCursor(coords.x, coords.y);
  disp.println(F("ILG Photogate"));
  coords = centerText("Firmware Rev. 1.0", 2);
  disp.setCursor(coords.x, coords.y);
  disp.println(F("Firmware Rev. 1.0"));
  disp.display();
}

void Display::menuSelect(Photogate& gate_1, Photogate& gate_2) {
  disp.clearDisplay();
  disp.setCursor(0,0);
  if (gate_1.connected() && gate_2.connected()) {
    rectAroundText("test", 0, 0);
    disp.println(F("Two gates connected."));
    disp.println(F("Time of Flight"));
    disp.println(F("Average"));
  }
  else {
    disp.println(F("One gate"));
    disp.println(F("Single    Avg"));
    disp.println(F("Pendulum"));
    disp.println(F("Stopwatch"));
    disp.println(F("Count"));
  }
  //enc.listen(enc_data);
  //disp.setCursor(0,0);
  //disp.println(F("More options below"));
  disp.display();
}