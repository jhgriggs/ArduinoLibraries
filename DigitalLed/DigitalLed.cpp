// Function definitions for the DigitalLed class. 

// @author Janette H. Griggs
// @version 1.3 03/29/14

#include "DigitalLed.h"

DigitalLed::DigitalLed(int ledPinNumber) {
  m_ledPinNumber = ledPinNumber;
  m_ledPinMode = OUTPUT;
  m_blinkInterval = 0L;
  m_blinkTimer = 0L;
  m_isBlinking = false;
  m_activeTimer = 0L;
  m_isActive = false;

  // Set pin mode to output.
  pinMode(m_ledPinNumber, m_ledPinMode);

  // Set the pin state to off (LOW).
  turnOffLed();
}
    
int DigitalLed::getLedPinNumber() const {
  return m_ledPinNumber;
}

int DigitalLed::getLedPinMode() const {
  return m_ledPinMode;
}

int DigitalLed::getLedPinState() const {
  return m_ledPinState;
}

unsigned long DigitalLed::getBlinkInterval() const {
  return m_blinkInterval;
}

unsigned long DigitalLed::getBlinkTimer() const {
  return m_blinkTimer;
}

bool DigitalLed::getIsBlinkingState() const {
  return m_isBlinking;
}

unsigned long DigitalLed::getActiveTimer() const {
  return m_activeTimer;
}

bool DigitalLed::getIsActiveState() const {
  return m_isActive;
}

void DigitalLed::runSteadyLed(unsigned long deltaMillis) {
  stopBlinkingLed();
  activateLed(deltaMillis);
  turnOnLed();
}

void DigitalLed::runBlinkingLed(unsigned long deltaMillis,
                          unsigned long blinkInterval) {
  m_blinkInterval = blinkInterval;

  activateLed(deltaMillis);

  // Blink the LED.
  if (!m_isBlinking) {
    m_isBlinking = true;
    turnOnLed();
  } else {    
    m_blinkTimer += deltaMillis;
    if (m_blinkTimer >= m_blinkInterval) {
        switchLedPinState();
        m_blinkTimer = 0L;
    }
  }
}

void DigitalLed::resetLed() {
  stopBlinkingLed();
  turnOffLed();
  m_activeTimer = 0L;
  m_isActive = false;
}
    
DigitalLed::~DigitalLed() {

}

void DigitalLed::stopBlinkingLed() {
  m_blinkTimer = 0L;
  m_isBlinking = false;
}

void DigitalLed::activateLed(unsigned long deltaMillis) {
  if (!m_isActive) { 
    m_isActive = true;
  } else {
    m_activeTimer += deltaMillis;
  }
}

void DigitalLed::turnOnLed() {
  m_ledPinState = HIGH;
  digitalWrite(m_ledPinNumber, m_ledPinState);
}

void DigitalLed::turnOffLed() {
  m_ledPinState = LOW;
  digitalWrite(m_ledPinNumber, m_ledPinState);
}

void DigitalLed::switchLedPinState() {
  if (m_ledPinState == HIGH) {
    turnOffLed();
  } else {
    turnOnLed(); 
  }
}