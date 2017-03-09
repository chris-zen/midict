#include <Arduino.h>
#include "RotaryEncodersIO.h"

#ifndef ROTARY_ENCODERS_H
#define ROTARY_ENCODERS_H

class Sensitivity {
private:
  unsigned int period;
  unsigned long timestamp;
  unsigned int count[NUM_ENCODERS];

public:
  Sensitivity() {
    for (int i = 0; i < NUM_ENCODERS; i++) count[i] = 0u;
    this->period = 0;
    this->timestamp = 0;
  };

  void setup(unsigned int period, unsigned int timestamp) {
    this->period = period;
    this->timestamp = timestamp;
  }

  void setPeriod(unsigned int period) {
    this->period = period;
  }

  void update(unsigned long timestamp) {
    unsigned long delta = timestamp - this->timestamp;
    if (delta > period) {
      for (int i = 0; i < NUM_ENCODERS; i++) {
        if (count[i] > 0) count[i] -= 1u;
      }
      this->timestamp += period;
    }
  }

  void tick(int index) {
    if (count[index] < 32) count[index] += 1u;
  }

  bool scale(unsigned int index) {
    return count[index] > 1 ? 4 : 1;
  }
};

class RotaryEncoders {
private:
  RotaryEncodersIO &io;

  uint8_t state[NUM_ENCODERS];
  int16_t value[NUM_ENCODERS];

  Sensitivity sensitivity;

public:
  static const int VALUE_RANGE = 128;

  RotaryEncoders(RotaryEncodersIO &io);

  unsigned int count() { return NUM_ENCODERS; }

  void setup();

  void loop();

  bool valueChanged(unsigned int index) {
    return (state[index] >> 7) == 1;
  }

  uint8_t getValue(unsigned int index) {
    return value[index];
  }

  void setValue(unsigned int index, uint8_t v) {
    value[index] = v;
  }
};

#endif
