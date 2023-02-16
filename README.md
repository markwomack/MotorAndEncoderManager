# MotorAndEncoderManager
A library that provides support for controlling motors and associated encoders.
It is mostly appropriate for mobile robot applications.

## Overview
Mobile robots most often use motors to move around. There is a plethora of motor
control hardware out there, each with its own API. When using motors to move around,
many robots also use associated encoders to track how much a motor (and thus an
attached wheel) has moved. A hall sensor quadrature encoder is the most common type
of encoder available (either built-in or as an add-on), but others are becoming more
common (such as 3-phase encoders on eScooter motors). The MotorAndEncoderManager
provides an API for motors and encoders that abstracts the specifics of the motor
controller and encoder hardware, and provides methods for doing what you need:
setting the motor speeds and reading the encoders (and more). Yes, you still have
to write some code that is specific to the motor controller hardware, but you do
this just once and then you can reuse it across multiple robots using the common
MotorAndEncoderManager api. And if you decide to switch contoller hardware, just
write a new code to support it, and you don't have to change your robot code at
all. Just use the new class instead.

As of this release, only a couple different controllers are supported, but it
is easy to write your own. If you do write your own, please considering submitting
it and it will be included in future releases.

## Acknowledgements
- attachInterruptEx - The attachInterruptEx files included with this library are
thanks to [luni64](https://github.com/luni64) and can be
[found here](https://github.com/luni64/TeensyHelpers) (along with other great stuff).

## Dependencies
Please see the
[DEPENDENCIES](https://github.com/markwomack/MotorAndEncoderManager/blob/main/DEPENDENCIES.md)
file for a complete list of dependencies used by this code. I have endeavored to keep
the gratuitous dependencies to a minimum, but since this is a library that abstracts
details, the hiding of details means there are some dependencies. At least on the
underlying contoller or encoder specific libraries.

## Caveats
This could also be considered a dependency, but it is definitely a buyer-be-aware:
I have only used this code on [Teensy microcontrollers](https://www.pjrc.com/store/).
Unless otherwise noted, it is probably also compatible with other Arduino microcontrollers,
but you may need to do some work to make it happen. And if you haven't used a Teensy
in your own projects yet, you owe it to yourself to give it a whirl. I don't think
you will be sorry.

## Class Roadmap

### [MotorAndEncoderManager](https://github.com/markwomack/MotorAndEncoderManager/blob/main/src/MotorAndEncoderManager.h)
This is the class that defines the api for interacting with motors and encoders.
Specific subclasses should be implemented for specific motor controller hardware.
Currently there are two implementations provided:

- [Pololu Qik 2s9v1 motor controller](https://github.com/markwomack/MotorAndEncoderManager/blob/main/src/PololuQik2s9v1MotorManager.h)
- [Ghost motor controller](https://github.com/markwomack/MotorAndEncoderManager/blob/main/src/GhostMotorManager.h)

### [MotorEncoder](https://github.com/markwomack/MotorAndEncoderManager/blob/main/src/MotorEncoder.h)
This is the class that defines the api for interacting with encoders. Specific
subclasses should be implemented for specific encoder hardware.
Currently there are two implementations provided:

- [Teensy Quadrature encoder](https://github.com/markwomack/MotorAndEncoderManager/blob/main/src/TeensyQuadratureMotorEncoder.h) - 
  provides an implementation using the Teensy Quadrature Encoder library.
- [Three Phase encoder](https://github.com/markwomack/MotorAndEncoderManager/blob/main/src/ThreePhaseMotorEncoder.h) - 
  provides an implemenation for a three phase encoder found in hoverboard-like BLDC motors.
  
### [MotorController](https://github.com/markwomack/MotorAndEncoderManager/blob/main/src/MotorController.h)
This class goes beyond the MotorAndEncoderManager api to provide a class that will use the
motor and encoders to make sure the motors maintain a desired speed. This means that the
robot motors will be monitored and controlled to make sure they perform to the desired
speed. It is compatible with any MotorAndEncoderManager and MotorEncoder implementations.
Please see the [README in the MotorController example](https://github.com/markwomack/MotorAndEncoderManager/blob/main/examples/MotorControllerExample/README.md) for more information.

## Example Roadmap

### [MotorManagerExample](https://github.com/markwomack/MotorAndEncoderManager/tree/main/examples/MotorManagerExample)
This is a basic example of how to initialize specific instances of the MotorAndEncoderManager
and then use them to drive the motors.

### [MotorControllerExample](https://github.com/markwomack/MotorAndEncoderManager/tree/main/examples/MotorControllerExample)
This is a basic example of how to use the MotorController class to drive motors so
that they run at the same speed, and your robot will drive straight for a long distance
instead off veering to one side or the other.
