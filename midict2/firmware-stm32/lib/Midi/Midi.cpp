#include "Midi.h"

void Midi::handleNoteOn(unsigned int channel, unsigned int note, unsigned int velocity) {
}

void Midi::handleNoteOff(unsigned int channel, unsigned int note, unsigned int velocity) {
}

void Midi::handleControlChange(unsigned int channel, unsigned int controller, unsigned int value) {
  if (handler != NULL)
    handler->handleControlChange(channel, controller, value);
}
