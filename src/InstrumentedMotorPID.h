//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#ifndef INSTRUMENTEDMOTORPID_H
#define INSTRUMENTEDMOTORPID_H

#include <InstrumentedPID.h>

#include "MotorPID.h"

class InstrumentedMotorPID : public MotorPID {
  public:
    InstrumentedMotorPID(double Kp, double Ki, double Kd) : MotorPID(Kp, Ki, Kd) {
      _instrumentedPID = new InstrumentedPID(Kp, Ki, Kd, P_ON_E, DIRECT);  
    };
    
    virtual void setSampleTime(uint32_t sampleTime) {
      _instrumentedPID->setSampleTime(sampleTime);
    };
    
    virtual void setOutputLimits(double outputMin, double outputMax) {
      _instrumentedPID->setOutputLimits(outputMin, outputMax);
    };
    
    virtual void start(double initialInput, double initialOutput) {
      _instrumentedPID->start(initialInput, initialOutput);
    };
    
    virtual void stop() {
      _instrumentedPID->stop();
    };
    
    virtual bool compute(double input, double setpoint, double* returnOutput) {
      return _instrumentedPID->compute(input, setpoint, returnOutput);
    };
    
    virtual void getLastPIDState(JsonDocument& jsonDoc) {
      _instrumentedPID->getLastPIDState(jsonDoc);
    };
    
  protected:
    InstrumentedPID* _instrumentedPID;
};
#endif // INSTRUMENTEDMOTORPID_H
