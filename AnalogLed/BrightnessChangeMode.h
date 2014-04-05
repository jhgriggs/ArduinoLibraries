// BrightnessChangeMode enum for LED.

// @author Janette H. Griggs
// @version 1.0 04/05/14

#ifndef BrightnessChangeMode_h
  #define BrightnessChangeMode_h

#ifndef __AVR_ATmega328P__
  #define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
  #include <Arduino.h>
#endif

enum BrightnessChangeMode {NONE, BLINK, FADE_IN, FADE_OUT,
                                FADE_IN_OUT};

#endif