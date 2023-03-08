//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

// Expected three phase square wave signals
//               ___________
// V ___________|           |_________
//       ___________             _____
// W ___|           |___________|
//   _______             ___________
// U        |___________|           |_
//  ^   ^   ^   ^   ^   ^   ^   ^   ^
//  0   0   0   1   1   1   0   0   0 ...
//  0   1   1   1   0   0   0   1   1 ...
//  1   1   0   0   0   1   1   1   0 ...
//                          ^-- pattern repeats
// V W U
// 0 0 0 INVALID, can never reach this state
// 0 0 1 = 1  <-these values are populated in the CWNEXTSTATE and
// 0 1 1 = 3    CCWNEXTSTATE arrays below and are the only valid
// 0 1 0 = 2    transitions allowed (eg from 6 you can only go to 2
// 1 1 0 = 6     when going CCW, or 4 when going CW).
// 1 0 0 = 4
// 1 0 1 = 5
// 1 1 1 INVALID, can never reach this state
//
// Please see this web article for more information:
// https://www.digikey.com/en/blog/using-bldc-hall-sensors-as-position-encoders-part-1

// Arduino includes
#include <Arduino.h>

// Local includes
#include "ThreePhaseMotorEncoder.h"
#include "attachInterruptEx.h"

// Masks used to clear phase value
const uint8_t VMASK(0b00000011);
const uint8_t WMASK(0b00000101);
const uint8_t UMASK(0b00000110);

// Offset use to shift phase value into place
const uint8_t VPOS(2);
const uint8_t WPOS(1);
const uint8_t UPOS(0);

// Arrays used to transition the current state (index in array)
// to the next state depending on which value (CW vs CCW) matches.
uint8_t CWNEXTSTATE[]  { 0, 3, 6, 2, 5, 1, 4, 0 };
uint8_t CCWNEXTSTATE[] { 0, 5, 3, 1, 6, 4, 2, 0 };

ThreePhaseMotorEncoder::ThreePhaseMotorEncoder() {
  _state = 0;  // the begin() method must be called, otherwise this state is invalid.
}

void ThreePhaseMotorEncoder::begin(const uint8_t phaseVPin, const uint8_t phaseWPin, const uint8_t phaseUPin) {
  // if previously called, then _state won't be zero
  if (_state == 0) {
    // Initialize members
    _tickCount = 0;
    _faultCount = 0;
    _direction = CW;
    
    // Set the pin modes
    pinMode(phaseVPin, INPUT_PULLUP);
    pinMode(phaseWPin, INPUT_PULLUP);
    pinMode(phaseUPin, INPUT_PULLUP);
    
    // Read current state of encoders
    _state = (digitalRead(phaseVPin)<<VPOS) + (digitalRead(phaseWPin)<<WPOS) + digitalRead(phaseUPin);
    
    // Ready to start fielding interrupt calls, assign interrupts
    attachInterruptEx(phaseVPin, [this, phaseVPin] { handleInterrupt(phaseVPin, VMASK, VPOS); }, CHANGE);
    attachInterruptEx(phaseWPin, [this, phaseWPin] { handleInterrupt(phaseWPin, WMASK, WPOS); }, CHANGE);
    attachInterruptEx(phaseUPin, [this, phaseUPin] { handleInterrupt(phaseUPin, UMASK, UPOS); }, CHANGE);
  }
}

void ThreePhaseMotorEncoder::handleInterrupt(const uint8_t pinNum, const uint8_t pinMask, const uint8_t pinShift) {

  // Immediately capture the pin state
  uint8_t pinValue = digitalRead(pinNum);
  
  // Calculate the new state
  uint8_t newState = (_state & pinMask) + (pinValue << pinShift);
  
  // If the new state is in the CW array, then going CW
  if (newState == CWNEXTSTATE[_state]) {
    _tickCount++;
    _direction = CW;
    _state = newState;
  // If the new state is in the CCW array, then going CCW
  } else if (newState == CCWNEXTSTATE[_state]) {
    _tickCount--;
    _direction = CCW;
    _state = newState;
  // This is noise to be ignored, but recorded
  } else {
    _faultCount++;
  }
}

int32_t ThreePhaseMotorEncoder::read(void) {
  int32_t value;
  
  noInterrupts();
  value = _tickCount;
  interrupts();

  return value;
}

int32_t ThreePhaseMotorEncoder::write(int32_t value) {
  int32_t oldValue;
  
  noInterrupts();
  oldValue = _tickCount;
  _tickCount = value;
  interrupts();
  
  return oldValue;
}

int32_t ThreePhaseMotorEncoder::readFaults(void) {
  int32_t value;
  
  noInterrupts();
  value = _faultCount;
  interrupts();

  return value;
}

Direction ThreePhaseMotorEncoder::readDirection(void) {
  Direction value;
  
  noInterrupts();
  value = _direction;
  interrupts();

  return value;
}
