# MotorManagerExample
<p>This example demonstrates how to initialize the motors and encoders for specific motor controller
hardware, and then how to call it. It currently supports two different motor controllers, the
Pololu Qik and Ghost controllers, and two different kinds of encoders, Quadrature and Three Phase.
The example is currently set to configure and use the Pololu Qik controller, but you can easily
change the code to use a different motor controller. The rest of the code is not motor controller
specific, and it will work with any controller/motor/encoder combination that your robot is using.</p>
<p>You can use this code when setting up the motors on your robot.
- With typical brushed or brushless robot motors using quadrature encoders, when the wheel is spinning
  "forward" the encoder tick count will be increasing, and when spinning "reverse" the encoder count
  will be decreasing. However, for a differential drive robot, the motors will need to spin in
  opposite directions in order for both the be going "forward" or "reverse". This is usually handled
  at the hardware level by swapping the power leads to one of the motors (You could do it in software
  too, but swapping the leads in much easier).
- With brushless dc (BLDC hoverboard-like motors it can be simpler. Instead of swapping leads, just
  mount the motors on your robot so that they are spinning clockwise for the "forward" direction of
  your robot. This is usually not a problem since the BLDC motors are self contained with a "hub"
  that the wheel rotates around.</p>
<p>Once you have the motor spinning in the correct directions (as recorded by the tick counts
increasing or decreasing), you are all set.</p>
