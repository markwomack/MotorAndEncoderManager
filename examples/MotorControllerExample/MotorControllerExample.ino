//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

#include <Arduino.h>

// These are the contants based on the specific motors and encoders being used.
// You should use values that match your own robot.

// Total encoder ticks for single wheel revolution
const double TICKS_PER_ROTATION(3000.0); // 250:1 gear ratio * 12 ticks per single motor rotation

// Code will use Radians (angular velocity) for velocity measurements
// Note: There are 2 radians in a single rotation (360 degrees)
const double RADIANS_PER_TICK(2 / TICKS_PER_ROTATION);

// This constant is based on measurements of the motor performance using a
// 5v power source. Your mileage may vary and you should verify your robots
// values by running the motors at full power (1) for a second and recording
// the encoder values.
// When motor is run at full for one second, this is approximately
// how many ticks it will turn.
const double MAX_TICKS_PER_SECOND(3600.0);

// This is the number of wheel rotations when run at full for one second.
const double MAX_ROTATIONS_PER_SECOND(MAX_TICKS_PER_SECOND / TICKS_PER_ROTATION);

// This is the max radians per second when run at full speed.
// Note: there are 2 radians in one rotation.
const double MAX_RADIANS_PER_SECOND(MAX_ROTATIONS_PER_SECOND * 2);

// This is the max meters per second when run at full speed.
// It is just for reference, since the MotorController will use radians/second.
// Wheel diameter in meters (31 mm)
const double WHEEL_DIAM_M(0.031);
const double WHEEL_CIRCUMFERENCE_M(PI * WHEEL_DIAM_M); // C=2*pi*r -> C=pi*2r -> C=pi*D
const double MAX_METERS_PER_SECOND(MAX_ROTATIONS_PER_SECOND * WHEEL_CIRCUMFERENCE_M);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
