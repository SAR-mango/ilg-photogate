#include "Display.h"

void setup() {
  Serial.begin(115200);
  Display disp;
  disp.initScreen();
  delay(500);
  Photogate gate_1(5, 2);
  Photogate gate_2(6, 3);
  disp.configure(gate_1, gate_2);
  disp.run();
}

void loop() {
}