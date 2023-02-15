//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

// Arduino includes
#include <Arduino.h>

// MotorManager includes
#include <MotorAndEncoderManager.h>
#include <MotorController.h>
#include <PololuQik2s9v1MotorManager.h>
#include <TeensyQuadratureMotorEncoder.h>

// This is a example of using the MotorController class with a
// specific motor. Please see the README for the details of the
// motor being used to calculate these constants.
// The robot will drive forward for 5 seconds and then backward
// for 5 seconds, ad infinitum. But! when the robot is driving you
// should see that it maintains a fairly straight line. This is
// because the MotorController is exerting control to make sure the
// motors are both turning at the same speed based on the tick counts.

//*** These are the contants based on the specific motors and encoders being used.
// You should use values that match your own robot.

// Total encoder ticks for single wheel revolution
const double TICKS_PER_ROTATION(3000.0); // 250:1 gear ratio * 12 ticks per single motor rotation

// Code will use Radians (angular velocity) for velocity measurements
// Note: There are 2 radians in a single rotation (360 degrees)
const double RADIANS_PER_TICK(2 / TICKS_PER_ROTATION);

// This constant is based on measurements of the motor performance using
// full motor power your robot is using (This one used 5v to the motors).
// Your mileage may vary and you should verify your robots values by running
// the motors at full power (1.0) for a second and recording the encoder values.
// When motor is run at full for one second, this is approximately
// how many ticks will be counted.
const double MAX_TICKS_PER_SECOND(3600.0);

// This is the number of wheel rotations when run at full for one second.
const double MAX_ROTATIONS_PER_SECOND(MAX_TICKS_PER_SECOND / TICKS_PER_ROTATION);

// This is the max radians per second when run at full speed.
// Note: there are 2 radians in one rotation.
const double MAX_RADIANS_PER_SECOND(MAX_ROTATIONS_PER_SECOND * 2);

// Just for reference, this the max meters per second when run at full speed.
// It is just for reference, since the MotorController will use radians/second.
// Wheel diameter in meters (31 mm)
const double WHEEL_DIAM_M(0.031);
const double WHEEL_CIRCUMFERENCE_M(PI * WHEEL_DIAM_M); // C=2*pi*r -> C=pi*2r -> C=pi*D
const double MAX_METERS_PER_SECOND(MAX_ROTATIONS_PER_SECOND * WHEEL_CIRCUMFERENCE_M);

const double CRUISE_SPEED(0.9 * MAX_RADIANS_PER_SECOND); // 90% of maximum spped

// Constants used with PID controller in the motor controller
const double KP(0.25);
const double KI(0.0008);
const double KD(0.0005);

// Pin Definitions - Defines all of the pins used
const uint8_t POLOLU_QIK_TX_PIN(0);     // tx Pololu qik
const uint8_t POLOLU_QIK_RX_PIN(1);     // rx Pololu qik
const uint8_t POLOLU_QIK_RESET_PIN(3);  // reset Pololu qik
const uint8_t M1_PHASE_B_PIN(31);       // right encoder phase b signal
const uint8_t M1_PHASE_A_PIN(32);       // right encoder phase a signal
const uint8_t M0_PHASE_B_PIN(34);       // left encoder phase b signal
const uint8_t M0_PHASE_A_PIN(35);       // left encoder phase a signal

// Motor manager
MotorAndEncoderManager* motorManager;

// Motor Controller
MotorController* motorController;

void setup() {
  Serial.begin(9600); // Only used for output messages for example
  
  //*** Start of implementation specific code

  // Using the Pololu Qik controller for this example, but you could
  // use any motor controller hardware that can drive the motor.
    
  // Setup the motor manager
  motorManager = 
    new PololuQik2s9v1MotorManager(
      POLOLU_QIK_TX_PIN, POLOLU_QIK_RX_PIN, POLOLU_QIK_RESET_PIN);

  // Setup encoders on the motor manager
  TeensyQuadratureMotorEncoder* leftEncoder =
      new TeensyQuadratureMotorEncoder(M0_PHASE_A_PIN, M0_PHASE_B_PIN);
  TeensyQuadratureMotorEncoder* rightEncoder =
      new TeensyQuadratureMotorEncoder(M1_PHASE_A_PIN, M1_PHASE_B_PIN);
  motorManager->setEncoders(leftEncoder, rightEncoder);
      
  //*** End of implementation specific code

  // Now set up the MotorController

  Serial.print("RADIANS_PER_TICK: ");
  Serial.println(RADIANS_PER_TICK);
  Serial.print("MAX_RADIANS_PER_SECOND: ");
  Serial.println(MAX_RADIANS_PER_SECOND);
  Serial.print("CRUISE_SPEED: ");
  Serial.println(CRUISE_SPEED);

  motorController = new MotorController(motorManager, KP, KI, KD, 50, RADIANS_PER_TICK, MAX_RADIANS_PER_SECOND);
  motorController->start();
}

bool dir = true;
uint32_t nextDirChangeTime = 0;
uint32_t nextAdjustTime = 0;

void loop() {
  if (millis() >= nextDirChangeTime) {
    dir = !dir;
    Serial.println(dir ? "Going forward" : "Going reverse");
    double speed = dir ? CRUISE_SPEED : -CRUISE_SPEED;
    Serial.println(speed);
    motorController->setDesiredSpeeds(speed, speed);

    // change direction in 5 seconds
    nextDirChangeTime = millis() + 5000;
  }
  
  if (millis() >= nextAdjustTime) {
    // adjust the speeds if needed
    motorController->adjustSpeeds();
    
    // Check back again in 10th of a second
    nextAdjustTime = millis() + 10;
  }
}
