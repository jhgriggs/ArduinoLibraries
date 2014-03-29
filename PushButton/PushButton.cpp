// Function definitions for the PushButton class. 

// @author Janette H. Griggs
// @version 1.0 03/28/14

#include "PushButton.h"

PushButton::PushButton(int buttonPinNumber, ResistorMode resistorMode, unsigned long debounceDelay) {
  m_buttonPinNumber = buttonPinNumber;
  m_buttonPinMode = INPUT;

  if (resistorMode == PULL_UP) {
    m_activeValue = LOW;
  } else if (resistorMode == PULL_DOWN) {
    m_activeValue = HIGH;    
  }

  m_buttonPushState = !(m_activeValue);
  m_currentReading = m_buttonPushState;
  m_previousReading = m_currentReading;
  m_debounceDelay = debounceDelay;
  m_debounceTimer = 0L;

  pinMode(m_buttonPinNumber, m_buttonPinMode);
}

int PushButton::getButtonPinNumber() const {
  return m_buttonPinNumber;
}

int PushButton::getButtonPinMode() const {
  return m_buttonPinMode;
}

int PushButton::getActiveValue() const {
  return m_activeValue;
}

int PushButton::getButtonPushState() const {
  return m_buttonPushState;
}

int PushButton::getCurrentReading() const {
  return m_currentReading;
}

int PushButton::getPreviousReading() const {
  return m_previousReading;
}

unsigned long PushButton::getDebounceDelay() const {
  return m_debounceDelay;
}

unsigned long PushButton::getDebounceTimer() const {
  return m_debounceTimer;
}

bool PushButton::detectPush(unsigned long deltaMillis) {
  bool isPushed = false;

  m_currentReading = digitalRead(m_buttonPinNumber);

  if (m_currentReading != m_buttonPushState) {
    if (m_currentReading != m_previousReading) {
      m_debounceTimer = 0L;
    } else if (m_currentReading == m_previousReading 
      && m_debounceTimer >= m_debounceDelay) {
      m_buttonPushState = m_currentReading;

      if (m_buttonPushState == m_activeValue) {
        isPushed = true;
      }
    } else if (m_currentReading == m_previousReading) {
      m_debounceTimer += deltaMillis;
    }
  } else if (m_currentReading == m_buttonPushState) {
    m_debounceTimer = 0L;
  }

  m_previousReading = m_currentReading;

  return isPushed;
}

PushButton::~PushButton() {

}