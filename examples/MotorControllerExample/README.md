# MotorControllerExample
<p>Having the MotorAndEncoderManager interface generalize the commands to any motor controller hardware
is great. Now your robot code doesn't have to be concerned with what specific hardware calls to use, the
MotorAndEncoderManager implementation handles all that. But your robot still won't drive straight. Even
though both motors are the same model and running on the same power, they will always perform differently
than each other. Maybe slightly, maybe alot. It's just a fact.</p>
<p>To address this issue, the MotorController class is included in this library. Using the
MotorAndEncoderManager instance and a proportional–integral–derivative (PID) controller on each motor,
the MotorController will control the speeds of the motor so that they perform at the expected speed.</p>
<p>First, the definitions of 'speed' are in order.
  
- For the MotorAndEncoderManager 'speed' means the amount of power being applied to the motor. It is a
  value between 1 and -1 where positive values are forward and negative values are reverse.
- For the MotorController 'speed' means the velocity of the turning motor as measured by the tick count
  between two points in time. This is not a speed in the way you normally think, like mph or millimeters
  per second. This speed is measured as a radial velocity, how fast the motor is turning. This is because
  the actual speed of the robot, how fast and how far it moves, is also dependent on the size of the
  wheels. One turn of a wheel with a larger diameter than another will travel farther. Radial velocity
  abstracts all of that away by using radians and the ticks of the encoder. You can think of radians
  similar to degrees of a circle (though they are different) to measure how far the motor has turned,
  and thus how fast it is turning in radians per secon between points in time.</p>
  
<p>You can take a look at the constants that are defined in this example and apply them to your
own robot. You just need to know two things:</p>

- How many ticks are recorded by a single turn of the wheel? As you will see below, a single turn of
the wheel might require many multiple turns of the motor due to gears. But once you know how many ticks in
a single motor rotation, it is easy math to calculate the total ticks for a wheel rotation.

- How many ticks will be recorded when the motor is run for one second? This you will need to test
through observation. Perform the test several times, record the results, average it out.

<p>Once you know those two pieces of information, everything is calculated and explained in the comments
of the example. The MotorController uses radians per second as the unit it will use when controlling
the speed. It will periodically check the performance of the motors and adjust their speed (power)
until they match the desired speed (in radians/second).</p>

<p>For this example, it is useful to know what motors and encoders were used to calculate all of the constants.
The motors are Pololu 250:1 Micro Metal Gearmotor with Extended Gear Shaft (https://www.pololu.com/product/3055).
The 250:1 gear ratio means that it takes 250 rotations of the motor shaft to rotate the wheel shaft a single
time. The quadrature encoders used are an add-on, not built into the original motor. The Pololu Magnetic Encoder
(https://www.pololu.com/product/2598) is attached to the extended gear (motor) shaft, and there are 12 ticks per
revolution. Because the encoder is attached to the motor shaft and not the wheel shaft, this means that there
are 250 * 12 = 3000 ticks per single revolution of the wheel shaft.</p>

<p>Even though the motor is rated for up to 12 volts, on my robot I am running it with only 5 volts. This means
that they will turn slower than when at 12 volts. So, in order to know how many ticks the motor will turn in
a second, I just created a program to run the motor at full power 5v (or 1 when using the MotorAndEncoderManager
calls) for one second and then read the ticks. When I did this several times I came up with 3600 ticks.</p>

<p>Plugging 3000 ticks per wheel rotation and 3600 ticks per second into the example constants means that my
robot can travel 2.14 radians per second when at full power. And that is the value given to the MotorController
that it can use when calculating the speeds (power) to set the motors to.</p>

<p>If you know the diameter of the wheels being used, you can also translate this into meters per second, so you
can get a better sense of how fast your robot will move. The MotorController doesn't use this measurement, but
it will be easier for you to grasp than radians per second. The wheels I am using have a diameter of 31mm,
which means they have a circumference of just over 97mm. Given the ticks per revolution and ticks per second,
my robot will travel almost 117mm per second. The calculations for this are also in the example, and you can
always double check it with observation.</p>

<p>This is all just a long way of saying once you have the two needed bits of information and you load this
example onto your robot, then the MotorController will drive your robot forward for 5 seconds, then backwards
for 5 seconds, ad infinitum. You should see that the robot stays on a fairly straight trajectory as it goes
back and forth. Drift will still happen over time, and the wheels can always slip on the surface, but the
robot should perform better than if it were just using the MotorAndEncoderManager by itself.</p>

