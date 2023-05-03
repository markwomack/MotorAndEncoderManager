[THIS IS A WORK IN PROGRESS]

# Arduino Uno
This is a project to build a mobile robot using the Arduino Uno microcontroller and other
various electronic parts. It won't be the most powerful robot you might build, but this
project is meant to show you the fundamental elements that you will need to know about
when building just about any mobile robot. I hope that you can use it as a jumping off
point to build more awesome robots.

## Expertise Needed
If you have never built a robot before, if you have never programmed a microcontroller
before, that is fine. You will need a computer (PC/Mac) and be familiar with installing
software on it. Having some programming background is useful as well. There are lots
of resources on the interwebs for learning to program the Arduino Uno. If you decide
you'd like to have a book to learn about using the Arduino Uno before jumping into robots,
I can highly recommend Simon Monk's
[Programming Arduino: Getting Started with Sketches](https://www.amazon.com/Programming-Arduino-Getting-Started-Sketches/dp/1264676980).
His writing style makes it easy to learn and follow along.

## Parts List
I'm going to go over the specific parts in more detail, but here is the list of all the
parts used to build this robot, with approximate costs. I've chosen most of the parts
from an outfit called SparkFun. I'm not getting any kind of kick back from them. It's
just easier to deal with just one or two sources, and I think they are a great source
for robot related gadgets. But if you can get the parts from someplace else, that is
fine too. But if the parts are different, you will be on your own to adapt them into
the overall build. Sometimes that can be half the fun! But if you are just staring out
you may want to stick with this list.

- [Arduino Uno](https://www.sparkfun.com/products/11021) - This will be the heart of
  the robot, controlling all it's actions. ($27.95)
- [breadboard](https://www.sparkfun.com/products/12615) - If you don't already have a
  breadboard, this is a nice one to have. We will need a single full size breadboard
  for this project. ($6.50)
- [jumper wires](https://www.sparkfun.com/products/14284) - To go with the breadboard,
  we will use these to connect the components together. ($2.75)
- [motors](https://www.sparkfun.com/products/13302) - This is a pair of inexpensive
  hobby motors that will be used for the robot. ($5.50)
- [wheels](https://www.sparkfun.com/products/13259) - Some basic wheels that attach to
  the motors. ($3.50)
- [wheel encoder kit](https://www.sparkfun.com/products/12629) - These encoders can
  be added to the motors to sense how far the wheels have turned. ($13.95)
- [motor driver](https://www.sparkfun.com/products/14450) - This sinple motor driver
  powers the motors and allows for speed and direction control. ($9.95)
- [battery holder](https://www.amazon.com/LAMPVPATH-Pack-Battery-Holder-Switch/dp/B07T83B4SW) - A
  battery holder for a 9 volt battery that will provide power to the motors and
  the Arduino Uno. We need a holder that has bare wires, and these fit the bill. ($5.90)
- [5v power regulator](https://www.sparkfun.com/products/21255) - We need to reduce
  the 9 volts from the battery to 5 volts for the motors. ($5.50)
- [Ultrasonic Distance Sensor - HC-SR04](https://www.sparkfun.com/products/15569) - This
  is a basic sensor for measuring distance to an object or wall. We will use it to
  detect obstacles before running into them. ($4.50)

In addition, some nice-to-haves-but-maybe-not-required:

- Wire stippers - We are using jumper wires, so there shouldn't be much need to strip
  wires, but if you are going to get serious about robots you will need one. A
  stripper that can strip at least 18 AWG to 24 AWG is fine.
- Multimeter - Hopefully you will connect everything exactly right the first time.
  But a cheap multimeter can come in handy when trying to track down connections.
  
For this project you won't need a soldering iron. I've endeavored to choose parts
that can be wired together without the need to learn how to solder. It is as plug-
and-play as possible.

## Decisions
When designing and building almost any mobile robot from scratch there are some
basic decisions you need to make early, and those decisions will usually inform other
decisions down-the-line.

### Motors

### Power
