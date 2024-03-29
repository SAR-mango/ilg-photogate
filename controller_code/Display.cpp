#include "Display.h"

void Display::centeredText(String text, unsigned short level = 5) {
  if (0 <= level && level <= 3) {
    disp.setCursor((SCREEN_WIDTH - CHAR_WIDTH * text.length()) / 2, CHAR_HEIGHT * level);
  }
  else {
    disp.setCursor((SCREEN_WIDTH - CHAR_WIDTH * text.length()) / 2, SCREEN_HEIGHT / 2 - CHAR_HEIGHT / 2);
  }
  disp.println(text);
}

void Display::boxedText(String text, short x, short y) {
  unsigned short rect_x = x;
  unsigned short rect_y = y;
  unsigned short rect_w;
  unsigned short rect_h;
  disp.getTextBounds(text, x, y, &rect_x, &rect_y, &rect_w, &rect_h);
  disp.drawRect(rect_x, rect_y, rect_w + 3, rect_h + 3, SSD1306_WHITE);
  disp.setCursor(x + 2, y + 2);
  disp.println(text);
}

GateStatus Display::checkGates(Photogate& gate_1, Photogate& gate_2) {
  if (gate_1.connected() && gate_2.connected()) {
    return BOTH;
  }
  if (gate_1.connected() || gate_2.connected()) {
    return ONE;
  }
  return NONE;
}

void Display::displayOptions(GateStatus status) {
  if (status == BOTH) {
    disp.clearDisplay();
    boxedText("Two Gates", -2, -2);
    disp.setCursor(0,11);
    disp.println("Average");
    disp.setCursor(0,22);
    disp.println("Time of Flight");
  }
  else if (status == ONE) {
    disp.clearDisplay();
    boxedText("One Gate", -2, -2);
    disp.setCursor(0,11);
    disp.print("Single");
    disp.setCursor(0,22);
    disp.print("Stopwatch");
    disp.setCursor(65,0);
    disp.print("Pendulum");
    disp.setCursor(65,11);
    disp.print("Continuous");
    disp.setCursor(65,22);
    disp.print("Count");
  }
  else {
    disp.clearDisplay();
    centeredText("No Gates Connected");
  }
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
  centeredText("ILG Photogate", 0);
  centeredText("Firmware Rev. 1.0", 2);
  disp.display();
}

void Display::modeSelect(Photogate& gate_1, Photogate& gate_2) {
  disp.clearDisplay();
  GateStatus last_gate_status = checkGates(gate_1, gate_2);
  GateStatus gate_status = last_gate_status;
  displayOptions(last_gate_status);
  disp.display();
  EncoderData enc_data;
  while (true) {
    gate_status = checkGates(gate_1, gate_2);
    if (gate_status != last_gate_status) {
      displayOptions(gate_status);
      disp.display();
      last_gate_status = gate_status;
    }
    enc.listen(enc_data);
    selectedDot(enc, gate_status);
  }
}