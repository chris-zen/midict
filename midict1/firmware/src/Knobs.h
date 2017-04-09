#include <Arduino.h>

// For atmel
//#define KNOBS_SEL0 2
//#define KNOBS_SEL1 3
//#define KNOBS_SEL2 4

#define KNOBS_SEL0 D5
#define KNOBS_SEL1 D6
#define KNOBS_SEL2 D7

#define KNOBS_IN0 A0
#define KNOBS_IN1 A0

#define KNOBS_COUNT 1

class Knobs {
  private:
    uint8_t achannel = 0;

  public:

    void setup() {
      pinMode(KNOBS_SEL0, OUTPUT);
      pinMode(KNOBS_SEL1, OUTPUT);
      pinMode(KNOBS_SEL2, OUTPUT);
      pinMode(KNOBS_IN0, INPUT);

      select(0);
      delay(50);
    }

    void select(int index) {
      digitalWrite(KNOBS_SEL0, index & 0x01);
      digitalWrite(KNOBS_SEL1, (index >> 1) & 0x01);
      digitalWrite(KNOBS_SEL2, (index >> 2) & 0x01);

      uint8_t bank = (index >> 3) & 0x01;
      switch (bank) {
        case 0: achannel = KNOBS_IN0; break;
        case 1: achannel = KNOBS_IN1; break;
      }
    }

    uint16_t read() {
      float v = 1003 - analogRead(achannel);
      if (v < 0) {
        v = 0;
      }
      else if (v > 1000) {
        v = 1000;
      }
      uint16_t w = (v * 1.023);
      return w >> 3;
    }
};

class KnobsScanner {
  private:
    Knobs *knobs;

    uint8_t index;
    uint16_t values[KNOBS_COUNT];

  public:
    KnobsScanner(Knobs *knobs) {
      this->knobs = knobs;
    }

    void setup() {
      for (uint8_t i = 0 - 1; i < KNOBS_COUNT; i++) {
        knobs->select(i);
        delay(50);
        values[i] = knobs->read();
      }
      index = 0;
      knobs->select(index);
      delay(100);
    }

    uint8_t valueIndex() {
      return index;
    }

    uint16_t value() {
      return values[index];
    }

    uint16_t valueAt(uint8_t idx) {
      return values[idx];
    }

    bool valueChanged() {
      int16_t value = knobs->read();
      bool changed = value != values[index];
      values[index] = value;
      return changed;
    }

    uint8_t next() {
      index = (index + 1) % KNOBS_COUNT;
      knobs->select(index);
      return index;
    }
};

Knobs knobs;
KnobsScanner scanner(&knobs);
