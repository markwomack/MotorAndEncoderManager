//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

// Dependent includes
#include <Encoder.h>

// Local includes
#include "TeensyQuadratureMotorEncoder.h"

TeensyQuadratureMotorEncoder::TeensyQuadratureMotorEncoder() {
  _encoder = 0;
}

void TeensyQuadratureMotorEncoder::begin(const int8_t phaseAPin, const int8_t phaseBPin) {
  if (!_encoder) {
    _encoder = new Encoder(phaseAPin, phaseBPin);
  }
}

int32_t TeensyQuadratureMotorEncoder::read(void) {
  if (_encoder) {
    return _encoder->read();
  } else {
    return 0;
  }
}

int32_t TeensyQuadratureMotorEncoder::write(const int32_t value) {
  if (_encoder) {
    int32_t curValue = _encoder->read();
    _encoder->write(value);
    return curValue;
  } else {
    return 0;
  }
}
