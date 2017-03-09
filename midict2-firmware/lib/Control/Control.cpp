#include "Control.h"

Control::Control(Midi &midi, RotaryEncoders &rotaryEncoders)
  : midi(midi), rotaryEncoders(rotaryEncoders) {

  midi.setHandler(this);
}

void Control::setup() {
  midi.begin();
  rotaryEncoders.setup();
}

void Control::loop() {
  rotaryEncoders.loop();

  for (unsigned int i = 0; i < rotaryEncoders.count(); i++) {
    if (rotaryEncoders.valueChanged(i)) {
      int value = rotaryEncoders.getValue(i);
      midi.sendControlChange(0, Control::BASE_CC + i, value);
      Serial.print(">"); Serial.print(i); Serial.print("="); Serial.println(value);
    }
  }

  midi.poll();
}

void Control::handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) {

}

void Control::handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) {

}

void Control::handleControlChange(unsigned int channel, unsigned int controller, unsigned int value) {
  unsigned int index = controller - Control::BASE_CC;
  if (index < NUM_ENCODERS) {
    rotaryEncoders.setValue(index, value);
    Serial.print("<"); Serial.print(index); Serial.print("="); Serial.println(value);
  }
}
