#include "RotaryEncoders.h"

static int8_t encStates[] = {
   0, // 00 -> 00
  -1, // 00 -> 01
   1, // 00 -> 10
   0, // 00 -> 11
   1, // 01 -> 00
   0, // 01 -> 01
   0, // 01 -> 10
  -1, // 01 -> 11
  -1, // 10 -> 00
   0, // 10 -> 01
   0, // 10 -> 10
   1, // 10 -> 11
   0, // 11 -> 00
   1, // 11 -> 01
  -1, // 11 -> 10
   0  // 11 -> 11
 };

RotaryEncoders::RotaryEncoders(RotaryEncodersIO &io) : io(io) {

  for (int i = 0; i < NUM_ENCODERS; i++) {
    state[i] = 0;
    value[i] = 0;
  }
}

void RotaryEncoders::setup() {
  io.setup();
  sensitivity.setup(500, millis());
}

void RotaryEncoders::loop() {
  sensitivity.update(millis());

  uint32_t pins = io.read();
  for (unsigned int i = 0; i < NUM_ENCODERS; i++) {
    uint8_t ab = pins & 0x03;
    state[i] = ((state[i] << 2) | ab) & 0x0f;

    int dir = encStates[state[i]];
    int delta = dir;

    if (dir != 0) {
      state[i] |= 0x80;
      if (i == 0) {
        sensitivity.tick(i);
        unsigned int scale = sensitivity.scale(i);
        delta = dir * scale;
        if (scale > 1) {
          Serial.print(">>");
        }
      }

      if (i == 1) {
        sensitivity.setPeriod(value[1]);
      }
    }

    if (i == 0 && dir != 0) {
      // unsigned int threshold = value[1] * 10;
      // if (timeDelta < threshold) {
      //   delta = dir * 2;
      //   Serial.print(">>>");
      // }

      // Serial.print(i); Serial.print(":");
      // Serial.print(" threshold: "); Serial.print(threshold);
      // Serial.print(" timeDelta: "); Serial.print(timeDelta);
      // Serial.print(" freq: "); Serial.print(freq);
      // Serial.println();
    }

    value[i] += delta;
    if (value[i] < 0) {
      value[i] = 0;
    }
    else if (value[i] >= RotaryEncoders::VALUE_RANGE) {
      value[i] = RotaryEncoders::VALUE_RANGE - 1;
    }

    pins = pins >> 2;
  }
}
