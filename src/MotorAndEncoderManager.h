//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef MotorAndEncoderManager_h
#define MotorAndEncoderManager_h

// Arduino includes
#include <inttypes.h>

// Local includes
#include "MotorEncoder.h"

// Differentiates between two motors
// available for differential drive robot.
// Usually M0 refers to the left-side motor
// (from robot POV), and M1 to the right-side,
// but it is up to you. Just be sure to use
// these values consistently in your robot code.
enum MotorNum {
  M0,
  M1
};

/*
 * Defines the abstract API for interacting with motors
 * and associated encoders of a differential drive robot.
 * Implementations for specific motor controllers and
 * encoders should implement the functionality for these
 * methods.
 */
class MotorAndEncoderManager {

public:
  MotorAndEncoderManager();

  /*
   * Sets the speed of the given motor. Speed is expected to be a 
   * value between -1 (reverse) and 1 (forward).
   */
  virtual void setMotorSpeed(const MotorNum motorNum, const float speed) = 0;

  /*
   * Sets the speed of both motors. Speeds are expected to be a 
   * value between -1 (reverse) and 1 (forward).
   */
  virtual void setMotorSpeeds(const float m0Speed, const float m1Speed) = 0;

  /*
   * Assigns the motor encoders associated with each motor.
   */
  void setEncoders(MotorEncoder* m0MotorEncoder, MotorEncoder* m1MotorEncoder);

  /*
   * Reads the current value of the motors associated encoder.
   */
  int32_t readEncoder(const MotorNum motorNum);

  /*
   * Reads the value of the motors associated encoder and then resets the
   * value to zero. Returns the original value.
   */
  int32_t readAndResetEncoder(const MotorNum motorNum);

  /*
   * Reads the value of the motors associated encoder and then sets the
   * value. Returns the original value.
   */
  int32_t writeToEncoder(const MotorNum motorNum, const int32_t value);

protected:
  MotorEncoder* _m0Encoder;
  MotorEncoder* _m1Encoder;
  
  MotorEncoder* getEncoder(const MotorNum motorNum);
};

#endif // MotorAndEncoderManager_h
