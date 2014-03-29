// ResistorMode enum for resistor configuration
// in a circuit, i.e. pull-up vs pull-down.

// @author Janette H. Griggs
// @version 1.0 03/28/14

#ifndef ResistorMode_h
  #define ResistorMode_h

#ifndef __AVR_ATmega328P__
  #define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
  #include <Arduino.h>
#endif

enum ResistorMode { PULL_UP, PULL_DOWN };

#endif