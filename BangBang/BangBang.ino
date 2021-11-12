
#include <Adafruit_MotorShield.h>

const int middleSensorPin = A0; 
const int leftSensorPin = A1;
const int rightSensorPin = A2;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);
int left_offset = 6;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(50-left_offset);
  rightMotor->setSpeed(50);
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);

}

// checkSensor() returns true sensor if on the tape
bool checkSensor(int sensorPin){
  if (analogRead(sensorPin) > 970) {
    return true;
  } else {
    return false;
  }
}


void turnLeft(){
  while(checkSensor(leftSensorPin)) {
    leftMotor->setSpeed(50-left_offset);
    rightMotor->setSpeed(50);
    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);
  }
}


void turnRight(){
  while(checkSensor(rightSensorPin)) {
    leftMotor->setSpeed(50-left_offset);
    rightMotor->setSpeed(50);
    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);
  }
}

void driveForward(){
    leftMotor->setSpeed(50-left_offset);
    rightMotor->setSpeed(50);
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
}


void loop() {
  if (checkSensor(leftSensorPin)){
    turnLeft();
  } else if (checkSensor(rightSensorPin)) {
    turnRight();
  } else {
    driveForward(); 
  }
}
