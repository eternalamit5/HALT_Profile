/*
 * BMI160Test.cpp
 *
 *  Created on: Nov 29, 2019
 *      Author: karsh
 */

#include "../BMI160Gen.h"
#include "../arduino-esp32/cores/esp32/Arduino.h"
#include "../arduino-esp32/libraries/Wire/src/Wire.h"


static char BMI160_TEST_TAG[]={"BMI160_Test: "};



typedef enum{
	GYRO_125=125,
	GYRO_250=250,
	GYRO_500=500,
	GYRO_1000=1000,
	GYRO_2000=2000
}gyroScaling_ForRange_t;

typedef enum{
	ACC_2G=16384,
	ACC_4G=8192,
	ACC_8G=4096,
	ACC_16G=2048
}accelScaling_ForRange_t;



float convertRawGyro(int gRaw,gyroScaling_ForRange_t scaleRange) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767

  float g = (gRaw * (scaleRange*1.0)) / 32768.0;

  return g;
}


float convertRawAccel(int gRaw,accelScaling_ForRange_t scaleRange) {

  float g = (gRaw /(scaleRange*1.0));

  return g;
}

void setup() {

  Serial.println("Initializing IMU device...");


}

void testTask(void* arg) {

  BMI160.begin(BMI160GenClass::I2C_MODE,0x69);

  BMI160.setGyroRange(250);
  BMI160.setAccelerometerRange(16);

  int axRaw, ayRaw, azRaw,gxRaw, gyRaw, gzRaw;
  float gx, gy, gz,ax, ay, az;

  while(1){
	  //Gyro:
		  //Take raw measurement
		  BMI160.readGyro(gxRaw, gyRaw, gzRaw);

		  // convert the raw gyro data to degrees/second
		  gx = convertRawGyro(gxRaw,GYRO_250);
		  gy = convertRawGyro(gyRaw,GYRO_250);
		  gz = convertRawGyro(gzRaw,GYRO_250);

		  // display result
		  ESP_LOGI(BMI160_TEST_TAG,"Gyro: [x] %f ,[y] %f ,[z] %f",gx,gy,gz);


	  //Accel:
		  //Take raw measurement
		  BMI160.readAccelerometer(axRaw, ayRaw, azRaw);

		  //Convert raw to G
		  ax = convertRawAccel(axRaw,ACC_2G);
		  ay = convertRawAccel(ayRaw,ACC_2G);
		  az = convertRawAccel(azRaw,ACC_2G);

		  // display result
		  ESP_LOGI(BMI160_TEST_TAG,"Acce: [x] %f ,[y] %f ,[z] %f",ax,ay,az);


	   delay(500);
  }
  vTaskDelete(NULL);

}



