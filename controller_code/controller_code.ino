#include "Includes.h"
#include "Display.h"

void setup(void) {
  Display disp;
  disp.initScreen();
  delay(1000);
  Photogate gate_1(5, 0);
  Photogate gate_2(6, 1);
  disp.modeSelect(gate_1, gate_2);
}

void loop(void) {
}
