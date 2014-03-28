/**
 * DigitalLed class.
 *
 * This is a base class that handles LED light digital output
 * on the Arduino Uno. Instead of relying on delay() to control 
 * activites such as blinking, it uses a timer based on the 
 * change in millis() between the loop() function calls.
 *
 * See the project TrafficLights in the jhgriggs/ArduinoProjects 
 * repository for an example of this class implementation.
 * 
 * @author Janette H. Griggs
 * @version 1.1 03/28/14
 */

#ifndef DigitalLed_h
  #define DigitalLed_h

#ifndef __AVR_ATmega328P__
  #define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
  #include <Arduino.h>
#endif

class DigitalLed {
  public:
    /**
     * Constructor.
     * Configures the LED light for digital output.
     * @param ledPinNumber The Arduino pin number for LED output. 
     * @param blinkInterval The interval (in ms) between on (HIGH) 
     * and off (LOW) pin states. Optional.
     */
    DigitalLed(int ledPinNumber, unsigned long blinkInterval = 0L);
    
    /**
     * Returns the LED pin number.
     * @return The LED pin number.
     */
    int getLedPinNumber() const;

    /**
     * Returns the LED pin mode.
     * @return The LED pin mode.
     */
    int getLedPinMode() const;

    /**
     * Returns the LED pin state.
     * @return The LED pin state.
     */
    int getLedPinState() const;

    /**
     * Returns the specified interval (in ms) between the   
     * on (HIGH) and off (LOW) pin states.
     * @return The blink interval.
     */
    unsigned long getBlinkInterval() const;

    /**
     * Returns the time (in ms) since the last pin state change.
     * @return The blink timer.
     */
    unsigned long getBlinkTimer() const;

    /**
     * Returns the time (in ms) since the led was active. 
     * @return The active timer.
     */
    unsigned long getActiveTimer() const;

    /**
     * Returns the active state of the LED.
     * @return The active state.
     */
    bool getIsActiveState() const;
     
    /**
     * Turns on the LED and sets it to an active state.
     * Blinks automatically using a timer based on the specified 
     * interval.
     * NOTE: Call this function during each loop to maintain LED
     * activity.
     * @param deltaMillis The change in time (ms) from the previous loop. 
     */
    virtual void activateLed(unsigned long deltaMillis);

    /**
     * Turns off the LED and sets it to an inactive state.
     * Timers are set to 0.
     * NOTE: Call this function to terminate LED activity
     * and set the LED back to its initial state.
     */
    void resetLed();
    
    /**
     * Destructor.
     */
    ~DigitalLed();
  protected:
    unsigned long m_blinkInterval; /**< interval (ms) between on (HIGH)
                                    and off (LOW) pin states */
    unsigned long m_blinkTimer; /**< time (ms) since last pin state */
    unsigned long m_activeTimer; /**< time (ms) since LED was active */
    bool m_isActive; /**< active state of LED */
    
    /**
     * Turns on the LED by switching the pin state from LOW to HIGH.
     */
    void turnOnLed(); 

    /**
     * Turns off the LED by switching the pin state from HIGH to LOW.
     */
    void turnOffLed();

    /**
     * Blinks the LED using a timer based on the specified interval.
     * @param deltaMillis The change in time (ms) from the previous loop.
     */
    void blinkLed(unsigned long deltaMillis);

    /**
     * Toggles the pin state from LOW to HIGH or from HIGH to LOW.
     */
    void switchLedPinState();
  private:
    int m_ledPinNumber; /**< LED pin number */
    int m_ledPinMode; /**< LED pin mode */
    int m_ledPinState; /**< LED pin state */
};

#endif