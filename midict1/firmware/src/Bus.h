#include <Arduino.h>

class Bus {
  private:
    Stream* _stream;
    size_t _ssize;

    void _send(const char type, const char* fmt, ...) {
      va_list args;
      va_start(args, fmt);
      _stream->print(type);
      char s[_ssize];
      vsnprintf(s, _ssize, fmt, args);
      _stream->println(s);
      va_end(args);
    }

  public:
    Bus(Stream* stream, size_t ssize = 32) {
      _stream = stream;
      _ssize = ssize;
    }

    void send_level(uint8_t index, uint16_t value) {
      _send('L', "%02u=%04u", index, value);
    }
};

Bus bus(&Serial);
