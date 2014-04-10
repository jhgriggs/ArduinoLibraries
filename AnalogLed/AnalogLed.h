/**
 * AnalogLed class.
 *
 * This is a base class that handles LED light analog (PWM) output
 * on the Arduino Uno. Instead of relying to delay() to control
 * activities such as blinking and fading, it uses the change in  
 * millis() between the loop() function calls and the specified
 * interval to calculate the brightness change amount during each 
 * loop.
 * 
 * @author Janette H. Griggs
 * @version 1.4 04/09/14
 */

#ifndef AnalogLed_h
  #define AnalogLed_h

#ifndef __AVR_ATmega328P__
  #define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
  #include <Arduino.h>
#endif
#ifndef LedType_h
  #include "LedType.h"
#endif
#ifndef BrightnessChangeMode_h
  #include "BrightnessChangeMode.h"
#endif

class AnalogLed {
  public:
    /**
     * Constructor.
     * Configures the LED light for analog (PWM) output.
     * @param ledPinNumber The Arduino pin number for LED output. 
     * @param minBrightness The minimum brightness value, which is
     * at least 0.
     * @param maxBrightness The maximum brightness value, which is
     * at most 255.
     * @param ledType The LED type, as in an RGB common cathode
     * or common anode. 
     */
    AnalogLed(int ledPinNumber, int minBrightness = 0, 
              int maxBrightness = 255,
              LedType ledType = COMMON_CATHODE);

    /**
     * Returns the LED pin number.
     * @return The LED pin number. 
     */
    int getLedPinNumber() const;

    /**
     * Returns the minimum brightness value of the LED.
     * @return The LED minimum brightness value.
     */
    int getMinBrightness() const;

    /**
     * Returns the maximum brightness value of the LED.
     * @return The LED maximum brightness value.
     */
    int getMaxBrightness() const;

    /**
     * Returns the current calculated brightness value.
     * @return The current calculated brightness value.
     */
    float getCurrentBrightness() const;

    /**
     * Returns the time (in ms) since the last brightness change.
     * @return The brightness change timer.
     */
    unsigned long getBrightnessChangeTimer() const;

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
     * Returns the LED type, whether a common cathode
     * or a common anode.
     * @return The LED type.
     */
    LedType getLedType() const;

    /**
     * Returns the brightness change mode of the LED.
     * @return The brightness change mode. 
     */
    BrightnessChangeMode getBrightnessChangeMode() const;

    /**
     * Sets the LED pin number.
     * @param The LED pin number.
     */
    void setLedPinNumber(int ledPinNumber);

    /**
     * Sets the minimum brightness value of the LED.
     * @param The LED minimum brightness value.
     */
    void setMinBrightness(int minBrightness);

    /**
     * Sets the maximum brightness value of the LED.
     * @param The LED maximum brightness value.
     */
    void setMaxBrightness(int maxBrightness);

    /**
     * Turns on the LED and stops any blinking or fading activity.
     * NOTE: Call this function during each loop to maintain steady 
     * LED activity.
     * @param deltaMillis The change in time (ms) from the previous loop. 
     */
    void showSteadyLed(unsigned long deltaMillis);

    /**
     * Blinks the LED based on the specified interval.
     * NOTE: Call this function during each loop to maintain blinking 
     * LED activity.
     * @param deltaMillis The change in time (ms) from the previous loop.
     * @param blinkInterval The interval (in ms) between the maximum 
     * brightness and minumum brightness.
     */
    void showBlinkingLed(unsigned long deltaMillis,
                       unsigned long blinkInterval);

    /**
     * Fades in the LED in a repeating loop based on the specified 
     * interval.
     * NOTE: Call this function during each loop to maintain fading
     * LED activity.
     * @param deltaMillis The change in time (ms) from the previous loop.
     * @param fadeInterval The interval (in ms) between the maximum 
     * brightness and minumum brightness.
     */
    void showFadingInLed(unsigned long deltaMillis,
                       unsigned long fadeInterval);

    /**
     * Fades out the LED in a repeating loop based on the specified 
     * interval.
     * NOTE: Call this function during each loop to maintain fading
     * LED activity.
     * @param deltaMillis The change in time (ms) from the previous loop.
     * @param fadeInterval The interval (in ms) between the maximum 
     * brightness and minumum brightness.
     */
    void showFadingOutLed(unsigned long deltaMillis,
                       unsigned long fadeInterval);

    /**
     * Fades the LED in and out repeatedly based on the specified
     * interval.
     * NOTE: Call this function during each loop to maintain fading
     * LED activity.
     * @param deltaMillis The change in time (ms) from the previous loop.
     * @param fadeInterval The interval (in ms) between the maximum 
     * brightness and minumum brightness.
     */
    void showFadingInOutLed(unsigned long deltaMillis,
                       unsigned long fadeInterval);

    /**
     * Sets the LED to its minimum brightness and sets it to an inactive 
     * state. The active timer is set to 0.
     * NOTE: Call this function to terminate LED activity
     * and set the LED back to its initial state.
     */
    void resetLed();

    /**
     * Destructor.
     */
    ~AnalogLed();
  private:
    enum Direction {NEGATIVE = -1, ZERO = 0, POSITIVE = 1}; /**< direction 
                                                            enum */

    int m_ledPinNumber; /**< LED pin number */
    int m_minBrightness; /**< LED min brightness */
    int m_maxBrightness; /**< LED max brightness */
    float m_currentBrightness; /**< LED current brightness */
    unsigned long m_brightnessChangeTimer; /**< time (ms) since last brightness
                                       change */
    unsigned long m_activeTimer; /**< time (ms) since LED was active */
    bool m_isActive; /**< active state of LED */
    LedType m_ledType; /**< LED type */
    BrightnessChangeMode m_brightnessChangeMode; /**< brightness change mode */
    Direction m_direction; /**< direction of brightness change*/

    /**
     * Stops blinking or fading the LED.
     */
    void stopChangingBrightness();

    /**
     * Activates the LED. Increments the active
     * timer during each loop.
     */
    void activateLed(unsigned long deltaMillis);

    /**
     * Sets the LED to maximum brightness.
     */
    void setToMaxBrightness();

    /**
     * Sets the LED to minimum brightness.
     */
    void setToMinBrightness();

    /**
     * Calculates the brightness change amount.
     */
    float calculateBrightnessChange(unsigned long deltaMillis,
                                    unsigned long minToMaxBrightnessInterval);
};

#endif