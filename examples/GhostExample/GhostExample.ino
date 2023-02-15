//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

// This is an example of using the Ghost Motor Contoller
// which is a controller of two BLDC hoverboard-like
// with 3-phase motor encoders.

// Arduino includes
#include <Arduino.h>

// MotorManager includes
#include <MotorAndEncoderManager.h>
#include <GhostMotorManager.h>
#include <ThreePhaseMotorEncoder.h>

const uint8_t M0_DIR_PIN(2);
const uint8_t M0_BRAKE_PIN(3);
const uint8_t M0_SPEED_PIN(4);
const uint8_t M0_W_SIGNAL_PIN(5);  // green  - Hc
const uint8_t M0_V_SIGNAL_PIN(6);  // blue   - Hb
const uint8_t M0_U_SIGNAL_PIN(7);  // yellow - Ha
const uint8_t M1_W_SIGNAL_PIN(8);  // green  - Hc
const uint8_t M1_V_SIGNAL_PIN(9);  // blue   - Hb
const uint8_t M1_U_SIGNAL_PIN(10); // yellow - Ha
const uint8_t M1_DIR_PIN(11);
const uint8_t M1_BRAKE_PIN(12);
const uint8_t M1_SPEED_PIN(14);

const float MAX_SPEED(0.1);

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
  ThreePhaseMotorEncoder* m0Encoder = new ThreePhaseMotorEncoder();
  m0Encoder->begin(M0_V_SIGNAL_PIN, M0_W_SIGNAL_PIN, M0_U_SIGNAL_PIN);
  ThreePhaseMotorEncoder* m1Encoder = new ThreePhaseMotorEncoder();
  m1Encoder->begin(M1_V_SIGNAL_PIN, M1_W_SIGNAL_PIN, M1_U_SIGNAL_PIN);
    
  // Setup the motor manager
  GhostMotorManager* ghostMotorManager = new GhostMotorManager();
  ghostMotorManager->begin(M0_SPEED_PIN, M0_DIR_PIN, M0_BRAKE_PIN,
      M1_SPEED_PIN, M1_DIR_PIN, M1_BRAKE_PIN);
  motorManager = (MotorAndEncoderManager*)ghostMotorManager;
  
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
