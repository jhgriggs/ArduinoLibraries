/**
 * TimedDigitalLed class.
 *
 * This is a derived class from DigitalLed that handles LED light 
 * digital output on the Arduino Uno. Instead of relying on delay() 
 * to control activites such as blinking, it uses a timer based on
 * the change in millis() between the loop() function calls. LED 
 * activity stops after reaching the specified active duration.
 * 
 * See the project TrafficLights in the jhgriggs/ArduinoProjects 
 * repository for an example of this class implementation.
 *
 * @author Janette H. Griggs
 * @version 1.2 03/29/14
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
     */
    TimedDigitalLed(int ledPinNumber, unsigned long activeDuration);

    /**
     * Returns the specified amount of time (in ms) that the led should 
     * remain active.
     * @return The active duration.
     */
    unsigned long getActiveDuration() const;

    /**
     * Turns on the led and sets it to an active state.
     * After the specifed active duration has been reached, the led
     * is turned off and becomes inactive.
     * NOTE: Call this function during each loop to maintain LED
     * activity.
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