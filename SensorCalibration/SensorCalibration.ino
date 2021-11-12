
const int left = A2; // 720-831: use 800 as cutoff
const int mid = A1; // 720-827: use 800 as cutoff
const int right = A0; // 670-755: use 720 as cutoff

const int cutoff_left = 800;
const int cutoff_mid = 800;
const int cutoff_right = 720;

#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);

void setup() 
{
  Serial.begin(9600);
  pinMode(left, INPUT);
  pinMode(mid, INPUT);
  pinMode(right, INPUT);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");

  // Set the speed to start, from 0 (off) to 255 (max speed)
  motor1->setSpeed(0);
  motor2->setSpeed(0);
  motor1->run(FORWARD);
  motor2->run(FORWARD);
}

void loop() 
{
  // Read in the ADC and convert it to a voltage:
  Serial.println("left, mid, right");
  for (int i = 0; i <= 10; i++) {
    Serial.print(analogRead(left));
    Serial.print(",");
    Serial.print(analogRead(mid));
    Serial.print(",");
    Serial.println(analogRead(right));
    delay(10);
  }
  delay(1000);
}
