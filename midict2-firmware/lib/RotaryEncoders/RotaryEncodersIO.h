#include <Arduino.h>

#ifndef ROTARY_ENCODERS_IO_H
#define ROTARY_ENCODERS_IO_H

#define NUM_ENCODERS 2

class RotaryEncodersIO {
private:
  static const unsigned int PORT_OFFSET = 3;
  static const unsigned int PORT_MASK = (1 << (NUM_ENCODERS * 2)) - 1;

public:
  RotaryEncodersIO() { }

  void setup() {
    GPIOB->regs->CRL = 0x88888888;
    GPIOB->regs->CRH = 0x88888888;
    GPIOB->regs->ODR = 0xffffffff;
  }

  uint32_t read() {
    return (GPIOB->regs->IDR >> PORT_OFFSET) & PORT_MASK;
  }
};

#endif
