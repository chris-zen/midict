#include <usb_midi.h>

#ifndef MIDI_H
#define MIDI_H

class MidiHandler {
public:
  virtual void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) = 0;
  virtual void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) = 0;
  virtual void handleControlChange(unsigned int channel, unsigned int controller, unsigned int value) = 0;
};

class Midi : public USBMidi {
public:
  Midi() : handler(NULL) {}

  void setHandler(MidiHandler *handler) {
    this->handler = handler;
  }

private:
  MidiHandler *handler;

  void handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity);
  void handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity);
  void handleControlChange(unsigned int channel, unsigned int controller, unsigned int value);
};

#endif
