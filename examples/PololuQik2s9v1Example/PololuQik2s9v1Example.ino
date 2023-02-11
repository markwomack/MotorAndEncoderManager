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

// Motor and encoder manager
MotorAndEncoderManager* motorManager;

float m0Speed;
float m1Speed;
bool m0IncrementDir;
bool m1IncrementDir;

void setup() {
  Serial.begin(9600); // Only used for output messages for example
  
  //*** Start of implementation specific code
  
  // Setup encoders
  TeensyQuadratureMotorEncoder* m0Encoder = new TeensyQuadratureMotorEncoder();
  m0Encoder->begin(M0_PHASE_A_PIN, M0_PHASE_B_PIN);
  TeensyQuadratureMotorEncoder* m1Encoder = new TeensyQuadratureMotorEncoder();
  m1Encoder->begin(M1_PHASE_A_PIN, M1_PHASE_B_PIN);
    
  // Setup the motor manager
  PololuQik2s9v1MotorManager* pololuQikMotorManager = new PololuQik2s9v1MotorManager();
  pololuQikMotorManager->begin(POLOLU_QIK_TX_PIN, POLOLU_QIK_RX_PIN, POLOLU_QIK_RESET_PIN);
  motorManager = (MotorAndEncoderManager*)pololuQikMotorManager;
  
  //*** End of implementation specific code

  motorManager->setEncoders(m0Encoder, m1Encoder);
  
  m0Speed = 0;
  m1Speed = 0;
  motorManager->setMotorSpeeds(m0Speed, m1Speed);
  motorManager->writeToEncoder(M0, 0);
  motorManager->writeToEncoder(M1, 0);
  m0IncrementDir = false; // forward
  m1IncrementDir = true; // reverse
}

void loop() {
  if (abs(m0Speed) >= 1.0) {
    Serial.println("Switching m0 direction");
    m0IncrementDir = !m0IncrementDir;
  }
  if (abs(m1Speed) >= 1.0) {
    Serial.println("Switching m1 direction");
    m1IncrementDir = !m1IncrementDir;
  }
  m0Speed += m0IncrementDir ? -0.1 : 0.1;
  m1Speed += m1IncrementDir ? -0.1 : 0.1;

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
