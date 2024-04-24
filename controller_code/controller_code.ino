#include "Display.h"

void setup() {
  Serial.begin(115200);
  Display disp;
  disp.initScreen();
  delay(1000);
  Photogate gate_1(5, 2);
  Photogate gate_2(6, 3);
  disp.modeSelect(gate_1, gate_2);
  setupInterrupts(gate_1, gate_2);
  //disp.runScreen();
  one_gate_modes[0].func_ptr();
}

void loop() {
}