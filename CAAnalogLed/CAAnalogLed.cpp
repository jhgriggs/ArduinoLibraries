// Function definitions for the CAAnalogLed class. 

// @author Janette H. Griggs
// @version 1.0 04/04/14

#include "CAAnalogLed.h"

CAAnalogLed::CAAnalogLed(int ledPinNumber, int minBrightness, int maxBrightness) {
  m_minBrightness = minBrightness;
  m_maxBrightness = maxBrightness;

  if (m_minBrightness > 255) {
    m_minBrightness = 255;
  }

  if (m_maxBrightness < 0) {
    m_maxBrightness = 0;
  }

  m_brightnessChangeMode = NONE;
  m_activeTimer = 0L;
  m_isActive = false;
  m_direction = ZERO;

  setLedPinNumber(ledPinNumber);
  setToMinBrightness();
}

void CAAnalogLed::setLedPinNumber(int ledPinNumber) {
  m_ledPinNumber = ledPinNumber;

  // Set pin mode to output.
  pinMode(m_ledPinNumber, OUTPUT);
}

void CAAnalogLed::setMinBrightness(int minBrightness) {
  m_minBrightness = minBrightness;

  if (m_minBrightness > 255) {
    m_minBrightness = 255;
  }
}

void CAAnalogLed::setMaxBrightness(int maxBrightness) {
  m_maxBrightness = maxBrightness;

  if (m_maxBrightness < 0) {
    m_maxBrightness = 0;
  }
}

void CAAnalogLed::showSteadyLed(unsigned long deltaMillis) {
  stopChangingBrightness();
  activateLed(deltaMillis);
  setToMaxBrightness();
}

void CAAnalogLed::showBlinkingLed(unsigned long deltaMillis,
                       unsigned long blinkInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != BLINK) {
    m_brightnessChangeMode = BLINK;
    setToMaxBrightness();
    m_direction = POSITIVE;
  } else {
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      blinkInterval);
    
    if (m_currentBrightness <= m_maxBrightness) {
      setToMaxBrightness();
      m_direction = POSITIVE;
    } else if (m_currentBrightness >= m_minBrightness) {
      setToMinBrightness();
      m_direction = NEGATIVE;
    }
  }
}

void CAAnalogLed::showFadingInLed(unsigned long deltaMillis,
                       unsigned long fadeInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != FADE_IN) {
    m_brightnessChangeMode = FADE_IN;
    setToMinBrightness();
    m_direction = NEGATIVE;
  } else {
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      fadeInterval);
    
    if (m_currentBrightness < m_maxBrightness) {
        setToMinBrightness();
    }

    analogWrite(m_ledPinNumber, (int) m_currentBrightness);
  }
}

void CAAnalogLed::showFadingOutLed(unsigned long deltaMillis,
                       unsigned long fadeInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != FADE_OUT) {
    m_brightnessChangeMode = FADE_OUT;
    setToMaxBrightness();
    m_direction = POSITIVE;
  } else {
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      fadeInterval);
    
    if (m_currentBrightness > m_minBrightness) {
      setToMaxBrightness();
    }

    analogWrite(m_ledPinNumber, (int) m_currentBrightness);
  }
}

void CAAnalogLed::showFadingInOutLed(unsigned long deltaMillis,
                       unsigned long fadeInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != FADE_IN_OUT) {
    m_brightnessChangeMode = FADE_IN_OUT;
    setToMinBrightness();
    m_direction = NEGATIVE;
  } else {
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      fadeInterval);
    
    if (m_currentBrightness <= m_maxBrightness) {
      m_currentBrightness = m_maxBrightness;
      m_direction = POSITIVE;
    } else if (m_currentBrightness >= m_minBrightness) {
      m_currentBrightness = m_minBrightness;
      m_direction = NEGATIVE;
    }

    analogWrite(m_ledPinNumber, (int) m_currentBrightness);
  }
}

void CAAnalogLed::resetLed() {
  stopChangingBrightness();
  setToMinBrightness();
  m_activeTimer = 0L;
  m_isActive = false;
}

CAAnalogLed::~CAAnalogLed() {

}

void CAAnalogLed::stopChangingBrightness() {
  m_brightnessChangeMode = NONE;
  m_direction = ZERO;
}

void CAAnalogLed::activateLed(unsigned long deltaMillis) {
  if (!m_isActive) { 
    m_isActive = true;
  } else {
    m_activeTimer += deltaMillis;
  }
}

void CAAnalogLed::setToMaxBrightness() {
  m_currentBrightness = m_maxBrightness;
  analogWrite(m_ledPinNumber, (int) m_currentBrightness);
}

void CAAnalogLed::setToMinBrightness() {
  m_currentBrightness = m_minBrightness;
  analogWrite(m_ledPinNumber, (int) m_currentBrightness);
}

float CAAnalogLed::calculateBrightnessChange(unsigned long deltaMillis,
                                unsigned long minToMaxBrightnessInterval) {
  float brightnessChange;

  brightnessChange = (m_minBrightness -  m_maxBrightness) / 
                     (float) minToMaxBrightnessInterval *
                     deltaMillis * m_direction;

  return brightnessChange;
}