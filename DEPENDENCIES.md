# Dependencies
<p>The MotorAndEncoderManager library has the following dependencies:</p>

- [Pololu Qik controller](https://github.com/pololu/qik-arduino) - For support of the Pololu Qik motor controller.
- [PID controller](https://github.com/br3ttb/Arduino-PID-Library) - The PID library is used by the MotorController implementation.
- [Teensy Encoder](https://github.com/PaulStoffregen/Encoder) - The Teesy Encoder library is installed as part of the Teensy Arduino development installation. It provides an implementation of a quadrature encoder.

<p>Just install these libraries in the Arduino libraries directory and restart the Arduino IDE.</p>

<p>The examples written for this library do not have any other dependencies, but I would like to recommend a couple
of my other libraries that I have found to be useful when writing code for my own robots:</p>

- [TaskManager](https://github.com/markwomack/TaskManager) - This library provides a simple, best-effort task manager
that helps you organize your code into executable tasks. It provides a useful utility task for blinking an LED, and
support for a start/stop button to control execution.
- [ArduinoLogging](https://github.com/markwomack/ArduinoLogging) - A simple to use library for printing debug
messages in your program. You can control whether messages of a certain level are printed, where the messages are
printed (different Serial instance or even a UDP port), and easy concatenation of strings and values.
