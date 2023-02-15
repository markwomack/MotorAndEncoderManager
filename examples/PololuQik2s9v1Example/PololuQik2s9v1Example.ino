//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

// This is an example of using the PololuQik2s9v1 motor
// controller with two motors, each with a quadrature motor
// encoder.

// Arduino includes
#include <Arduino.h>

// MotorManager includes
#include <MotorAndEncoderManager.h>
#include <PololuQik2s9v1MotorManager.h>
#include <TeensyQuadratureMotorEncoder.h>

// Pin Definitions - Defines all of the pins used
const uint8_t POLOLU_QIK_TX_PIN        =  0; // tx Pololu qik
const uint8_t POLOLU_QIK_RX_PIN        =  1; // rx Pololu qik
const uint8_t POLOLU_QIK_RESET_PIN     =  3; // reset Pololu qik
const uint8_t M1_PHASE_B_PIN    = 31; // right encoder phase b signal
const uint8_t M1_PHASE_A_PIN    = 32; // right encoder phase a signal
const uint8_t M0_PHASE_B_PIN    = 34; // left encoder phase b signal
const uint8_t M0_PHASE_A_PIN    = 35; // left encoder phase a signal

const float MAX_SPEED(1.0);

// Motor and encoder manager
MotorAndEncoderManager* motorManager;

float m0Speed;
float m1Speed;
bool m0IncrementDir;
bool m1IncrementDir;
uint32_t m0LastEncoder;
uint32_t m1LastEncoder;

void setup() {
  Serial.begin(9600); // Only used for output messages for example
  
  //*** Start of implementation specific code
  
  // Setup encoders
  TeensyQuadratureMotorEncoder* m0Encoder =
      new TeensyQuadratureMotorEncoder(M0_PHASE_A_PIN, M0_PHASE_B_PIN);
  TeensyQuadratureMotorEncoder* m1Encoder =
      new TeensyQuadratureMotorEncoder(M1_PHASE_A_PIN, M1_PHASE_B_PIN);
    
  // Setup the motor manager
  motorManager = new PololuQik2s9v1MotorManager(POLOLU_QIK_TX_PIN, POLOLU_QIK_RX_PIN, POLOLU_QIK_RESET_PIN);
  
  //*** End of implementation specific code

  motorManager->setEncoders(m0Encoder, m1Encoder);
  
  m0Speed = 0;
  m1Speed = 0;
  motorManager->setMotorSpeeds(m0Speed, m1Speed);
  motorManager->readAndResetEncoder(M0);
  motorManager->readAndResetEncoder(M1);
  m0IncrementDir = false; // forward
  m1IncrementDir = true; // reverse
}

void loop() {
  if (abs(m0Speed) >= MAX_SPEED) {
    Serial.println("Switching m0 direction");
    m0IncrementDir = !m0IncrementDir;
    m0Speed += m0IncrementDir ? -0.1 : 0.1;
  } else if (m0Speed == 0) {
    // Waiting for the motor to stop spinning
    uint32_t curEncoder = motorManager->readEncoder(M0);
    if (curEncoder - m0LastEncoder == 0) {
      m0Speed += m0IncrementDir ? -0.1 : 0.1;
    }
    m0LastEncoder = curEncoder;
  } else {
    m0Speed += m0IncrementDir ? -0.1 : 0.1;
  }
  
  if (abs(m1Speed) >= MAX_SPEED) {
    Serial.println("Switching m1 direction");
    m1IncrementDir = !m1IncrementDir;
    m1Speed += m1IncrementDir ? -0.1 : 0.1;
  } else if (m1Speed == 0) {
    // Waiting for the motor to stop spinning
    uint32_t curEncoder = motorManager->readEncoder(M1);
    if (curEncoder - m1LastEncoder == 0) {
      m1Speed += m1IncrementDir ? -0.1 : 0.1;
    }
    m1LastEncoder = curEncoder;
  } else {
    m1Speed += m1IncrementDir ? -0.1 : 0.1;
  }

  motorManager->setMotorSpeeds(m0Speed, m1Speed);

  Serial.print("M0 speed: ");
  Serial.print(m0Speed);
  Serial.print(", M1 speed: ");
  Serial.println(m1Speed);
  
  Serial.print("M0 ticks: ");
  Serial.print(motorManager->readEncoder(M0));
  Serial.print(", M1 ticks: ");
  Serial.println(motorManager->readEncoder(M1));

  // See you again in a half second
  delay(500);
}
