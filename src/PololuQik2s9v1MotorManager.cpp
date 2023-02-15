//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

 #include "PololuQik2s9v1MotorManager.h"
  
 PololuQik2s9v1MotorManager::PololuQik2s9v1MotorManager(const uint8_t txPin, const uint8_t rxPin, const uint8_t resetPin) {
  _qik = new PololuQik2s9v1(txPin, rxPin, resetPin);
  _qik->init(9600);
}

int PololuQik2s9v1MotorManager::mapSpeed(const double input) {
  // Pin to value between -1 and 1, then multiply by 127
  // for expected qik value.
  return (int)(min(max(input, -1.0), 1.0) * 127);
}

void PololuQik2s9v1MotorManager::setMotorSpeed(const Motor motor, const double speed) {
  if (motor == M0) {
    _qik->setM0Speed(mapSpeed(speed));
  } else {
    _qik->setM1Speed(mapSpeed(speed));
  }
}

void PololuQik2s9v1MotorManager::setMotorSpeeds(const double m0Speed, const double m1Speed) {
  _qik->setSpeeds(mapSpeed(m0Speed), mapSpeed(m1Speed));
}
