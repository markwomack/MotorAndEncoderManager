//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

// Arduino includes
#include <inttypes.h>

// Third party includes
#include <InstrumentedPID.h>

// Local includes
#include "MotorAndEncoderManager.h"

/*
 * The MotorController class adds a control layer that
 * uses PIDs to make sure the motors are turning at the
 * desired speed. The associated PID will adjust the speed
 * of the motor faster or slower so that it matches the
 * desired speed.
 
 * Where the underlying MotorAndEncoderManager
 * instance sets the speed of the motor based on power (ie 0
 * is stopped and -1/1 is full power reverse/forward), the
 * MotorController is setting speed based on distance being travelled
 * as measured by the difference in value of the encoders between
 * two different samples in time. The 'distance' is measured in radians
 * per second. A radian is measuring how far the motor has turned.
 * The MotorController will use the MotorAndEncoderManager to set
 * the 'power' to the motors so that the desired radians/second is
 * achieved. How many physical centimeters/second this translates to
 * can be calculated by the client code by using the wheel circumference
 * and radians per tick. The MotorController only deals in radians/second.
 */
class MotorController {
  public:
    /*
     * Sets up MotorController.
     *  motorManager - The underlying motors and encoders to be controlled.
     *  Kp, Ki, Kd - PID parameters to be used when computing changes.
     *  frequency - How often the PID should apply changes.
     *  radiansPerTick - The number of radians the motor will turn for a single tick of the encoder.
     *  maxRadiansPerSecond - The maximum number of radians per second the motor will be allowed to turn.
     *
     *  Typically the frequency should be a value less than the interval the adjustSpeeds method is called.
     */
    MotorController(MotorAndEncoderManager* motorManager, const double Kp, const double Ki, const double Kd,
      const uint16_t frequency, const double radiansPerTick, const double maxRadiansPerSecond);
      
    /*
     * Starts the active control of the motors to match the desired speeds
     * when set with setDesiredSpeeds.
     */
    void start();
    
    /*
     * Stops the active control of the motors. Does not attempt to stop the
     * motors.
     */
    void disengage();
    
    /*
     * Stops the active control of the motors and stops the motors abruptly.
     */
    void stop();
    
    /*
     * Returns true if controller is controlling motor speeds.
     */
    bool isRunning();
    
    /*
     * The desired speed of the robot value should be in radians/second.
     */
    void setDesiredSpeeds(const double m0MotorSpeed, const double m1MotorSpeed);
    
    /*
     * Must be called periodically by the robot so that the motor speeds
     * can be checked and adjusted. If the motor controller is not actively
     * controlling speeds (ie start() has not been called), then no actions
     * are taken. Returns true if the motor speeds were adjusted.
     */
    bool adjustSpeeds();

  private:
    bool _isRunning;
    
    // Parameters for the PID calculations
    double _Kp;
    double _Ki;
    double _Kd;

    // Specifc to the motors on the robot
    double _radiansPerTick;      // Number of radians per tick of the encoder
    double _maxRadiansPerSecond; // The maximum speed allowed in radians/second
    
    double m0Setpoint;      // The desired speed in radians/second
    double m0Input;         // input used by the PID
    double m0Output;        // Output from the PID Compute method
    double m0LastSpeed;     // The last speed that was set in radians/second
    int32_t m0LastEncoder;  // The last encoder reading
    InstrumentedPID* m0Pid; // The PID doing the control calculations
    
    double m1Setpoint;
    double m1Input;
    double m1Output;
    double m1LastSpeed;
    int32_t m1LastEncoder;
    InstrumentedPID* m1Pid;
    
    // The last time the encoders were read
    uint32_t _lastEncoderReadTime;
    
    // The underlying motors and encoders being controlled
    MotorAndEncoderManager* _motorManager;
};

#endif
