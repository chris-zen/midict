#include <BuiltinLed.hpp>
#include <Midi.h>
#include <RotaryEncoders.h>
#include <Control.h>

#if defined(STM32)
  BuiltinLed<PC13, LOW, HIGH> led;

// #elif defined(ARDUINO_AVR_PRO)
//   BuiltinLed<13, HIGH, LOW> led;

#else
  #error "Board not supported"
#endif
