/*
 * StepperTest.cpp
 *
 *  Created on: Mar 4, 2020
 *      Author: amit
 */

/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
---->	http://www.adafruit.com/products/1438
*/

#include "../../../components/arduino-esp32/libraries/Wire/src/Wire.h"
#include "../Adafruit_MotorShield.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
//Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x69);

// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 1);


void Steppersetup() {
  //Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Stepper test!");

  //AFMS.begin();  // create with the default frequency 1.6KHz
  AFMS.begin();  // OR with a different frequency, say 1KHz

  myMotor->setSpeed(10);  // 10 rpm
}

void StepperMotorTask(void *arg)  {
	Steppersetup();


	while (1) {
		 myMotor->step(1, FORWARD, SINGLE);
//		 Serial.println("Single coil steps");
//  myMotor->step(100, BACKWARD, SINGLE);
//
//  Serial.println("Double coil steps");
//  myMotor->step(100, FORWARD, DOUBLE);
//  myMotor->step(100, BACKWARD, DOUBLE);
//
//  Serial.println("Interleave coil steps");
//  myMotor->step(100, FORWARD, INTERLEAVE);
//  myMotor->step(100, BACKWARD, INTERLEAVE);
//
//  Serial.println("Microstep steps");
//  myMotor->step(50, FORWARD, MICROSTEP);
//  myMotor->step(50, BACKWARD, MICROSTEP);
  delay(100);
}
}

