/*
 * PCA9685test.cpp
 *
 *  Created on: Feb 17, 2020
 *      Author: amit
 */

/***************************************************
 This is an example for our Adafruit 16-channel PWM & Servo driver
 Servo test - this will drive 8 servos, one after the other on the
 first 8 pins of the PCA9685

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/products/815

 These drivers use I2C to communicate, 2 pins are required to
 interface.

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries.
 BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "../../../components/arduino-esp32/libraries/Wire/src/Wire.h"
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x71);
//Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  110 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  510 // this is the 'maximum' pulse length count (out of 4096)

// May have to adjust values to match your servos
// Test your servo with the procedures below

// our servo # counter
uint8_t servonum = 0;
int convert2angle(int myang);

void servosetup() {

	Serial.println("pca9685_TurnoutTest!");
	pwm.begin();
	pwm.setPWMFreq(50);  // Analog servos run at ~50 Hz updates
	delay(50);
}
///////////////////Functions//////////////////////

void driveMin() {
	pwm.setPWM(servonum, 0, SERVOMIN);    //Use to test low range
}
void driveMax() {
	pwm.setPWM(servonum, 0, SERVOMAX);    //Use to test high range
}
///////////////End Of Functions//////////////////

void PCA9685Task(void *arg) {
	servosetup();
	while (1) {

		for (int angle = 0; angle < 181; angle += 15) { // testing only right now
			delay(500);
			pwm.setPWM(1, 0, convert2angle(angle)); // May only need this for sweeping the servo
		}
	}
}

int convert2angle(int myang) {
	int pulse = map(myang, 0, 180, SERVOMIN, SERVOMAX); // map angle of 0 to 180 to Servo min and Servo max
	Serial.print("Angle/Pulse: ");
	Serial.print(myang);
	Serial.print(" / ");
	Serial.println(pulse);
	return pulse;
}
