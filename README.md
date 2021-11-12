# Line Following Car with IR sensor

## Sensor Calibration 
Sensor_Calibration contain all of the code that we used to find calibration values for our sensors

### Sensor_calibration.ino 
Sensor_calibration.ino when uploaded to an arduino will read out the values recored to three IR sensors connected to analog input pin A0, A1, and A2. It prints the data collected into the serial monitor. We first put all three sensors off the line, collected data, then put all three sensors onto the line to see what the difference was. 

### Calibration_boxplot.rmd 
This is a R markdown file which we used to create our calibration boxplot. It uses the data that we entered into calibration.csv. 

## BangBang
BangBang was a older simplier version of the code which uses two IR sensors with the same cutoff value. It was never used, but was left in the repository as a template for more advanced code.

### WithMiddleSensor 
WithMiddleSensor  is our final robot code. It asks for an input of cutoff values. CUtoff values can be determined using Sensor_Calibration.ino. We picked values that were greater than the maximum reading off of the tape but lower than the minimum reading on the tape so that the robot would be able to clearly determine when it was on the tape.

### Project Report
This project was completed as a mini project for Principles of Intergrated engineering at Olin College of Engineering. A link to our report can be found here. 