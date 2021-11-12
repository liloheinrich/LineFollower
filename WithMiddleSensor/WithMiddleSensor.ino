
#include <Adafruit_MotorShield.h>

const int leftSensorPin = A2; // 880-940: use 910 as cutoff
const int middleSensorPin = A1; // 830-900: use 870 as cutoff
const int rightSensorPin = A0; // 790-870: use 840 as cutoff

int cutoff_left = 920;
int cutoff_mid = 850;
int cutoff_right = 800;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

int left_offset = 6;
int default_speed = 50;
char serial_state = '-';

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

//  start up the serial console input system
  Serial.println("Type letter \"L\", \"M\", or \"R\" to set new IR threshold value in range (0,1023)");
  Serial.print("LeftIR = ");
  Serial.print(cutoff_left);
  Serial.print(" | MiddleIR = ");
  Serial.print(cutoff_mid);
  Serial.print(" | RightIR = ");
  Serial.println(cutoff_right);
  Serial.println();

  // Set the speed to start, from 0 (off) to 255 (max speed)
  stop_driving();
}

// checkSensor() returns true sensor if on the tape
bool checkSensor(int sensorPin, int cutoff_value){
  if (analogRead(sensorPin) > cutoff_value) {
    return true;
  }
  return false;
}

void turn(bool leftDir){
  int sensorPin = rightSensorPin;
  if (leftDir) {
    sensorPin = leftSensorPin;
  }
  if (leftDir) {
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(default_speed);
  } else {
    leftMotor->setSpeed(default_speed-left_offset);
    rightMotor->setSpeed(0);
  }
  leftMotor->run(FORWARD);
  rightMotor->run(FORWARD);
}

//void turn_slightly(bool leftDir){
//  int sensorPin = rightSensorPin;
//  if (leftDir) {
//    sensorPin = leftSensorPin;
//  }
//  if (leftDir) {
//    leftMotor->setSpeed((default_speed-left_offset) / 2);
//    rightMotor->setSpeed(default_speed);
//  } else {
//    leftMotor->setSpeed(default_speed-left_offset);
//    rightMotor->setSpeed(default_speed / 2);
//  }
//  leftMotor->run(FORWARD);
//  rightMotor->run(FORWARD);
//}

void forward(){
    leftMotor->setSpeed(default_speed-left_offset);
    rightMotor->setSpeed(default_speed);
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
}

void stop_driving(){
    leftMotor->setSpeed(0);
    rightMotor->setSpeed(0);
    leftMotor->run(FORWARD);
    rightMotor->run(FORWARD);
}

void search() {
  turn(true);
}

void loop() {
  updateFromSerial() // this gets updated IR cutoff/threshold values from serial console input menu
  
//  Serial.print("Left: ");
//  Serial.print(checkSensor(leftSensorPin, cutoff_left));
//  Serial.print(" | Mid: ");
//  Serial.print(checkSensor(middleSensorPin, cutoff_mid));
//  Serial.print(" | Right: ");
//  Serial.println(checkSensor(rightSensorPin, cutoff_right));
//  Serial.print("Left: ");
//  Serial.print(analogRead(leftSensorPin));
//  Serial.print(" | Mid: ");
//  Serial.print(analogRead(middleSensorPin));
//  Serial.print(" | Right: ");
//  Serial.println(analogRead(rightSensorPin));
  
  if (checkSensor(middleSensorPin, cutoff_mid)) { // and (!checkSensor(leftSensorPin, cutoff_left) or !checkSensor(rightSensorPin, cutoff_right))){
    forward();
//  } else if (checkSensor(leftSensorPin, cutoff_left) and checkSensor(middleSensorPin, cutoff_mid)){
//    turn(true); // turn left
//  } else if (checkSensor(middleSensorPin, cutoff_mid) and checkSensor(rightSensorPin, cutoff_right)){
//    turn(false); // turn right
  } else if (checkSensor(leftSensorPin, cutoff_left) and !checkSensor(rightSensorPin, cutoff_right)){
    turn(true); // turn left
  } else if (!checkSensor(leftSensorPin, cutoff_left) and checkSensor(rightSensorPin, cutoff_right)){
    turn(false); // turn right
  } else if (!checkSensor(middleSensorPin, cutoff_mid) and !checkSensor(leftSensorPin, cutoff_left) and !checkSensor(rightSensorPin, cutoff_right)){
    search(); 
  } 
}

// allows the user to update the three IR sensor threshold/cutoff values
void updateFromSerial(){
  if (Serial.available()) { 

//    serial_state not being '-' (null) means that the program knows which sensor to change the threshold for
//    therefore, the next value that it expects as input is an integer on (0,1023)
    if ((serial_state != '-')) { 
      int value = Serial.parseInt();
      Serial.println(value);

      if (value > 0 and value < 1023){
        if (serial_state == 'L') {
          cutoff_left = value;
          Serial.println("Left IR threshold set!");
        } else if (serial_state == 'M') {
          cutoff_mid = value;
          Serial.println("Middle IR threshold set!");
        } else if (serial_state == 'R') {
          cutoff_right = value;
          Serial.println("Right IR threshold set!");
        }

// the program does not know which sensor to change the threshold for
// therefore it is waiting for a letter L M or R to specify
      } else {
        Serial.println("Invalid IR threshold value given.");
      }
      Serial.print("LeftIR = ");
      Serial.print(cutoff_left);
      Serial.print(" | MiddleIR = ");
      Serial.print(cutoff_mid);
      Serial.print(" | RightIR = ");
      Serial.println(cutoff_right);
      Serial.println();
      
      serial_state = '-';
      Serial.read();
    } else { 
      char ch = Serial.read();
      serial_state = '-';
      
      if (ch == 'L') {
        serial_state = 'L';
        Serial.print("Set Left IR threshold: ");
      } else if (ch == 'M') {
        serial_state = 'M';
        Serial.print("Set Middle IR threshold: ");
      } else if (ch == 'R') {
        serial_state = 'R';
        Serial.print("Set Right IR threshold: ");
      } 
      Serial.parseInt();
    }
  }
}
