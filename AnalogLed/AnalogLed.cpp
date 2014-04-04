// Function definitions for the AnalogLed class. 

// @author Janette H. Griggs
// @version 1.0 04/04/14

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

  m_brightnessChangeMode = NONE;
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

void AnalogLed::setMinBrightness(int minBrightness) {
  m_minBrightness = minBrightness;

  if (m_minBrightness < m_maxBrightness) {
    if (m_minBrightness < 0) {
      m_minBrightness = 0;
    } 
  } else {
    if (m_minBrightness > 255) {
      m_minBrightness = 255;
    }
  }
}

void AnalogLed::setMaxBrightness(int maxBrightness) {
  m_maxBrightness = maxBrightness;

  if (m_minBrightness < m_maxBrightness) { 
    if (m_maxBrightness > 255) {
      m_maxBrightness = 255;
    }
  } else {
    if (m_maxBrightness < 0) {
      m_maxBrightness = 0;
    }
  }
}

void AnalogLed::showSteadyLed(unsigned long deltaMillis) {
  stopChangingBrightness();
  activateLed(deltaMillis);
  setToMaxBrightness();
}

void AnalogLed::showBlinkingLed(unsigned long deltaMillis,
                       unsigned long blinkInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != BLINK) {
    m_brightnessChangeMode = BLINK;
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
  }
}

void AnalogLed::showFadingInLed(unsigned long deltaMillis,
                       unsigned long fadeInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != FADE_IN) {
    m_brightnessChangeMode = FADE_IN;
    setToMinBrightness();
    if (m_minBrightness < m_maxBrightness) {
      m_direction = POSITIVE;
    } else {
      m_direction = NEGATIVE;
    }
  } else {
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      fadeInterval);
    
    if (m_minBrightness < m_maxBrightness) {
      if (m_currentBrightness > m_maxBrightness) {
        setToMinBrightness();
      }
    } else {
      if (m_currentBrightness < m_maxBrightness) {
        setToMinBrightness();
      }
    }

    analogWrite(m_ledPinNumber, (int) m_currentBrightness);
  }
}

void AnalogLed::showFadingOutLed(unsigned long deltaMillis,
                       unsigned long fadeInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != FADE_OUT) {
    m_brightnessChangeMode = FADE_OUT;
    setToMaxBrightness();
    if (m_minBrightness < m_maxBrightness) {
      m_direction = NEGATIVE;
    } else {
      m_direction = POSITIVE;
    }
  } else {
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      fadeInterval);
    
    if (m_minBrightness < m_maxBrightness) {
      if (m_currentBrightness < m_minBrightness) {
        setToMaxBrightness();
      }
    } else {
      if (m_currentBrightness > m_minBrightness) {
        setToMaxBrightness();
      }
    }

    analogWrite(m_ledPinNumber, (int) m_currentBrightness);
  }
}

void AnalogLed::showFadingInOutLed(unsigned long deltaMillis,
                       unsigned long fadeInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != FADE_IN_OUT) {
    m_brightnessChangeMode = FADE_IN_OUT;
    setToMinBrightness();
    if (m_minBrightness < m_maxBrightness) {
      m_direction = POSITIVE;
    } else {
      m_direction = NEGATIVE;
    }
  } else {
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      fadeInterval);
    
    if (m_minBrightness < m_maxBrightness) {
      if (m_currentBrightness >= m_maxBrightness) {
        m_currentBrightness = m_maxBrightness;
        m_direction = NEGATIVE;
      } else if (m_currentBrightness <= m_minBrightness) {
        m_currentBrightness = m_minBrightness;
        m_direction = POSITIVE;
      }
    } else {
      if (m_currentBrightness <= m_maxBrightness) {
        m_currentBrightness = m_maxBrightness;
        m_direction = POSITIVE;
      } else if (m_currentBrightness >= m_minBrightness) {
        m_currentBrightness = m_minBrightness;
        m_direction = NEGATIVE;
      }
    }

    analogWrite(m_ledPinNumber, (int) m_currentBrightness);
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
  m_brightnessChangeMode = NONE;
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