// Function definitions for the AnalogLed class. 

// @author Janette H. Griggs
// @version 1.0 03/31/14

#include "AnalogLed.h"

AnalogLed::AnalogLed(int ledPinNumber, int minBrightness, int maxBrightness) {
  m_minBrightness = minBrightness;
  m_maxBrightness = maxBrightness;

  if (m_minBrightness < m_maxBrightness) {
    if (m_minBrightness < 0) {
      m_minBrightness = 0;
    } 
    if (m_maxBrightness > 255) {
      m_maxBrightness = 255;
    }
  } else {
    if (m_minBrightness > 255) {
      m_minBrightness = 255;
    }
    if (m_maxBrightness < 0) {
      m_maxBrightness = 0;
    }
  }

  m_isChangingBrightness = false;
  m_activeTimer = 0L;
  m_isActive = false;
  m_direction = ZERO;

  setLedPinNumber(ledPinNumber);
  setToMinBrightness();
}

void AnalogLed::setLedPinNumber(int ledPinNumber) {
  m_ledPinNumber = ledPinNumber;

  // Set pin mode to output.
  pinMode(m_ledPinNumber, OUTPUT);
}

void AnalogLed::showSteadyLed(unsigned long deltaMillis) {
  stopChangingBrightness();
  activateLed(deltaMillis);
  setToMaxBrightness();
}

void AnalogLed::showBlinkingLed(unsigned long deltaMillis,
                       unsigned long blinkInterval) {
  activateLed(deltaMillis);

  if (!m_isChangingBrightness) {
    m_isChangingBrightness = true;
    setToMaxBrightness();
    if (m_minBrightness < m_maxBrightness) {
      m_direction = NEGATIVE;
    } else {
      m_direction = POSITIVE;
    }
  } else {
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      blinkInterval);
    
    if (m_minBrightness < m_maxBrightness) {
      if (m_currentBrightness >= m_maxBrightness) {
        setToMaxBrightness();
        m_direction = NEGATIVE;
      } else if (m_currentBrightness <= m_minBrightness) {
        setToMinBrightness();
        m_direction = POSITIVE;
      }
    } else {
      if (m_currentBrightness <= m_maxBrightness) {
        setToMaxBrightness();
        m_direction = POSITIVE;
      } else if (m_currentBrightness >= m_minBrightness) {
        setToMinBrightness();
        m_direction = NEGATIVE;
      }
    }

    Serial.println(m_currentBrightness);
    Serial.println();
  }
}

void AnalogLed::resetLed() {
  stopChangingBrightness();
  setToMinBrightness();
  m_activeTimer = 0L;
  m_isActive = false;
}

AnalogLed::~AnalogLed() {

}

void AnalogLed::stopChangingBrightness() {
  m_isChangingBrightness = false;
  m_direction = ZERO;
}

void AnalogLed::activateLed(unsigned long deltaMillis) {
  if (!m_isActive) { 
    m_isActive = true;
  } else {
    m_activeTimer += deltaMillis;
  }
}

void AnalogLed::setToMaxBrightness() {
  m_currentBrightness = m_maxBrightness;
  analogWrite(m_ledPinNumber, (int) m_currentBrightness);
}

void AnalogLed::setToMinBrightness() {
  m_currentBrightness = m_minBrightness;
  analogWrite(m_ledPinNumber, (int) m_currentBrightness);
}

float AnalogLed::calculateBrightnessChange(unsigned long deltaMillis,
                                unsigned long minToMaxBrightnessInterval) {
  float brightnessChange;

  if (m_minBrightness < m_maxBrightness) {
    brightnessChange = ((m_maxBrightness -  m_minBrightness) / 
                       (float) minToMaxBrightnessInterval) *
                       deltaMillis * m_direction;
  } else {
    brightnessChange = (m_minBrightness -  m_maxBrightness) / 
                       (float) minToMaxBrightnessInterval *
                       deltaMillis * m_direction;
  }

  return brightnessChange;
}