//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef CLASSICMOTORPID_H
#define CLASSICMOTORPID_H

// The classic Arduino PID
#include <PID_v1.h>

#include "MotorPID.h"

class ClassicMotorPID : public MotorPID {
  public:
    ClassicMotorPID(double Kp, double Ki, double Kd) : MotorPID(Kp, Ki, Kd) {
      _pid = new PID(&_input, &_output, &_setpoint, Kp, Ki, Kd, P_ON_E, DIRECT);
    };
    
    virtual void setSampleTime(uint32_t sampleTime) {
      _pid->SetSampleTime(sampleTime);
    };
    
    virtual void setOutputLimits(double outputMin, double outputMax) {
      _pid->SetOutputLimits(outputMin, outputMax);
    };
    
    virtual void start(double initialInput, double initialOutput) {
      _input = initialInput;
      _output = initialOutput;
      _pid->SetMode(AUTOMATIC);
    };
    
    virtual void stop() {
      _pid->SetMode(MANUAL);
    };
    
    virtual bool compute(double input, double setpoint, double* returnOutput) {
      _input = input;
      _setpoint = setpoint;
      bool didCompute = _pid->Compute();
      if (didCompute) {
        *returnOutput = _output;
      }
      return didCompute;
    };
    
    virtual void getLastPIDState(JsonDocument& jsonDoc) {
    
    };
    
  protected:
    double _setpoint;      // The desired speed in radians/second
    double _input;         // input used by the PID
    double _output;        // Output from the PID Compute method
    PID* _pid;
};
#endif // CLASSICMOTORPID_H
