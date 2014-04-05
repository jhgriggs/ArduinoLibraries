// LedType enum for LED, common cathode or
// common anode.

// @author Janette H. Griggs
// @version 1.0 04/05/14

#ifndef LedType_h
  #define LedType_h

#ifndef __AVR_ATmega328P__
  #define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
  #include <Arduino.h>
#endif
    
enum LedType {COMMON_CATHODE, COMMON_ANODE};

#endif