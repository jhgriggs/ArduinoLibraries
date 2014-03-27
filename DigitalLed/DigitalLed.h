/**
 * DigitalLed class.
 * This is a base class that handles led light digital output
 * activities on the Arduino Uno.
 * 
 * @author Janette H. Griggs
 * @version 1.1 03/26/14
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
     * Configures the led light for digital output.
     * @param ledPinNumber The Arduino pin number for led output. 
     * @param blinkInterval The interval (in ms) between on (HIGH) 
     * and off (LOW) pin states. Optional.
     */
    DigitalLed(int ledPinNumber, unsigned long blinkInterval = 0L);
    
    /**
     * Returns the led pin number.
     * @return The led pin number.
     */
    int getLedPinNumber() const;

    /**
     * Returns the led pin mode.
     * @return The led pin mode.
     */
    int getLedPinMode() const;

    /**
     * Returns the led pin state.
     * @return The led pin state.
     */
    int getLedPinState() const;

    /**
     * Returns the specified interval (in ms) between the   
     * on (HIGH) and off (LOW) pin states.
     * @return The blink interval.
     */
    unsigned long getBlinkInterval() const;

    /**
     * Returns the time (in ms) since the last pin state.
     * @return The blink timer.
     */
    unsigned long getBlinkTimer() const;

    /**
     * Returns the time (in ms) since the led was active. 
     * @return The active timer.
     */
    unsigned long getActiveTimer() const;

    /**
     * Returns the active state of the led.
     * @return The active state.
     */
    bool getIsActiveState() const;
     
    /**
     * Turns on the led and sets it to an active state.
     * Blinks automatically using a timer based on the specified 
     * interval.
     * @param deltaMillis The change in time (ms) from the previous loop. 
     */
    virtual void activateLed(unsigned long deltaMillis);

    /**
     * Turns off the led and sets it to an inactive state.
     * Timers are set to 0.
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
    unsigned long m_activeTimer; /**< time (ms) since led was active */
    bool m_isActive; /**< active state of led */
    
    /**
     * Turns on the led by switching the pin state from LOW to HIGH.
     */
    void turnOnLed(); 

    /**
     * Turns off the led by switching the pin state from HIGH to LOW.
     */
    void turnOffLed();

    /**
     * Blinks the led using a timer based on the specified interval.
     * @param deltaMillis The change in time (ms) from the previous loop.
     */
    void blinkLed(unsigned long deltaMillis);

    /**
     * Toggles the pin state from LOW to HIGH or from HIGH to LOW.
     */
    void switchLedPinState();
  private:
    int m_ledPinNumber; /**< led pin number */
    int m_ledPinMode; /**< led pin mode */
    int m_ledPinState; /**< led pin state */
};

#endif