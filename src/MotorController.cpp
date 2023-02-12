//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#include <Arduino.h>

// Local includes
#include "MotorController.h"

MotorController::MotorController(MotorAndEncoderManager* motorManager, const double Kp, const double Ki, const double Kd,
    const uint16_t frequency, const double radiansPerTick, const double maxRadiansPerSecond) {
    
  _motorManager = motorManager;
  
  _isRunning = false;
  
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;

  _radiansPerTick = radiansPerTick;
  _maxRadiansPerSecond = maxRadiansPerSecond;

  m0Pid = new PID(&m0Input, &m0Output, &m0Setpoint, _Kp, _Ki, _Kd, DIRECT);
  m0Pid->SetSampleTime(frequency);
  m0Pid->SetOutputLimits(-maxRadiansPerSecond, maxRadiansPerSecond);
  
  m1Pid = new PID(&m1Input, &m1Output, &m1Setpoint, _Kp, _Ki, _Kd, DIRECT);
  m1Pid->SetSampleTime(frequency);
  m1Pid->SetOutputLimits(-maxRadiansPerSecond, maxRadiansPerSecond);
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
  m0Pid->SetMode(AUTOMATIC);
  m1Pid->SetMode(AUTOMATIC);
  _isRunning = true;
}

bool MotorController::isRunning() {
  return _isRunning;
}

void MotorController::setDesiredSpeeds(const double m0Speed, const double m1Speed) {
  m0Setpoint = m0Speed;
  m1Setpoint = m1Speed;
}

bool MotorController::adjustSpeeds() {

  if (!_isRunning) {
    return false;
  }
  
  // Read the current time and encoder values
  uint32_t currentTime = millis();
  int32_t encoderM0 = _motorManager->readEncoder(M0);
  int32_t encoderM1 = _motorManager->readEncoder(M1);

  // Calculate the distance traveled since last call, in radians
  double diffM0 = static_cast<double>(encoderM0 - m0LastEncoder) * _radiansPerTick;
  double diffM1 = static_cast<double>(encoderM1 - m1LastEncoder) * _radiansPerTick;
  double diffTime = (currentTime - _lastEncoderReadTime)/1000.0;

  // Calculate the current speed in radians/second and use as input to the PID Compute
  m0Input = (diffM0/diffTime);
  m1Input = (diffM1/diffTime);

  // Run the new values through the pids
  bool changeMotorSpeeds = false;
  if (m0Pid->Compute()) {
    // Compute made an adjustment, use the output to calculate the new speed
    m0LastSpeed = min(max(m0LastSpeed + m0Output, -_maxRadiansPerSecond), _maxRadiansPerSecond);
    changeMotorSpeeds = true;
  }
  if (m1Pid->Compute()) {
    // Compute made an adjustment, use the output to calculate the new speed
    m1LastSpeed = min(max(m1LastSpeed + m1Output, -_maxRadiansPerSecond), _maxRadiansPerSecond);
    changeMotorSpeeds = true;
  }

  // If the pids adjusted the motor speeds, apply the new speeds to the motor
  if (changeMotorSpeeds) {
    // Set the new speeds, converting them to a value between -1 and 1
    _motorManager->setMotorSpeeds((float)(m0LastSpeed/_maxRadiansPerSecond), (float)(m1LastSpeed/_maxRadiansPerSecond));
  }

  // Remember time and encoder values for next call
  m0LastEncoder = encoderM0;
  m1LastEncoder = encoderM1;
  _lastEncoderReadTime = currentTime;

  return changeMotorSpeeds;
}

void MotorController::stop() {
  // Stop the motors and stop active control
  _motorManager->setMotorSpeeds(0, 0);
  _isRunning = false;
  m0Pid->SetMode(MANUAL);
  m1Pid->SetMode(MANUAL);
}
