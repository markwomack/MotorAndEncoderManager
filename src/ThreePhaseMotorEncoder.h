//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef ThreePhaseMotorEncoder_h
#define ThreePhaseMotorEncoder_h

// Arduino includes
#include <inttypes.h>

// Local includes
#include "MotorAndEncoderManager.h"
#include "MotorEncoder.h"

enum Direction {
  CW  = 0,  // Clockwise - Positive motor speed
  CCW = 1   // Counter-Clockwise - Negative motor speed
};

/*
 * An implementation of a 3-phase encoder built-in to BLDC
 * motors used on hoverboards or eScooters. More specific
 * information can be found here:
 * https://www.digikey.com/en/blog/using-bldc-hall-sensors-as-position-encoders-part-1
 *
 * This implemenation uses hardware interrupts on three pins per
 * encoder to track the encoder values. It uses the attachInterruptEx
 * code to efficiently attach the interrupt handler.
 */
class ThreePhaseMotorEncoder : public MotorEncoder {
  public:
    ThreePhaseMotorEncoder();
  
    /*
     * Initializes and starts the encoder. Must be called
     * before calling the MotorEncoder and other methods.
     */
    void begin(const uint8_t phaseVPin, const uint8_t phaseWPin, const uint8_t phaseUPin);
    
    // MotorEncoder methods implemented
    int32_t read(void);
    int32_t write(const int32_t value);
    
    /*
     * Returns the number of 'faults' recorded from the encoder
     * signals. A fault is recorded when an invalid state transition
     * occurs due to noise.
     */
    int32_t readFaults(void);
    
    /*
     * Returns the direction the motor is currently turning.
     * See the Direction enum in MotorAndEncoderManager.
     */
    Direction readDirection(void);
    
  private:
    void handleInterrupt(const uint8_t pinNum, const uint8_t pinMask, const uint8_t pinShift);

    int32_t volatile _tickCount;   // Number of valid ticks counted
    int32_t volatile _faultCount;  // Number or encoder faults detected
    Direction volatile _direction; // The current direction of the motor
    uint8_t volatile _state;       // The current state as determined by the encoder phase pins
};

#endif // ThreePhaseMotorEncoder_h
