//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef MOTORPID_H
#define MOTORPID_H

#include <inttypes.h>
#include <ArduinoJson.h>

class MotorPID {
  public:
    MotorPID(double Kp, double Ki, double Kd) {
      _Kp = Kp;
      _Ki = Ki;
      _Kd = Kd;
    };
    
    virtual void setSampleTime(uint32_t sampleTime) = 0;
    virtual void setOutputLimits(double outputMin, double outputMax) = 0;
    virtual void start(double initialInput, double initialOutput) = 0;
    virtual void stop() = 0;
    virtual bool compute(double input, double setpoint, double* returnOutput) = 0;
    virtual void getLastPIDState(JsonDocument& jsonDoc) = 0;
    
    double getKp() {
      return _Kp;
    };
    
    double getKi() {
      return _Ki;
    };
    
    double getKd() {
      return _Kd;
    };
    
  protected:
    double _Kp;
    double _Ki;
    double _Kd;
};
#endif // MOTORPID_H
