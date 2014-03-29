// Function definitions for the TimedDigitalLed class.
 
// @author Janette H. Griggs
// @version 1.3 03/29/14


#include "TimedDigitalLed.h"

TimedDigitalLed::TimedDigitalLed(int ledPinNumber, 
  unsigned long activeDuration) : DigitalLed(ledPinNumber) {
    m_activeDuration = activeDuration;
}

unsigned long TimedDigitalLed::getActiveDuration() const {
  return m_activeDuration;
}

void TimedDigitalLed::runSteadyLed(unsigned long deltaMillis) {
  stopBlinkingLed();
  activateLed(deltaMillis);
  if (m_isActive) {
    turnOnLed();
  } else {
    turnOffLed();
  }
}

void TimedDigitalLed::runBlinkingLed(unsigned long deltaMillis,
                          unsigned long blinkInterval) {
  m_blinkInterval = blinkInterval;

  activateLed(deltaMillis);

  // Blink the LED only if it is active.
  if (m_isActive && !m_isBlinking) {
    m_isBlinking = true;
    turnOnLed();
  } else if (m_isActive) {    
    m_blinkTimer += deltaMillis;
    if (m_blinkTimer >= m_blinkInterval) {
        switchLedPinState();
        m_blinkTimer = 0L;
    }
  } else {
    turnOffLed();
  }
}

void TimedDigitalLed::activateLed(unsigned long deltaMillis) {
  if (m_activeTimer == 0L && !m_isActive) {
    m_isActive = true;
  } else {
    m_activeTimer += deltaMillis;
    if (m_activeTimer >= m_activeDuration) {
      m_isActive = false;
    }
  }
}

TimedDigitalLed::~TimedDigitalLed() {

}