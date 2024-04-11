#include "Display.h"

void Display::centeredText(String text, unsigned short level = 5) {
  if (0 <= level && level <= 3) {
    disp.setCursor((SCREEN_WIDTH - CHAR_WIDTH * text.length()) / 2, CHAR_HEIGHT * level);
  } else {
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

void Display::displayOptions() {
  disp.clearDisplay();
  if (gate_status == ONE) {
    boxedText("One Gate", -2, -2);
    for (const auto i : one_gate_modes) {
      disp.setCursor(i.x, i.y);
      disp.print(i.name);
    }
  } else if (gate_status == BOTH) {
    boxedText("Two Gates", -2, -2);
    for (const auto i : two_gate_modes) {
      disp.setCursor(i.x, i.y);
      disp.print(i.name);
    }
  } else {
    centeredText("No Gates Connected");
  }
  disp.display();
}

short Display::getSelectedMode() {
  if (gate_status == ONE) {
    const unsigned short mode_num = abs(enc_data.position % NUM_ONE_GATE_MODES);
    for (unsigned short i = 0; i < NUM_ONE_GATE_MODES; i++) {
      if (i == mode_num) {
        disp.fillRect(one_gate_modes[i].x + 6 * one_gate_modes[i].name.length() + 2, one_gate_modes[i].y + 3, 3, 3, SSD1306_WHITE);
      } else {
        disp.fillRect(one_gate_modes[i].x + 6 * one_gate_modes[i].name.length() + 2, one_gate_modes[i].y + 3, 3, 3, SSD1306_BLACK);
      }
    }
    disp.display();
    return mode_num;
  } else if (gate_status == BOTH) {
    const unsigned short mode_num = abs(enc_data.position % NUM_TWO_GATE_MODES);
    for (unsigned short i = 0; i < NUM_TWO_GATE_MODES; i++) {
      if (i == mode_num) {
        disp.fillRect(two_gate_modes[i].x + 6 * two_gate_modes[i].name.length() + 2, two_gate_modes[i].y + 3, 3, 3, SSD1306_WHITE);
      } else {
        disp.fillRect(two_gate_modes[i].x + 6 * two_gate_modes[i].name.length() + 2, two_gate_modes[i].y + 3, 3, 3, SSD1306_BLACK);
      }
    }
    disp.display();
    return NUM_ONE_GATE_MODES + mode_num;
  } else {
    return -1;
  }
}

bool Display::confirmMode() {
  disp.clearDisplay();
  if (mode == -1) {
    return false;
  }
  if (0 <= mode && mode <= NUM_ONE_GATE_MODES - 1) {
    centeredText(one_gate_modes[mode].name, 0);
  }
  else {
    centeredText(two_gate_modes[mode - NUM_ONE_GATE_MODES].name, 0);
  }
  centeredText("OK    BACK", 2);
  while (enc_data.button_pressed) {
    enc.listen(enc_data);
  }
  do {
    if (enc_data.position % 2 == 0) {
      disp.fillRect(48, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_WHITE);
      disp.fillRect(96, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_BLACK);
      disp.display();
    }
    else {
      disp.fillRect(48, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_BLACK);
      disp.fillRect(96, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_WHITE);
      disp.display();
    }
    enc.listen(enc_data);
  } while (!enc_data.button_pressed);
  return enc_data.position % 2 == 0;
}

Display::Display() {
  disp = {SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST};
  disp.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR);
  disp.clearDisplay();
  disp.setTextSize(1);
  disp.setTextColor(SSD1306_WHITE);
}

void Display::initScreen() {
  disp.clearDisplay();
  centeredText("ILG Photogate", 0);
  centeredText("Firmware Rev. 1.0", 2);
  disp.display();
}

void Display::modeSelect(Photogate& gate_1, Photogate& gate_2) {
  disp.clearDisplay();
  GateStatus last_gate_status = checkGates(gate_1, gate_2);
  gate_status = last_gate_status;
  displayOptions();
  bool selection_confirmed = false;
  while (!selection_confirmed) {
    enc.listen(enc_data);
    while (!enc_data.button_pressed) {
      gate_status = checkGates(gate_1, gate_2);
      if (gate_status != last_gate_status) {
        displayOptions();
        last_gate_status = gate_status;
      }
      enc.listen(enc_data);
      mode = getSelectedMode();
    }
    selection_confirmed = confirmMode();
    if (!selection_confirmed) {
      displayOptions();
      while (enc_data.button_pressed) {
        enc.listen(enc_data);
      }
    }
  }
}