//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef TeensyQuadratureMotorEncoder_h
#define TeensyQuadratureMotorEncoder_h

// Arduino includes
#include <inttypes.h>

// Dependent includes
#include <Encoder.h> // Part of the Teensy libraries

// Local includes
#include "MotorEncoder.h"

/*
 * Implementation for a typical quadrature encoder
 * used with most robotic motors.
 *
 * Note: this implementation uses the Encoder
 * library from Teensy for the heavy lifting.
 * It is installed as part of the teensy development
 * package and is also on GitHub:
 * https://github.com/PaulStoffregen/Encoder
 */
class TeensyQuadratureMotorEncoder : public MotorEncoder {
  public:
    TeensyQuadratureMotorEncoder(const int8_t phaseAPin, const int8_t phaseBPin);
    
    int32_t read(void);
    int32_t write(const int32_t value);

  private:
    Encoder* _encoder;
};

#endif // TeensyQuadratureMotorEncoder_h

