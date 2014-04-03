/**
 * AnalogLed class.
 *
 * 
 * @author Janette H. Griggs
 * @version 1.0 03/31/14
 */

#ifndef AnalogLed_h
  #define AnalogLed_h

#ifndef __AVR_ATmega328P__
  #define __AVR_ATmega328P__
#endif
#ifndef Arduino_h
  #include <Arduino.h>
#endif

class AnalogLed {
  public:
    AnalogLed(int ledPinNumber, int minBrightness, int maxBrightness);

    void setLedPinNumber(int ledPinNumber);
    void showSteadyLed(unsigned long deltaMillis);
    void showBlinkingLed(unsigned long deltaMillis,
                       unsigned long blinkInterval);
    //void showFadeOnLed();
    //void showFadeOffLed();
    void showFadingLed(unsigned long deltaMillis,
                       unsigned long fadeInterval);
    void resetLed();

    ~AnalogLed();
  private:
    enum Direction {NEGATIVE = -1, ZERO = 0, POSITIVE = 1};

    int m_ledPinNumber;
    int m_minBrightness;
    int m_maxBrightness;
    float m_currentBrightness;
    bool m_isChangingBrightness;
    unsigned long m_activeTimer; /**< time (ms) since LED was active */
    bool m_isActive; /**< active state of LED */
    Direction m_direction;

    void stopChangingBrightness();
    void activateLed(unsigned long deltaMillis);
    void setToMaxBrightness();
    void setToMinBrightness();
    float calculateBrightnessChange(unsigned long deltaMillis,
                                    unsigned long minToMaxBrightnessInterval);
};

#endif