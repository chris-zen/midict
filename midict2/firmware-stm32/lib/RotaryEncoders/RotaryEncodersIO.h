#include <Arduino.h>

#ifndef ROTARY_ENCODERS_IO_H
#define ROTARY_ENCODERS_IO_H

#define NUM_ENCODERS 3

#define CLK 9
#define LD 8
#define OUT1 7

class RotaryEncodersIO {
private:
  static const unsigned int PORT_OFFSET = 3;
  static const unsigned int PORT_MASK = (1 << (NUM_ENCODERS * 2)) - 1;

public:
  RotaryEncodersIO() { }

  void setup() {
    GPIOB->regs->CRL = 0b10001000100010001000100010001000;
    GPIOB->regs->CRH = 0b10001000100010001000100001110111;
    GPIOB->regs->ODR = (1 << LD) | (0 << CLK);
    // GPIOC->regs->CRH = 0b10000111011100000000000000000000;
    // GPIOC->regs->ODR = (1 << LD) | (0 << CLK);
  }

  uint32_t read() {

    GPIOC->regs->ODR = 0xffffffff;
    uint32_t b = (GPIOB->regs->IDR >> PORT_OFFSET) & PORT_MASK;

    GPIOC->regs->ODR = (0 << LD) | (0 << CLK); delayMicroseconds(1);
    GPIOC->regs->ODR = (1 << LD) | (0 << CLK); delayMicroseconds(1);

    uint32_t v = 0;
    GPIOC->regs->ODR = (1 << LD) | (1 << CLK); delayMicroseconds(1);
    v |= ((GPIOC->regs->IDR >> OUT1) & 0x01) << 0;
    GPIOC->regs->ODR = (1 << LD) | (0 << CLK); delayMicroseconds(1);
    GPIOC->regs->ODR = (1 << LD) | (1 << CLK); delayMicroseconds(1);
    v |= ((GPIOC->regs->IDR >> OUT1) & 0x01) << 0;
    GPIOC->regs->ODR = (1 << LD) | (0 << CLK); delayMicroseconds(1);

    static uint8_t p = 0;
    if (v != p) {
      p = v;
      Serial.print((v >> 1) & 0x1);
      Serial.println(v & 0x1);
    }

    return (b << 2) | (v & 0x03);
  }
};

#endif
