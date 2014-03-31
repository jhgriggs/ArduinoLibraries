/*
 * PushButton class.
 *
 * This is a base class that handles push button input
 * on the Arduino Uno. A timer, based on the change
 * in millis() between the loop() function calls, is used
 * to debounce the input.
 *
 * See the project TrafficLights in the jhgriggs/ArduinoProjects
 * repository for an example of this class implementation.
 *
 * @author Janette H. Griggs
 * @version 1.2 03/31/14
 */

#ifndef PushButton_h
  #define PushButton_h

#ifndef __AVR_ATmega328P__
  #define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
  #include <Arduino.h>
#endif

#include "ResistorMode.h"

class PushButton {
  public:
    /**
     * Constructor.
     * Configures the push button for input.
     * @param buttonPinNumber The Arduino pin number for button input.
     * @param resistorMode The resistor mode configuration used in the
     * circuit. This is one of the enum values: PULL_UP, PULL_DOWN.
     */
    PushButton(int buttonPinNumber, ResistorMode resistorMode);

    /**
     * Returns the push button pin number.
     * @return The push button pin number.
     */
    int getButtonPinNumber() const;

    /**
     * Returns the push button pin state that would be read if 
     * the button is pressed.
     * @return The pin state value when push button is pressed.
     */
    int getActiveValue() const;

    /** 
     * Returns the push button's push state, verified by debouncing.
     * If pushed, it will equal the active value of the push button 
     * pin state.
     * @return The push button's push state. 
     */
    int getButtonPushState() const;

    /** 
     * Returns the current raw reading of the push button.
     * @return The current reading of the push button.
     */
    int getCurrentReading() const;

    /**
     * Returns the raw reading of the push button from the
     * previous loop.
     * @return The previous reading of the push button.
     */
    int getPreviousReading() const;

    /**
     * Returns the debounce timer (in ms).
     * @return The debounce timer.
     */
    unsigned long getDebounceTimer() const;

    /**
     * Detects if the push button is pushed. Input is debounced for a
     * specified duration to verify reading. If the button is actually  
     * pushed, a true value is returned only once during a continuous 
     * press.
     * @param deltaMillis The change in time (ms) from the previous loop.
     * @param debounceDelay The delay time (ms) for debouncing input.
     * @return The truth value of whether a push is detected or not.
     */
    bool detectPush(unsigned long deltaMillis, unsigned long debounceDelay);

    /**
     * Destructor.
     */
    ~PushButton();
  private:
    int m_buttonPinNumber; /**< push button pin number */
    int m_activeValue; /**< push button pin state value when pressed */
    int m_buttonPushState; /**< push button push state */    
    int m_currentReading; /**< push button current reading */
    int m_previousReading; /**< push button previous reading */
    unsigned long m_debounceTimer; /**< debounce timer (ms) */
};

#endif