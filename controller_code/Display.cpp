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
  if (status == ONE) {
    disp.clearDisplay();
    boxedText("One Gate", -2, -2);
    for (const auto i : one_gate_modes) {
      disp.setCursor(i.x, i.y);
      disp.print(i.name);
    }
  }
  else if (status == BOTH) {
    disp.clearDisplay();
    boxedText("Two Gates", -2, -2);
    for (const auto i : two_gate_modes) {
      disp.setCursor(i.x, i.y);
      disp.print(i.name);
    }
  }
  else {
    disp.clearDisplay();
    centeredText("No Gates Connected");
  }
}

void Display::selectedDot(EncoderData data, GateStatus status) {
  if (status == ONE) {
    const unsigned short mode_num = abs(data.position % num_one_gate_modes);
    unsigned short last_mode_num;
    unsigned short next_mode_num;
    if (mode_num == 0) {
      last_mode_num = num_one_gate_modes;
    }
    else {
      last_mode_num = mode_num - 1;
    }
    if (mode_num == 4) {
      next_mode_num = 0;
    }
    else {
      next_mode_num = mode_num + 1;
    }
    disp.fillRect(one_gate_modes[last_mode_num].x + 6*one_gate_modes[last_mode_num].name.length() + 2, one_gate_modes[last_mode_num].y + 3, 3, 3, SSD1306_BLACK);
    disp.fillRect(one_gate_modes[next_mode_num].x + 6*one_gate_modes[next_mode_num].name.length() + 2, one_gate_modes[next_mode_num].y + 3, 3, 3, SSD1306_BLACK);
    disp.fillRect(one_gate_modes[mode_num].x + 6*one_gate_modes[mode_num].name.length() + 2, one_gate_modes[mode_num].y + 3, 3, 3, SSD1306_WHITE);
    disp.display();
  }
  else if (status == BOTH) {
  }
  else {
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
    selectedDot(enc_data, gate_status);
  }
}