#include <Midi.h>
#include <RotaryEncoders.h>

#ifndef CONTROL_H
#define CONTROL_H

class Control : MidiHandler {
public:
  Control(Midi &midi, RotaryEncoders &rotaryEncoders);

  void setup();
  void loop();

private:
  static const unsigned int BASE_CC = 20;

  Midi &midi;
  RotaryEncoders &rotaryEncoders;

  void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity);
  void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity);
  void handleControlChange(unsigned int channel, unsigned int controller, unsigned int value);
};

#endif
