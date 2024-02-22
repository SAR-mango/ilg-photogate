#include "Encoder.h"

Encoder::Encoder(bool enable_neopixel = false) {
  encoder.begin(ENC_ADDR);
  if (enable_neopixel) {
    neopixel = seesaw_NeoPixel(1, ENC_INTERNAL_NEOPIX, NEO_GRB + NEO_KHZ800);
    neopixel.begin(ENC_ADDR);
    neopixel.setBrightness(10);
    neopixel.show();
  }
  encoder.pinMode(ENC_INTERNAL_SWITCH, INPUT_PULLUP);
  encoder_position = encoder.getEncoderPosition();
  encoder.setGPIOInterrupts((uint32_t)1 << ENC_INTERNAL_SWITCH, 1);
  encoder.enableEncoderInterrupt();
}

EncoderData Encoder::listen(EncoderData& data) {
  if (!encoder.digitalRead(ENC_INTERNAL_SWITCH)) {
    data.button_pressed = true;
  }
  else {
    data.button_pressed = false;
  }
  long new_encoder_position = encoder.getEncoderPosition();
  if (encoder_position != new_encoder_position) {
    data.position = new_encoder_position;
    //neopixel.setPixelColor(0, Wheel(new_encoder_position & 0xFF));
    //neopixel.show();
    encoder_position = new_encoder_position;
  }
}

// uint32_t Wheel(byte WheelPos) {
//   WheelPos = 255 - WheelPos;
//   if (WheelPos < 85) {
//     return sspixel.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//   }
//   if (WheelPos < 170) {
//     WheelPos -= 85;
//     return sspixel.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//   }
//   WheelPos -= 170;
//   return sspixel.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
// }