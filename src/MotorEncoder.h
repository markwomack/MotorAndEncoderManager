//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef MotorEncoder_h
#define MotorEncoder_h

// Arduino includes
#include <inttypes.h>

/*
 * Defines the abstract API for interacting with a motor encoder
 * that all encoder specific versions must implement.
 */
class MotorEncoder {
  public:
    MotorEncoder(){};

    /*
     * Returns the current value of the encoder.
     */
    virtual int32_t read(void) = 0;

    /*
     * Sets the current value of the encoder to the given value,
     * returns what the value of the encoder was before setting the
     * new value.
     */ 
    virtual int32_t write(const int32_t value) = 0;
};
#endif // MotorEncoder_h
