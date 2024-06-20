#include "Display.h"

void Display::centeredText(String text, unsigned short level = 5) {
  if (0 <= level && level <= 3) {
    disp.setCursor((SCREEN_WIDTH - CHAR_WIDTH * text.length()) / 2, CHAR_HEIGHT * level);
  } else {
    disp.setCursor((SCREEN_WIDTH - CHAR_WIDTH * text.length()) / 2, SCREEN_HEIGHT / 2 - CHAR_HEIGHT / 2);
  }
  disp.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  disp.println(text);
}

void Display::boxedText(String text, short x, short y) {
  short rect_x = x;
  short rect_y = y;
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
  if (gate_1.connected()) {
    return GATE1;
  }
  if (gate_2.connected()) {
    return GATE2;
  }
  return NONE;
}

void Display::displayOptions() {
  disp.clearDisplay();
  if (gate_status == GATE1 || gate_status == GATE2) {
    boxedText("One Gate", -2, -2);
    for (auto i : one_gate_modes) {
      disp.setCursor(i.x, i.y);
      disp.print(i.name);
    }
  } else if (gate_status == BOTH) {
    boxedText("Two Gates", -2, -2);
    for (auto i : two_gate_modes) {
      disp.setCursor(i.x, i.y);
      disp.print(i.name);
    }
  } else {
    centeredText("No Gates Connected");
  }
  disp.display();
}

short Display::getSelectedMode() {
  if (gate_status == GATE1 || gate_status == GATE2) {
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
    return mode_num;
  } else {
    return -1;
  }
}

bool Display::confirmMode() {
  enc_data.position = 0;
  disp.clearDisplay();
  if (mode == -1) {
    return false;
  }
  if (gate_status == GATE1 || gate_status == GATE2) {
    centeredText(one_gate_modes[mode].name, 0);
  }
  else {
    centeredText(two_gate_modes[mode].name, 0);
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

void Display::trigSelect(Photogate& gate_1, Photogate& gate_2) {
  enc_data.position = 0;
  disp.clearDisplay();
  TriggerConfig trig_conf = {TM_RISING, TM_NONE};
  if (gate_status != BOTH) {
    if (mode != 2) {
      boxedText("Trigger", -2, -2);
      centeredText("RISE  FALL  CHANGE", 2);
      while (enc_data.button_pressed) {
        enc.listen(enc_data);
      }
      do {
        switch (enc_data.position % 3) {
          case 0:
          disp.fillRect(36, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_WHITE);
          disp.fillRect(72, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_BLACK);
          disp.fillRect(120, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_BLACK);
          disp.display();
          break;
          case 1:
          disp.fillRect(36, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_BLACK);
          disp.fillRect(72, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_WHITE);
          disp.fillRect(120, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_BLACK);
          disp.display();
          break;
          default:
          disp.fillRect(36, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_BLACK);
          disp.fillRect(72, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_BLACK);
          disp.fillRect(120, CHAR_HEIGHT * 2 + 2, 3, 3, SSD1306_WHITE);
          disp.display();
          break;
        }
        enc.listen(enc_data);
      } while (!enc_data.button_pressed);
      switch (enc_data.position % 3) {
        case 0:
        if (gate_status == GATE1) {
          trig_conf = {TM_RISING, TM_NONE};
        }
        else {
          trig_conf = {TM_NONE, TM_RISING};
        }
        break;
        case 1:
        if (gate_status == GATE1) {
          trig_conf = {TM_FALLING, TM_NONE};
        }
        else {
          trig_conf = {TM_NONE, TM_FALLING};
        }
        break;
        default:
        if (gate_status == GATE1) {
          trig_conf = {TM_CHANGE, TM_NONE};
        }
        else {
          trig_conf = {TM_NONE, TM_CHANGE};
        }
        break;
      }
    }
  }
  // TODO finish two-gate trig conf
  else {
  }
  setupInterrupts(gate_1, gate_2, trig_conf);
}