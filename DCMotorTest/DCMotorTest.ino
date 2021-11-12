/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
---->	http://www.adafruit.com/products/1438
*/


#include <Adafruit_MotorShield.h>

const int Sensor1Pin = A0; // Sensor output voltage

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);
int left_offset = 6;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  leftMotor->setSpeed(50-left_offset);
  rightMotor->setSpeed(50);
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
//  // turn on motor
//  motor1->run(RELEASE);
//  motor2->run(RELEASE);
}

// checkSensor() returns true if on the tape
bool checkSensor(){
  if (analogRead(Sensor1Pin) > 970) {
    return true;
  } else {
    return false;
  }
}

// searchRight() checks sensor while turning right, returning how long it turned for.
// If it never finds tape, return -1
int searchRight(int maxLoops=10000){
  bool onTape = checkSensor();
  int start_time = millis();
  int numLoops = 0;
  
  while (!onTape or numLoops >= maxLoops) {
    leftMotor->setSpeed(50-left_offset);
    rightMotor->setSpeed(50);
    leftMotor->run(FORWARD);
    rightMotor->run(BACKWARD);
    
    onTape = checkSensor();
    if (onTape) {
      Serial.println(onTape);
    }
    delay(10);
    numLoops ++;
  }
  
  int elapsed_time = -1;
  if (onTape) {
    elapsed_time = millis() - start_time;
  }

  leftMotor->setSpeed(0);
  rightMotor->setSpeed(0);
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
    
  return elapsed_time;
}

// searchLeft() checks sensor while turning left, returning how long it turned for.
// If it never finds tape, return -1
int searchLeft(int maxLoops=10000){
  bool onTape = checkSensor();
  int start_time = millis();
  int numLoops = 0;
  
  while (!onTape or numLoops >= maxLoops) {
    leftMotor->setSpeed(50-left_offset);
    rightMotor->setSpeed(50);
    leftMotor->run(BACKWARD);
    rightMotor->run(FORWARD);
    
    onTape = checkSensor();
    if (onTape) {
      Serial.println(onTape);
    }
    delay(10);
    numLoops ++;
  }
  
  int elapsed_time = -1;
  if (onTape) {
    elapsed_time = millis() - start_time;
  }

  leftMotor->setSpeed(0);
  rightMotor->setSpeed(0);
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
    
  return elapsed_time;
}

int findTape(){
  int maxLoopsRight = 100;
  int time_right = searchRight(maxLoopsRight);
  Serial.println("searchedRight");
  if (time_right == -1) {
    int time_left = searchLeft();
    Serial.println("searchedLeft");
    if (time_left == -1) {
      return -1;
    } else {
      return -(time_left);
    }
  } else {
    return +time_right;
  }
}

void loop() {
  findTape();
}
