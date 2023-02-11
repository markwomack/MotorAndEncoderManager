//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef PololuQik2s9v1MotorManager_h
#define PololuQik2s9v1MotorManager_h

// Arduino includes
#include <inttypes.h>

// Dependent includes
#include <PololuQik.h>

// Local includes
#include "MotorAndEncoderManager.h"

/*
 * This is an implementations specific to the Pololu Qik2s9v1
 * motor controller (https://www.pololu.com/product/1110). The 
 * controller is officially discontinued.
 */
class PololuQik2s9v1MotorManager : public MotorAndEncoderManager {

public:
  PololuQik2s9v1MotorManager();
  
  /*
   * Initializes and begins operation of motor controller hardware.
   * Must be called before using MotorAndEncoderManager methods.
   */
  void begin(const uint8_t txPin, const uint8_t rxPin, const uint8_t resetPin);

  void setMotorSpeed(const MotorNum motorNum, const float speed);
  void setMotorSpeeds(const float m0Speed, const float m1Speed);
  
private:
  PololuQik2s9v1* _qik;
  
  int mapSpeed(const float input);
};

#endif
