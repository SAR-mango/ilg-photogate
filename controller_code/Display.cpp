#include "Display.h"

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

void Display::configure(Photogate& gate_1, Photogate& gate_2) {
  enc_data.position = 0;
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
  trigSelect(gate_1, gate_2);
}

void Display::run() {
  // TODO finish continuous one-gate modes and finish all two-gate modes
  disp.clearDisplay();
  if (gate_status == GATE1 || gate_status == GATE2) {
    if (!one_gate_modes[mode].continuous) {
      centeredText(one_gate_modes[mode].name, 0);
      centeredText("--");
      centeredText("seconds", 3);
      disp.display();
      centeredText(String(one_gate_modes[mode].program() / 1000000.0, 4));
      disp.display();
    }
    else {
    }
  }
  else {
  }
}