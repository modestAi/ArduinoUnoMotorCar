#include <AFMotor.h>

// Define motor pins
#define L1 A0
#define M1 A1
#define R1 A2

// Initialize motors
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

// Motor speeds
int forwardSpeed = 175;
int turnSpeedmax = 175;
int turnSpeedmin = 175;

void setup() {
  // Initialize serial communication and sensor pins
  Serial.begin(9600);
  pinMode(L1, INPUT);
  pinMode(M1, INPUT);
  pinMode(R1, INPUT);
}

void loop() {
  // Read sensor values
  int LSensor = digitalRead(L1);
  int MSensor = digitalRead(M1);
  int RSensor = digitalRead(R1);

  // Check sensor conditions for different movements
  if (LSensor == 0 && MSensor == 0 && RSensor == 0) { 
    // MOVE FORWARD
    moveForward(forwardSpeed);
  } else if (LSensor == 0 && MSensor == 0 && RSensor == 1) {
    // TURN LEFT
    turnLeft();
  } else if (LSensor == 1 && MSensor == 0 && RSensor == 0) {
    // TURN RIGHT
    turnRight();
  } else if (LSensor == 1 && MSensor == 1 && RSensor == 1) {
    // STOP-When no sensors are active
    stopMotors();
  } else if (LSensor == 0 && MSensor == 1 && RSensor == 1) {
    // STOP-When only Left sensor is active
    stopMotors();
  } else if (LSensor == 1 && MSensor == 1 && RSensor == 0) {
    // STOP-When only Right sensor is active
    stopMotors();
  }
}

void moveForward(int speed) {
  // Set motor speeds and run them forward
  setMotorSpeeds(speed, speed, speed, speed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  Serial.println("Moving Forward...");
}

void turnLeft() {
  // Set motor speeds for turning left and run motors
  setMotorSpeeds(turnSpeedmax, turnSpeedmin, turnSpeedmin, turnSpeedmax);
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  Serial.println("Turning Left...");
}

void turnRight() {
  // Set motor speeds for turning right and run motors
  setMotorSpeeds(turnSpeedmin, turnSpeedmax, turnSpeedmax, turnSpeedmin);
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  Serial.println("Turning Right...");
}

void stopMotors() {
  // Stop motors and release them
  setMotorSpeeds(0, 0, 0, 0);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  Serial.println("Stopped...");
}

void setMotorSpeeds(int m1Speed, int m2Speed, int m3Speed, int m4Speed) {
  // Set speeds for individual motors
  motor1.setSpeed(m1Speed);
  motor2.setSpeed(m2Speed);
  motor3.setSpeed(m3Speed);
  motor4.setSpeed(m4Speed);
}
