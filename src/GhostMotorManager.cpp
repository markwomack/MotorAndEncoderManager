//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#include <Arduino.h>

#include "GhostMotorManager.h"

GhostMotorManager::GhostMotorManager() {
  _begun = false;
}

void GhostMotorManager::begin(const uint8_t m0SpeedPin, const uint8_t m0DirPin, const uint8_t m0BrakePin,
    const uint8_t m1SpeedPin, const uint8_t m1DirPin, const uint8_t m1BrakePin) {
  
  if (!_begun) {
    _begun = true;
    
    _m0SpeedPin = m0SpeedPin;
    _m0DirPin = m0DirPin;
    _m0BrakePin = m0BrakePin;
    _m1SpeedPin = m1SpeedPin;
    _m1DirPin = m1DirPin;
    _m1BrakePin = m1BrakePin;

    // Setup the speed pins
    pinMode(_m0SpeedPin, OUTPUT);
    pinMode(_m1SpeedPin, OUTPUT);
  
    // Teensy 4.X, values will be 0-8191
    analogWriteResolution(13);
    analogWriteFrequency(_m0SpeedPin, 18310.55);
    analogWriteFrequency(_m1SpeedPin, 18310.55);
  
    analogWrite(_m0SpeedPin, 0);
    analogWrite(_m1SpeedPin, 0);

    // Setup brake pins, engage brake
    pinMode(_m0BrakePin, OUTPUT);
    digitalWrite(_m0BrakePin, HIGH);
    pinMode(_m1BrakePin, OUTPUT);
    digitalWrite(_m1BrakePin, HIGH);

    // Setup direction pins, set for forward
    pinMode(_m0DirPin, OUTPUT);
    digitalWrite(_m0DirPin, LOW);
    pinMode(_m1DirPin, OUTPUT);
    digitalWrite(_m1DirPin, LOW);
  }
}

// Make sure the input is between -1 and 1, then convert to int for speed PWM
int GhostMotorManager::mapSpeed(const float input) {
  return (int)(min(max(input, -1.0), 1.0) * 8191);
}

void GhostMotorManager::setMotorSpeed(const MotorNum motorNum, const float speed) {
  if (motorNum == M0) {
    digitalWrite(_m0BrakePin, LOW);
    analogWrite(_m0SpeedPin, abs(mapSpeed(speed)));
    digitalWrite(_m0DirPin, speed >= 0 ? LOW : HIGH);
  } else {
    digitalWrite(_m1BrakePin, LOW);
    analogWrite(_m1SpeedPin, abs(mapSpeed(speed)));
    digitalWrite(_m1DirPin, speed >= 0 ? LOW : HIGH);
  }
}

void GhostMotorManager::setMotorSpeeds(const float m0Speed, const float m1Speed) {
  setMotorSpeed(M0, m0Speed);
  setMotorSpeed(M1, m1Speed);
}
