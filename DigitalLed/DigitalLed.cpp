// Function definitions for the DigitalLed class. 

// @author Janette H. Griggs
// @version 1.1 03/26/14

#include "DigitalLed.h"

DigitalLed::DigitalLed(int ledPinNumber, unsigned long blinkInterval) {
  m_ledPinNumber = ledPinNumber;
  m_ledPinMode = OUTPUT;
  m_ledPinState = LOW;
  m_blinkInterval = blinkInterval;
  m_blinkTimer = 0L;
  m_activeTimer = 0L;
  m_isActive = false;

  pinMode(ledPinNumber, m_ledPinMode);
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

unsigned long DigitalLed::getActiveTimer() const {
  return m_activeTimer;
}

bool DigitalLed::getIsActiveState() const {
  return m_isActive;
}

void DigitalLed::activateLed(unsigned long deltaMillis) {
  if (!m_isActive) {
    turnOnLed();
    m_isActive = true;
  } else {
    m_activeTimer += deltaMillis;
    if (m_blinkInterval != 0L) {
      blinkLed(deltaMillis);
    }
  }
}

void DigitalLed::resetLed() {
  turnOffLed();
  m_blinkTimer = 0L;
  m_activeTimer = 0L;
  m_isActive = false;
}
    
DigitalLed::~DigitalLed() {

}

void DigitalLed::turnOnLed() {
  m_ledPinState = HIGH;
  digitalWrite(m_ledPinNumber, m_ledPinState);
}

void DigitalLed::turnOffLed() {
  m_ledPinState = LOW;
  digitalWrite(m_ledPinNumber, m_ledPinState);
}

void DigitalLed::blinkLed(unsigned long deltaMillis) {
  m_blinkTimer += deltaMillis;
  if (m_blinkTimer >= m_blinkInterval) {
    switchLedPinState();
    m_blinkTimer = 0L;
  }
}

void DigitalLed::switchLedPinState() {
  if (m_ledPinState == HIGH) {
    turnOffLed();
  } else {
    turnOnLed(); 
  }
}