/**
 * TimedDigitalLed class.
 * This is a derived class from DigitalLed that handles led light 
 * digital output activities on the Arduino Uno. An active duration
 * can be specified for the led.
 * 
 * @author Janette H. Griggs
 * @version 1.1 03/22/14
 */

#ifndef TimedDigitalLed_h
  #define TimedDigitalLed_h

#ifndef __AVR_ATmega328P__
  #define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
  #include <Arduino.h>
#endif

#include "DigitalLed.h"

class TimedDigitalLed : public DigitalLed {
  public:
    /**
     * Constructor.
     * Configures the led light for digital output.
     * @param ledPinNumber The Arduino pin number for led output. 
     * @param activeDuration The amount of time (in ms) for which the 
     * led should be active.
     * @param blinkInterval The interval (in ms) between on (HIGH) and 
     * (LOW) off pin states. Optional.
     */
    TimedDigitalLed(int ledPinNumber, unsigned long activeDuration, 
      unsigned long blinkInterval = 0L);

    /**
     * Returns the specified amount of time (in ms) that the led should 
     * remain active.
     * @return The active duration.
     */
    unsigned long getActiveDuration() const;

    /**
     * Turns on the led and sets it to an active state.
     * Blinks automatically using a timer based on the specified 
     * interval.
     * After the specifed active duration has been reached, the led
     * is turned off and becomes inactive.
     * @param deltaMillis The change in time (ms) from the previous loop. 
     */
    virtual void activateLed(unsigned long deltaMillis);

    /**
     * Destructor.
     */
    ~TimedDigitalLed();
  protected:
    unsigned long m_activeDuration; /**< amount of time led should be active */
};

#endif