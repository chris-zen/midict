#include <Arduino.h>

template<uint8_t pin, uint8_t on_value, uint8_t off_value>
class BuiltinLed {
public:
  void setup() {
    pinMode(pin, OUTPUT);
  }

  void setValue(uint8_t value) {
    digitalWrite(pin, value);
  }

  void flash(unsigned int n, unsigned int on_ms, unsigned int off_ms) {
    for (unsigned int i = 0; i < n; i++) {
      digitalWrite(pin, on_value);
      delay(on_ms);
      digitalWrite(pin, off_value);
      delay(off_ms);
    }
  }
};
