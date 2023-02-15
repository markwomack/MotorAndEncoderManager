//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

// Local includes
#include "MotorAndEncoderManager.h"

void MotorAndEncoderManager::setEncoders(MotorEncoder* m0Encoder, MotorEncoder* m1Encoder) {
  _m0Encoder = m0Encoder;
  _m1Encoder = m1Encoder;
}

int32_t MotorAndEncoderManager::readEncoder(const Motor motor) {
  if (motor == M0) {
    return _m0Encoder->read();
  } else {
    return _m1Encoder->read();
  }
}

int32_t MotorAndEncoderManager::readAndResetEncoder(const Motor motor) {
  if (motor == M0) {
    return _m0Encoder->write(0);
  } else {
    return _m1Encoder->write(0);
  }
}

int32_t MotorAndEncoderManager::writeEncoder(const Motor motor, const int32_t value) {
  if (motor == M0) {
    return _m0Encoder->write(value);
  } else {
    return _m1Encoder->write(value);
  }
}
