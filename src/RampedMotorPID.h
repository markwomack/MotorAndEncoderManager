//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef RAMPEDMOTORPID_H
#define RAMPEDMOTORPID_H

#include "MotorPID.h"

class RampedMotorPID : public MotorPID {
  public:
    RampedMotorPID(double maxIncrement) : MotorPID(0, 0, 0) {
      _isRunning = false;
      _sampleTime = 100; // default is 100ms
      _maxIncrement = maxIncrement;
      _maxComputeIncrement = _maxIncrement/(1000.0/(double)_sampleTime);
    };
    
    virtual void setSampleTime(uint32_t sampleTime) {
      _sampleTime = sampleTime;
      _maxComputeIncrement = _maxIncrement/(1000.0/(double)_sampleTime);
    };
    
    virtual void setOutputLimits(double outputMin, double outputMax) {
      _outputMin = outputMin;
      _outputMax = outputMax;
    };
    
    virtual void start(double initialInput, double initialOutput) {
      _isRunning = true;
      _lastComputeTime = 0;
    };
    
    virtual void stop() {
      _isRunning = false;
    };
    
    virtual bool compute(double input, double setpoint, double* returnOutput) {
      if (!_isRunning || millis() - _lastComputeTime < _sampleTime) {
        return false;
      }
      
      // input = current speed in radians/second
      // setpoint = target speed in radians/second
      
      double diff = setpoint - input;
      double increment = (diff >= 0) ? min(_maxComputeIncrement, diff) : max(-_maxComputeIncrement, diff);
      DebugMsgs.debug().printfln("diff: %.8f, increment: %.8f, output: %.8f",
        diff, increment, min(max(increment, _outputMin), _outputMax));
      *returnOutput = min(max(increment, _outputMin), _outputMax);
      _lastComputeTime = millis();
      return true;
    };
    
    virtual void getLastPIDState(JsonDocument& jsonDoc) {
    
    };

  protected:
    bool _isRunning;
    double _maxIncrement;
    double _maxComputeIncrement;
    double _outputMin;
    double _outputMax;
    uint32_t _sampleTime;
    uint32_t _lastComputeTime;
};
#endif // RAMPEDMOTORPID_H
