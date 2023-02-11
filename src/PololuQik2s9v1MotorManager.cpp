//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

// Dependent includes
#include <PololuQik.h>

// Local includes
 #include "PololuQik2s9v1MotorManager.h"

PololuQik2s9v1MotorManager::PololuQik2s9v1MotorManager() {
  _qik = 0;
}

void PololuQik2s9v1MotorManager::begin( const uint8_t txPin, const uint8_t rxPin, const uint8_t resetPin) {
  if (!_qik) {
    _qik = new PololuQik2s9v1(txPin, rxPin, resetPin);
    _qik->init(9600);
  }
}

int PololuQik2s9v1MotorManager::mapSpeed(const float input)  {
  // Pin to value between -1 and 1, then multiply by 127
  // for expected qik value.
  return (int)(min(max(input, -1.0), 1.0) * 127);
}

void PololuQik2s9v1MotorManager::setMotorSpeed(const MotorNum motorNum, const float speed) {
  if (motorNum == M0) {
    _qik->setM0Speed(mapSpeed(speed));
  } else {
    _qik->setM1Speed(mapSpeed(speed));
  }
}

void PololuQik2s9v1MotorManager::setMotorSpeeds(const float m0Speed, const float m1Speed) {
  if (!_qik) {
    return;
  }
  
  _qik->setSpeeds(mapSpeed(m0Speed), mapSpeed(m1Speed));
}
