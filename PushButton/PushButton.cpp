// Function definitions for the PushButton class. 

// @author Janette H. Griggs
// @version 1.2 03/31/14

#include "PushButton.h"

PushButton::PushButton(int buttonPinNumber, ResistorMode resistorMode) {
  m_buttonPinNumber = buttonPinNumber;

  if (resistorMode == PULL_UP) {
    m_activeValue = LOW;
  } else if (resistorMode == PULL_DOWN) {
    m_activeValue = HIGH;    
  }

  m_buttonPushState = !(m_activeValue);
  m_currentReading = m_buttonPushState;
  m_previousReading = m_currentReading;
  m_debounceTimer = 0L;

  pinMode(m_buttonPinNumber, INPUT);
}

int PushButton::getButtonPinNumber() const {
  return m_buttonPinNumber;
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

unsigned long PushButton::getDebounceTimer() const {
  return m_debounceTimer;
}

bool PushButton::detectPush(unsigned long deltaMillis, 
                            unsigned long debounceDelay) {
  bool isPushed = false;

  m_currentReading = digitalRead(m_buttonPinNumber);

  // If the current reading is not equal to the button push
  // state, debounce to verify that the button push state has 
  // actually changed.
  // If the button push state has actually changed and is equal
  // to the active "ON" value, the button is considered to be
  // pushed.
  if (m_currentReading != m_buttonPushState) {
    if (m_currentReading != m_previousReading) {
      m_debounceTimer = 0L;
    } else if (m_debounceTimer >= debounceDelay) {
      m_buttonPushState = m_currentReading;

      if (m_buttonPushState == m_activeValue) {
        isPushed = true;
      }
    } else {
      m_debounceTimer += deltaMillis;
    }
  } else {
    m_debounceTimer = 0L;
  }

  m_previousReading = m_currentReading;

  return isPushed;
}

PushButton::~PushButton() {

}