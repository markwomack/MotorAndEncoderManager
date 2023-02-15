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

enum Motor {
  M0,
  M1
};

class MotorAndEncoderManager {

public:

  /*
   * Sets the speed of the given motor. Speed is expected to be a 
   * value between -1 and 1.
   */
  virtual void setMotorSpeed(const Motor motor, const double speed) = 0;

  /*
   * Sets the speed of the motors. Speeds are expected to be a 
   * value between -1 and 1.
   */
  virtual void setMotorSpeeds(const double m0Speed, const double m1Speed) = 0;
  
  /*
   * Assigns the motor encoders.
   */
  void setEncoders(MotorEncoder* m0Encoder, MotorEncoder* m1Encoder);
  
  /*
   * Reads the value of the given motors encoder.
   */
  int32_t readEncoder(const Motor motor);
  
  /*
   * Reads the value of the given motors encoder and then resets the
   * value to zero.
   */
  int32_t readAndResetEncoder(const Motor motor);

  /*
   * Sets the value of the given motors encoder to the given value.
   */
  int32_t writeEncoder(const Motor motor, int32_t const value);

protected:
  MotorEncoder* _m0Encoder;
  MotorEncoder* _m1Encoder;
};

#endif  // MotorAndEncoderManager_h
