#include "midict2.h"

Midi midi;
RotaryEncodersIO rotaryEncodersIO;
RotaryEncoders rotaryEncoders(rotaryEncodersIO);
Control control(midi, rotaryEncoders);

void setup() {
  Serial.begin(115200);
  Serial.println("MIDIct2");

  control.setup();

  led.setup();
  led.flash(5, 200, 200);
}

void loop() {
  control.loop();
}
