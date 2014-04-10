/**
 * AnalogRGBLed class.
 * 
 * This class handles RGB LED light analog (PWM) output on the
 * Arduino Uno. It can perform various activities such as
 * blinking and fading for a common cathode or a common anode
 * RGB LED.
 *
 * @author Janette H. Griggs
 * @version 1.2 04/09/14
 */
 
#ifndef AnalogRGBLed_h
  #define AnalogRGBLed_h

#ifndef __AVR_ATmega328P__
  #define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
  #include <Arduino.h>
#endif
#ifndef AnalogLed_h
  #include "AnalogLed.h"
#endif

class AnalogRGBLed {
  
  public:
    /**
     * Constructor.
     * Configures the RGB LED light for analog (PWM) output.
     * @param redPinNumber The pin number for the red color.
     * @param greenPinNumber The pin number for the green color.
     * @param bluePinNumber The pin number for the blue color.
     * @param redBrightness The brightness value for the red color,
     * which is between 0 and 255, inclusive.
     * @param greenBrightness The brightness value for the green color,
     * which is between 0 and 255, inclusive.
     * @param blueBrightness The brightness value for the blue color,
     * which is between 0 and 255, inclusive.
     * @param ledType The LED type, as in an RGB common cathode or
     * common anode.
     */
    AnalogRGBLed(int redPinNumber,
                 int greenPinNumber,
                 int bluePinNumber,
                 int redBrightness,
                 int greenBrightness,
                 int blueBrightness,
                 LedType ledType);
    
    /**
     * Returns the time (in ms) since the LED was active.
     * @return The active timer.
     */
    unsigned long getRGBActiveTimer() const;

    /**
     * Sets the color of the RGB LED.
     * @param redBrightness The brightness value for the red color,
     * which is between 0 and 255, inclusive.
     * @param greenBrightness The brightness value for the green color,
     * which is between 0 and 255, inclusive.
     * @param blueBrightness The brightness value for the blue color,
     * which is between 0 and 255, inclusive.
     */
    void setRGBColor(int redBrightness,
                     int greenBrightness,
                     int blueBrightness);
    
    /**
     * Turns on the LED and stops any blinking or fading activity.
     * NOTE: Call this function during each loop to maintain steady 
     * LED activity.
     * @param deltaMillis The change in time (ms) from the previous loop. 
     */
    void showSteadyRGBLed(unsigned long deltaMillis);

    /**
     * Blinks the LED based on the specified interval.
     * NOTE: Call this function during each loop to maintain blinking 
     * LED activity.
     * @param deltaMillis The change in time (ms) from the previous loop.
     * @param blinkInterval The interval (in ms) between the maximum 
     * brightness and minumum brightness.
     */
    void showBlinkingRGBLed(unsigned long deltaMillis,
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
    void showFadingInRGBLed(unsigned long deltaMillis,
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
    void showFadingOutRGBLed(unsigned long deltaMillis,
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
    void showFadingInOutRGBLed(unsigned long deltaMillis,
                               unsigned long fadeInterval);
    
    /**
     * Sets the LED to its minimum brightness and sets it to an inactive 
     * state. The active timer is set to 0.
     * NOTE: Call this function to terminate LED activity
     * and set the LED back to its initial state.
     */
    void resetRGBLed();
    
    /**
     * Destructor.
     */
    ~AnalogRGBLed();
  private:
    AnalogLed m_redLed; /**< red LED */
    AnalogLed m_greenLed; /**< green LED */
    AnalogLed m_blueLed; /**< blue LED */
};

#endif