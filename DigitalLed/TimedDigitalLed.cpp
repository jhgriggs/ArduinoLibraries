// Function definitions for the TimedDigitalLed class.
 
// @author Janette H. Griggs
// @version 1.1 03/22/14


#include "TimedDigitalLed.h"

TimedDigitalLed::TimedDigitalLed(int ledPinNumber, unsigned long activeDuration, 
  unsigned long blinkInterval) : DigitalLed(ledPinNumber, blinkInterval) {
    m_activeDuration = activeDuration;
}

unsigned long TimedDigitalLed::getActiveDuration() const {
  return m_activeDuration;
}

void TimedDigitalLed::activateLed(unsigned long deltaMillis) {
  if (m_activeTimer == 0L && !m_isActive) {
    turnOnLed();
    m_isActive = true;
  } else {
    m_activeTimer += deltaMillis;
    if (m_activeTimer >= m_activeDuration) {
      turnOffLed();
      m_isActive = false;
    } else if (m_blinkInterval != 0L) {
      blinkLed(deltaMillis);
    }
  }
}

TimedDigitalLed::~TimedDigitalLed() {

}