# MotorAndEncoderManager
<p>A library that provides support for controlling motors and associated encoders.
It is most appropriate for mobile robot applications.</p>

## Overview
<p>Mobile robots most often use motors to move around. There is a plethora of motor
control hardware out there, each with its own API. When using motors to move around
many robots also use associated encoders to track how much a motor (and thus an
attached wheel) has moved. Hall sensor quadrature encoders are the most common type
of encoder available (either built-in or as an add-on), but others are becoming more
common (such as 3-phase encoders on eScooter motors). The MotorAndEncoderManager
provides an API for motors and encoders that abstracts the specifics of the motor
controller and encoder hardware, and provides methods for doing what you need:
setting the motor speeds and reading the encoders (and more). Yes, you still have
to write some code that is specific to the motor controller hardware, but you do
this just once and then you can reuse it across multiple robots using the common
MotorAndEncoderManager api. And if you decide to switch contoller hardware, just
write a new code to support it, and you don't have to change your robot code at
all. Just use the new class instead.</p>
<p>As of this release, only a couple different controllers are supported, but it
is easy to write your own. If you do write your own, please considering submitting
it and it will be included in future releases.</p>

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
