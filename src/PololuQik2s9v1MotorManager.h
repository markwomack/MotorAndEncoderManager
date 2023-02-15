//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef PololuQik2s9v1MotorManager_h
#define PololuQik2s9v1MotorManager_h

// Arduino includes
#include <inttypes.h>

// Third party includes
#include <PololuQik.h>

// Local includes
#include "MotorAndEncoderManager.h"

class PololuQik2s9v1MotorManager : public MotorAndEncoderManager {

  public:
    PololuQik2s9v1MotorManager(const uint8_t txPin, const uint8_t rxPin, const uint8_t resetPin);

    void setMotorSpeed(const Motor motor, const double speed);
    void setMotorSpeeds(const double m0Speed, const double m1Speed);
  
  private:
    PololuQik2s9v1* _qik;
  
    int mapSpeed(const double input);
};

#endif
