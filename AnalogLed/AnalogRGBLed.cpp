// Function definitions for AnalogRGBLed class.

// @author Janette H. Griggs
// @version 1.1 04/05/14

#include "AnalogRGBLed.h"

AnalogRGBLed::AnalogRGBLed(
    int redPinNumber,
    int greenPinNumber,
    int bluePinNumber,
    int redBrightness,
    int greenBrightness,
    int blueBrightness,
    LedType ledType) :
    m_redLed(redPinNumber, 0, redBrightness, ledType),
    m_greenLed(greenPinNumber, 0, greenBrightness, ledType),
    m_blueLed(bluePinNumber, 0, blueBrightness, ledType) {
}
   
void AnalogRGBLed::setRGBColor(int redBrightness,
                               int greenBrightness,
                               int blueBrightness) {
  m_redLed.setMaxBrightness(redBrightness);
  m_greenLed.setMaxBrightness(greenBrightness);
  m_blueLed.setMaxBrightness(blueBrightness);
}


void AnalogRGBLed::showSteadyRGBLed(unsigned long deltaMillis) {
  m_redLed.showSteadyLed(deltaMillis);
  m_greenLed.showSteadyLed(deltaMillis);
  m_blueLed.showSteadyLed(deltaMillis);
}


void AnalogRGBLed::showBlinkingRGBLed(unsigned long deltaMillis,
                     unsigned long blinkInterval) {
  m_redLed.showBlinkingLed(deltaMillis, blinkInterval);
  m_greenLed.showBlinkingLed(deltaMillis, blinkInterval);
  m_blueLed.showBlinkingLed(deltaMillis, blinkInterval);
}

void AnalogRGBLed::showFadingInRGBLed(unsigned long deltaMillis,
                                      unsigned long fadeInterval) {
  m_redLed.showFadingInLed(deltaMillis, fadeInterval);
  m_greenLed.showFadingInLed(deltaMillis, fadeInterval);
  m_blueLed.showFadingInLed(deltaMillis, fadeInterval);
}

void AnalogRGBLed::showFadingOutRGBLed(unsigned long deltaMillis,
                                       unsigned long fadeInterval) {
  m_redLed.showFadingOutLed(deltaMillis, fadeInterval);
  m_greenLed.showFadingOutLed(deltaMillis, fadeInterval);
  m_blueLed.showFadingOutLed(deltaMillis, fadeInterval);
}

void AnalogRGBLed::showFadingInOutRGBLed(unsigned long deltaMillis,
                                         unsigned long fadeInterval) {
  m_redLed.showFadingInOutLed(deltaMillis, fadeInterval);
  m_greenLed.showFadingInOutLed(deltaMillis, fadeInterval);
  m_blueLed.showFadingInOutLed(deltaMillis, fadeInterval);
}

void AnalogRGBLed::resetRGBLed() {
  m_redLed.resetLed();
  m_greenLed.resetLed();
  m_blueLed.resetLed();
}

AnalogRGBLed::~AnalogRGBLed() {

}