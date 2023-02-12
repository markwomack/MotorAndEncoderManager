//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef GhostMotorManager_h
#define GhostMotorManager_h

// Arduino includes
#include <inttypes.h>

// Local includes
#include "MotorAndEncoderManager.h"

/*
 * This is an implementation of MotorManager for the Ghost motor
 * controller, which is a controller for two BLDC hoverboard-like
 * motors. More information can be found at:
 * https://github.com/markwomack/GhostMotorController
 *
 * Right now it is controlling the motors directly through the
 * connected pins, but eventually it will control through
 * a-yet-to-be-implemented I2C api.
 */
class GhostMotorManager : public MotorAndEncoderManager {

public:
  GhostMotorManager();
  
  /*
   * Initializes and starts the motor controller, must be called before the
   * MotorManager methods are used.
   */
  void begin(const uint8_t m0SpeedPin, const uint8_t m0DirPin, const uint8_t m0BrakePin,
      const uint8_t m1SpeedPin, const uint8_t m1DirPin, const uint8_t m1BrakePin);

  void setMotorSpeed(const MotorNum motorNum, const float speed);
  void setMotorSpeeds(const float m0Speed, const float m1Speed);
  
private:
  bool _begun;
  uint8_t _m0SpeedPin;
  uint8_t _m0DirPin;
  uint8_t _m0BrakePin;
  uint8_t _m1SpeedPin;
  uint8_t _m1DirPin;
  uint8_t _m1BrakePin;
  
  int mapSpeed(const float input);
};

#endif // GhostMotorManager_h
