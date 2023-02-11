//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#include "MotorAndEncoderManager.h"
#include "MotorEncoder.h"


MotorAndEncoderManager::MotorAndEncoderManager(){
  _m0Encoder = 0;
  _m1Encoder = 0;
}

void MotorAndEncoderManager::setEncoders(MotorEncoder* m0Encoder, MotorEncoder* m1Encoder) {
  _m0Encoder = m0Encoder;
  _m1Encoder = m1Encoder;
}

int32_t MotorAndEncoderManager::readEncoder(const MotorNum motorNum) {
  MotorEncoder* motorEncoder = getEncoder(motorNum);
  if (!motorEncoder) {
    return 0;
  }
  
  return motorEncoder->read();
}

int32_t MotorAndEncoderManager::readAndResetEncoder(const MotorNum motorNum) {
  MotorEncoder* motorEncoder = getEncoder(motorNum);
  if (!motorEncoder) {
    return 0;
  }
  
  return motorEncoder->write(0);
}

int32_t MotorAndEncoderManager::writeToEncoder(const MotorNum motorNum, const int32_t value) {
  MotorEncoder* motorEncoder = getEncoder(motorNum);
  if (!motorEncoder) {
    return 0;
  }
  
  return motorEncoder->write(value);
}

MotorEncoder* MotorAndEncoderManager::getEncoder(const MotorNum motorNum) {
  return (motorNum == M0) ? _m0Encoder : _m1Encoder;
}
