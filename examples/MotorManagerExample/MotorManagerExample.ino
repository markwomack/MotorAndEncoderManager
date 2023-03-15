//
// Licensed under Apache 2.0 license.
// See accompanying LICENSE file for details.
//

// This is an example of using the motor controller with two motors,
// each with an associated encoder. It has code to intialize either the
// Pololu Qik or Ghost motor controllers.
// You can use this sketch to set the motor and controller setup on
// your robot to make sure the encoder values are increasing and
// decreasing correctly.

// Arduino includes
#include <Arduino.h>

// MotorManager includes
#include <MotorAndEncoderManager.h>
#include <PololuQik2s9v1MotorManager.h>
#include <TeensyQuadratureMotorEncoder.h>
#include <GhostMotorManager.h>
#include <ThreePhaseMotorEncoder.h>

// Pin Definitions used for the Pololu Qik motor controller
const uint8_t POLOLU_QIK_TX_PIN        =  0; // tx Pololu qik
const uint8_t POLOLU_QIK_RX_PIN        =  1; // rx Pololu qik
const uint8_t POLOLU_QIK_RESET_PIN     =  3; // reset Pololu qik
const uint8_t M1_PHASE_B_PIN    = 31; // Motor 1 encoder phase b signal
const uint8_t M1_PHASE_A_PIN    = 32; // Motor 1 encoder phase a signal
const uint8_t M0_PHASE_B_PIN    = 34; // Motor 0 encoder phase b signal
const uint8_t M0_PHASE_A_PIN    = 35; // Motor 0 encoder phase a signal

// Pin Definitions used for the Ghost motor controller
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

// Motor and encoder manager
MotorAndEncoderManager* motorManager;

// Motor encoders
MotorEncoder* m0Encoder = 0;
MotorEncoder* m1Encoder = 0;
  
float m0Speed;
float m1Speed;
bool m0IncrementDir;
bool m1IncrementDir;
uint32_t m0LastEncoder;
uint32_t m1LastEncoder;
double maxSpeed;

// This method has all of the motor and encoder specific
// code. You would probably only have the code for the
// specific motor controller your robot is using, but this
// code will support whichever controller you choose to
// test with.

// Controller types currently supported
enum ControllerType {
  POLOLU_QIK,
  GHOST
};

// Change this constant to the controller type
// to be used.
const ControllerType CONTROLLER_TYPE(GHOST);

void setupMotorManager() {

  //*** Start of implementation specific code

  switch (CONTROLLER_TYPE) {
    case POLOLU_QIK:
    {
      // Setup the encoders
      m0Encoder = new TeensyQuadratureMotorEncoder(M0_PHASE_A_PIN, M0_PHASE_B_PIN);
      m1Encoder = new TeensyQuadratureMotorEncoder(M1_PHASE_A_PIN, M1_PHASE_B_PIN);
        
      // Setup the motor manager
      motorManager = new PololuQik2s9v1MotorManager(
          POLOLU_QIK_TX_PIN, POLOLU_QIK_RX_PIN, POLOLU_QIK_RESET_PIN);
    }
    break;

    case GHOST:
    {
      // Setup the encoders
      ThreePhaseMotorEncoder* m0ThreePhaseEncoder = new ThreePhaseMotorEncoder();
      m0ThreePhaseEncoder->begin(M0_V_SIGNAL_PIN, M0_W_SIGNAL_PIN, M0_U_SIGNAL_PIN);
      m0Encoder = m0ThreePhaseEncoder;
      ThreePhaseMotorEncoder* m1ThreePhaseEncoder = new ThreePhaseMotorEncoder();
      m1ThreePhaseEncoder->begin(M1_V_SIGNAL_PIN, M1_W_SIGNAL_PIN, M1_U_SIGNAL_PIN);
      m1Encoder = m1ThreePhaseEncoder;
        
      // Setup the motor manager
      GhostMotorManager* ghostMotorManager = new GhostMotorManager();
      ghostMotorManager->begin(M0_SPEED_PIN, M0_DIR_PIN, M0_BRAKE_PIN,
        M1_SPEED_PIN, M1_DIR_PIN, M1_BRAKE_PIN);
      motorManager = (MotorAndEncoderManager*)ghostMotorManager;
      maxSpeed = 0.1; // Reduce the max speed for safety purposes
    }
    break;

    default:
    {
      Serial.println("*** ERROR - UNKNOWN MOTOR CONTROLLER ***");
    }
    break;
  }
  
  //*** End of implementation specific code

  // Set the encoders into the motor controller
  motorManager->setEncoders(m0Encoder, m1Encoder);

  // Make sure a max speed is assigned
  if (maxSpeed == 0) {
    maxSpeed = 1.0;
  }
}

void setup() {
  Serial.begin(9600); // Only used for output messages for example

  // Example using Pololu Qik, but you can change the
  // the ControllerType passed to this method.
  setupMotorManager();
  
  m0Speed = 0;
  m1Speed = 0;
  motorManager->setMotorSpeeds(m0Speed, m1Speed);
  motorManager->readAndResetEncoder(M0);
  motorManager->readAndResetEncoder(M1);
  m0IncrementDir = true;  // Start with positive speed
  m1IncrementDir = true;  // Start with positive speed
}

void loop() {
  // If at max speed, forward or reverse, switch increment
  // direction to slow the motor down
  if (abs(m0Speed) >= maxSpeed) {
    m0IncrementDir = !m0IncrementDir;
    Serial.print("Switching m0 increment direction: ");
    Serial.println(m0IncrementDir);
    m0Speed += m0IncrementDir ? 0.1 : -0.1;
  // If the motor speed is zero, check the encoders to
  // make sure the wheel has stopped spinning completely
  } else if (m0Speed == 0) {
    // Waiting for the motor to stop spinning, if it has, then
    // continue by incrementing
    uint32_t curEncoder = motorManager->readEncoder(M0);
    if (curEncoder - m0LastEncoder == 0) {
      m0Speed += m0IncrementDir ? 0.1 : -0.1;
    }
    m0LastEncoder = curEncoder;
  // Increment the speed
  } else {
    m0Speed += m0IncrementDir ? 0.1 : -0.1;
  }
  
  if (abs(m1Speed) >= maxSpeed) {
    m1IncrementDir = !m1IncrementDir;
    Serial.print("Switching m1 increment direction: ");
    Serial.println(m1IncrementDir);
    m1Speed += m1IncrementDir ? 0.1 : -0.1;
  } else if (m1Speed == 0) {
    // Waiting for the motor to stop spinning
    uint32_t curEncoder = motorManager->readEncoder(M1);
    if (curEncoder - m1LastEncoder == 0) {
      m1Speed += m1IncrementDir ? 0.1 : -0.1;
    }
    m1LastEncoder = curEncoder;
  } else {
    m1Speed += m1IncrementDir ? 0.1 : -0.1;
  }

  
  motorManager->setMotorSpeeds(m0Speed, m1Speed);

  Serial.print("M0 speed: ");
  Serial.print(m0Speed);
  Serial.print(", M1 speed: ");
  Serial.println(m1Speed);

  Serial.print("M0 ticks: ");
  Serial.print(motorManager->readEncoder(M0));
  Serial.print("(values should be ");
  Serial.print(m0Speed >= 0 ? "increasing)" : "decreasing)");
  if (CONTROLLER_TYPE == GHOST) {
    Serial.print(", faults: ");
    Serial.print(((ThreePhaseMotorEncoder*)m0Encoder)->readFaults());
  }
  Serial.print(", M1 ticks: ");
  Serial.print(motorManager->readEncoder(M1));
  Serial.print("(values should be ");
  Serial.print(m1Speed >= 0 ? "increasing)" : "decreasing)");
  if (CONTROLLER_TYPE == GHOST) {
    Serial.print(", faults: ");
    Serial.print(((ThreePhaseMotorEncoder*)m1Encoder)->readFaults());
  }
  Serial.println();

  // See you again in a half second
  delay(500);
}
