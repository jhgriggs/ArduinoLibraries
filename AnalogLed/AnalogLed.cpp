// Function definitions for the AnalogLed class. 

// @author Janette H. Griggs
// @version 1.3 04/06/14

#include "AnalogLed.h"

AnalogLed::AnalogLed(int ledPinNumber, 
                     int minBrightness, 
                     int maxBrightness, 
                     LedType ledType) {
  m_ledType = ledType;

  if (m_ledType == COMMON_CATHODE) {
    m_minBrightness = minBrightness;
    m_maxBrightness = maxBrightness;
  } 
  
  if (m_ledType == COMMON_ANODE) {
    m_minBrightness = 255 - minBrightness;
    m_maxBrightness = 255 - maxBrightness;
  }

  m_brightnessChangeTimer = 0L;
  m_brightnessChangeMode = NONE;
  m_activeTimer = 0L;
  m_isActive = false;
  m_direction = ZERO;

  setLedPinNumber(ledPinNumber);
  setToMinBrightness();
}

int AnalogLed::getLedPinNumber() const {
  return m_ledPinNumber;
}

int AnalogLed::getMinBrightness() const {
  return m_minBrightness;
}

int AnalogLed::getMaxBrightness() const {
  return m_maxBrightness;
}

float AnalogLed::getCurrentBrightness() const {
  return m_currentBrightness;
}

unsigned long AnalogLed::getBrightnessChangeTimer() const {
  return m_brightnessChangeTimer;
}

unsigned long AnalogLed::getActiveTimer() const {
  return m_activeTimer;
}

bool AnalogLed::getIsActiveState() const {
  return m_isActive;
}

LedType AnalogLed::getLedType() const {
  return m_ledType;
}

BrightnessChangeMode AnalogLed::getBrightnessChangeMode() const {
  return m_brightnessChangeMode;
}

void AnalogLed::setLedPinNumber(int ledPinNumber) {
  m_ledPinNumber = ledPinNumber;

  // Set pin mode to output.
  pinMode(m_ledPinNumber, OUTPUT);
}

void AnalogLed::setMinBrightness(int minBrightness) {
  if (m_ledType == COMMON_CATHODE) {
    m_minBrightness = minBrightness;
  }
  
  if (m_ledType == COMMON_ANODE) {
    m_minBrightness = 255 - minBrightness;
  }
}

void AnalogLed::setMaxBrightness(int maxBrightness) {
  if (m_ledType == COMMON_CATHODE) {
    m_maxBrightness = maxBrightness;
  } 
  
  if (m_ledType == COMMON_ANODE) {
    m_maxBrightness = 255 - maxBrightness;
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
    m_brightnessChangeTimer = 0L;
    m_brightnessChangeMode = BLINK;
    setToMaxBrightness();

    if (m_ledType == COMMON_CATHODE) {
      m_direction = NEGATIVE;
    }
    
    if (m_ledType == COMMON_ANODE) {
      m_direction = POSITIVE;
    } 
  } else {
    m_brightnessChangeTimer += deltaMillis;
    //m_currentBrightness += calculateBrightnessChange(deltaMillis,
    //                                  blinkInterval);
    
    if (m_ledType == COMMON_CATHODE && 
        m_brightnessChangeTimer >= blinkInterval) {
      if (m_direction == POSITIVE) {
        setToMaxBrightness();
        m_direction = NEGATIVE;      
      } else if (m_direction == NEGATIVE) {
        setToMinBrightness();
        m_direction = POSITIVE;
      }

      m_brightnessChangeTimer = 0L;
    }
    
    if (m_ledType == COMMON_ANODE && 
        m_brightnessChangeTimer >= blinkInterval) {
      if (m_direction == NEGATIVE) {
        setToMaxBrightness();
        m_direction = POSITIVE;
      } else if (m_direction == POSITIVE) {
        setToMinBrightness();
        m_direction = NEGATIVE;
      }

      m_brightnessChangeTimer = 0L;
    }
  }
}

void AnalogLed::showFadingInLed(unsigned long deltaMillis,
                       unsigned long fadeInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != FADE_IN) {
    m_brightnessChangeTimer = 0L;
    m_brightnessChangeMode = FADE_IN;
    setToMinBrightness();
    
    if (m_ledType == COMMON_CATHODE) {
      m_direction = POSITIVE;
    }
    
    if (m_ledType == COMMON_ANODE) {
      m_direction = NEGATIVE;
    }
  } else {
    m_brightnessChangeTimer += deltaMillis;
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      fadeInterval);
    
    /*
    if (m_brightnessChangeTimer > fadeInterval) {
      setToMinBrightness();
      m_brightnessChangeTimer = 0L;
    } else {
      analogWrite(m_ledPinNumber, (int) m_currentBrightness);
    }
    */

    if (m_ledType == COMMON_CATHODE && 
        m_brightnessChangeTimer >= fadeInterval) {
      if (m_direction == POSITIVE) {
        setToMaxBrightness();
        m_direction = NEGATIVE;       
      } else if (m_direction == NEGATIVE) {
        setToMinBrightness();
        m_direction = POSITIVE;
      }

      m_brightnessChangeTimer = 0L;
    } else if (m_ledType == COMMON_CATHODE 
               && m_direction == POSITIVE) {
      analogWrite(m_ledPinNumber, (int) m_currentBrightness);
    }
    
    if (m_ledType == COMMON_ANODE && 
        m_brightnessChangeTimer >= fadeInterval) {
      if (m_direction == NEGATIVE) {
        setToMaxBrightness();
        m_direction = POSITIVE;        
      } else if (m_direction == POSITIVE) {
        setToMinBrightness();
        m_direction = NEGATIVE;
      }

      m_brightnessChangeTimer = 0L;
    } else if (m_ledType == COMMON_ANODE
               && m_direction == NEGATIVE) {
      analogWrite(m_ledPinNumber, (int) m_currentBrightness);
    }   
  }
}

void AnalogLed::showFadingOutLed(unsigned long deltaMillis,
                       unsigned long fadeInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != FADE_OUT) {
    m_brightnessChangeTimer = 0L;
    m_brightnessChangeMode = FADE_OUT;
    setToMaxBrightness();
    
    if (m_ledType == COMMON_CATHODE) {
      m_direction = NEGATIVE;
    }
    
    if (m_ledType == COMMON_ANODE) {
      m_direction = POSITIVE;
    }
  } else {
    m_brightnessChangeTimer += deltaMillis;
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      fadeInterval);  

    /*
    if (m_brightnessChangeTimer > fadeInterval) {
      setToMaxBrightness();
      m_brightnessChangeTimer = 0L;
    } else {
      analogWrite(m_ledPinNumber, (int) m_currentBrightness);
    }
    */

    if (m_ledType == COMMON_CATHODE && 
        m_brightnessChangeTimer >= fadeInterval) {
      if (m_direction == POSITIVE) {
        setToMaxBrightness();
        m_direction = NEGATIVE;       
      } else if (m_direction == NEGATIVE) {
        setToMinBrightness();
        m_direction = POSITIVE;
      }

      m_brightnessChangeTimer = 0L;
    } else if (m_ledType == COMMON_CATHODE 
               && m_direction == NEGATIVE) {
      analogWrite(m_ledPinNumber, (int) m_currentBrightness);
    }
    
    if (m_ledType == COMMON_ANODE && 
        m_brightnessChangeTimer >= fadeInterval) {
      if (m_direction == NEGATIVE) {
        setToMaxBrightness();
        m_direction = POSITIVE;        
      } else if (m_direction == POSITIVE) {
        setToMinBrightness();
        m_direction = NEGATIVE;
      }

      m_brightnessChangeTimer = 0L;
    } else if (m_ledType == COMMON_ANODE
               && m_direction == POSITIVE) {
      analogWrite(m_ledPinNumber, (int) m_currentBrightness);
    }
  }
}

void AnalogLed::showFadingInOutLed(unsigned long deltaMillis,
                       unsigned long fadeInterval) {
  activateLed(deltaMillis);

  if (m_brightnessChangeMode != FADE_IN_OUT) {
    m_brightnessChangeTimer = 0L;
    m_brightnessChangeMode = FADE_IN_OUT;
    setToMinBrightness();

    if (m_ledType == COMMON_CATHODE) {
      m_direction = POSITIVE;
    }
    
    if (m_ledType == COMMON_ANODE) {
      m_direction = NEGATIVE;
    }
  } else {
    m_brightnessChangeTimer += deltaMillis;
    m_currentBrightness += calculateBrightnessChange(deltaMillis,
                                      fadeInterval);
    
    if (m_ledType == COMMON_CATHODE && 
        m_brightnessChangeTimer >= fadeInterval) {
      if (m_direction == POSITIVE) {
        setToMaxBrightness();
        m_direction = NEGATIVE;       
      } else if (m_direction == NEGATIVE) {
        setToMinBrightness();
        m_direction = POSITIVE;
      }

      m_brightnessChangeTimer = 0L;
    } else if (m_ledType == COMMON_CATHODE) {
      analogWrite(m_ledPinNumber, (int) m_currentBrightness);
    }
    
    if (m_ledType == COMMON_ANODE && 
        m_brightnessChangeTimer >= fadeInterval) {
      if (m_direction == NEGATIVE) {
        setToMaxBrightness();
        m_direction = POSITIVE;        
      } else if (m_direction == POSITIVE) {
        setToMinBrightness();
        m_direction = NEGATIVE;
      }

      m_brightnessChangeTimer = 0L;
    } else if (m_ledType == COMMON_ANODE) {
      analogWrite(m_ledPinNumber, (int) m_currentBrightness);
    }   
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
  m_brightnessChangeTimer = 0L;
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

  if (m_ledType == COMMON_CATHODE) {
    brightnessChange = (m_maxBrightness -  m_minBrightness) / 
                       (float) minToMaxBrightnessInterval *
                       deltaMillis * m_direction;
  }
    
  if (m_ledType == COMMON_ANODE) {
    brightnessChange = (m_minBrightness -  m_maxBrightness) / 
                       (float) minToMaxBrightnessInterval *
                       deltaMillis * m_direction;  
  }

  return brightnessChange;
}