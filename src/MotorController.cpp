//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

// Arduino includes
#include <Arduino.h>

#include <DebugMsgs.h>

// Local includes
#include "MotorController.h"
#include "MotorPID.h"

MotorController::MotorController(MotorAndEncoderManager* motorManager, MotorPID* m0MotorPID, MotorPID* m1MotorPID,
    const uint32_t frequency, const double radiansPerTick, const double maxRadiansPerSecond) {
    
  _motorManager = motorManager;
  
  _isRunning = false;

  _radiansPerTick = radiansPerTick;
  _maxRadiansPerSecond = maxRadiansPerSecond;
  
  m0Pid = m0MotorPID;
  m0Pid->setSampleTime(frequency);
  m0Pid->setOutputLimits(-_maxRadiansPerSecond, _maxRadiansPerSecond);
  
  m1Pid = m1MotorPID;
  m1Pid->setSampleTime(frequency);
  m1Pid->setOutputLimits(-_maxRadiansPerSecond, _maxRadiansPerSecond);
}

void MotorController::start() {
  _motorManager->readAndResetEncoder(M0);
  _motorManager->readAndResetEncoder(M1);
  
  m0Setpoint = 0.0;
  m0Input = 0.0;
  m0Output = 0.0;
  m0LastSpeed = 0.0;
  m0LastEncoder = 0;
  
  m1Setpoint = 0.0;
  m1Input = 0.0;
  m1Output = 0.0;
  m1LastSpeed = 0.0;
  m1LastEncoder = 0;
  
  _lastEncoderReadTime = millis();
  
  // Start active control
  m0Pid->start(m0Input, m0Output);
  m1Pid->start(m1Input, m1Output);
  _isRunning = true;
}

bool MotorController::isRunning() {
  return _isRunning;
}

void MotorController::setDesiredSpeeds(const double m0Speed, const double m1Speed) {
  m0Setpoint = min(max(m0Speed, -_maxRadiansPerSecond), _maxRadiansPerSecond);
  m1Setpoint = min(max(m1Speed, -_maxRadiansPerSecond), _maxRadiansPerSecond);;
}

bool MotorController::adjustSpeeds() {

  if (!_isRunning) {
    return false;
  }
  
  // Read the current time
  uint32_t currentTime = millis();
  // If no time has passed since last call, exit early
  if (currentTime - _lastEncoderReadTime == 0) {
    return false;
  }
  
  // Read the current time and encoder values
  int32_t encoderM0 = _motorManager->readEncoder(M0);
  int32_t encoderM1 = _motorManager->readEncoder(M1);

  // Calculate the distance traveled since last call, in radians
  double diffM0 = static_cast<double>(encoderM0 - m0LastEncoder) * _radiansPerTick;
  double diffM1 = static_cast<double>(encoderM1 - m1LastEncoder) * _radiansPerTick;
  double diffTime = (currentTime - _lastEncoderReadTime)/1000.0;

  // Calculate the current speed in radians/second and divide that by the max
  // radians per second to get a value for velocity in radians/second.
  m0Input = (diffM0/diffTime);
  m1Input = (diffM1/diffTime);

  // Run the new values through the pids
  bool changeMotorSpeeds = false;
  if (m0Pid->compute(m0Input, m0Setpoint, &m0Output)) {
    // Compute made an adjustment, use the output to calculate the new speed
    m0LastSpeed = min(max(m0LastSpeed + m0Output, -_maxRadiansPerSecond), _maxRadiansPerSecond);
    changeMotorSpeeds = true;
  }
  if (m1Pid->compute(m1Input, m1Setpoint, &m1Output)) {
    // Compute made an adjustment, use the output to calculate the new speed
    m1LastSpeed = min(max(m1LastSpeed + m1Output, -_maxRadiansPerSecond), _maxRadiansPerSecond);
    changeMotorSpeeds = true;
  }
  
  // If the pids adjusted the motor speeds, apply the new speeds to the motor with a values
  // between -1 and 1.
  if (changeMotorSpeeds) {
    DebugMsgs.debug().printfln("Setting motor speeds: %.4f, %.4f", m0LastSpeed/_maxRadiansPerSecond, m0LastSpeed/_maxRadiansPerSecond);
    // Set the new speeds
    _motorManager->setMotorSpeeds(m0LastSpeed/_maxRadiansPerSecond, m1LastSpeed/_maxRadiansPerSecond);
  }

  // Remember time and encoder values for next call
  m0LastEncoder = encoderM0;
  m1LastEncoder = encoderM1;
  _lastEncoderReadTime = currentTime;

  return changeMotorSpeeds;
}

void MotorController::disengage() {
  _isRunning = false;
  m0Pid->stop();
  m1Pid->stop();
}

void MotorController::stop() {
  disengage();
  // Stop the motors and stop active control
  _motorManager->setMotorSpeeds(0, 0);
}

double MotorController::getLastM0SetSpeed() {
  return m0LastSpeed;
}

double MotorController::getLastM1SetSpeed() {
  return m1LastSpeed;
}
    
