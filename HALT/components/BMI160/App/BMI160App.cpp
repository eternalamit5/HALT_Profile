/*
 * BMI160App.cpp
 *
 *  Created on: Dec 1, 2019
 *      Author: karsh
 */

#include "BMI160App.h"
#include "esp_log.h"

static char BMI160APP_TAG[]={"BMI160App: "};

BMI160App::BMI160App(int i2cAddress,gyroScaling_ForRange_t gyroScaling,accelScaling_ForRange_t accelScaling){

	try{
		this->sensor=new BMI160GenClass;

		BMI160.begin(BMI160GenClass::I2C_MODE,i2cAddress);

		this->gyroScaling=gyroScaling;
		this->accelScaling=accelScaling;
	}
	catch(exception& err){
		ESP_LOGW(BMI160APP_TAG,"{destructor}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(BMI160APP_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
	}
}


BMI160App::~BMI160App(){
	try{
		if(this->sensor!=NULL){
			delete this->sensor;
		}
	}
	catch(exception& err){
		ESP_LOGW(BMI160APP_TAG,"{destructor}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(BMI160APP_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
	}
}


bool BMI160App::measure(BMIMeasurement_t* measurement){

	try{
		int gxRaw,gyRaw,gzRaw,axRaw,ayRaw,azRaw;

		  //Gyro:
				//Take raw measurement
				this->sensor->readGyro(gxRaw, gyRaw, gzRaw);

				// convert the raw gyro data to degrees/second
				measurement->gyroscope_RPS[0] = convertRawGyro(gxRaw,this->gyroScaling);
				measurement->gyroscope_RPS[1] = convertRawGyro(gyRaw,this->gyroScaling);
				measurement->gyroscope_RPS[2] = convertRawGyro(gzRaw,this->gyroScaling);

		  //Accel:
				//Take raw measurement
				this->sensor->readAccelerometer(axRaw, ayRaw, azRaw);

				//Convert raw to G
				measurement->accelerometer_G[0] = convertRawAccel(axRaw,this->accelScaling);
				measurement->accelerometer_G[1] = convertRawAccel(ayRaw,this->accelScaling);
				measurement->accelerometer_G[2] = convertRawAccel(azRaw,this->accelScaling);

		return true;
	}
	catch(exception& err){
		ESP_LOGW(BMI160APP_TAG,"{destructor}, Exception: %s",err.what());
		return false;
	}
	catch(emu_err_t& err){
		ESP_LOGW(BMI160APP_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
		return false;
	}
}


void BMI160App::displayMeasurement(BMIMeasurement_t measurement){
	try{
		ESP_LOGI(BMI160APP_TAG,"Gyro: [x] %f ,[y] %f ,[z] %f",measurement.gyroscope_RPS[0],
																measurement.gyroscope_RPS[1],
																measurement.gyroscope_RPS[2]);

		ESP_LOGI(BMI160APP_TAG,"Acce: [x] %f ,[y] %f ,[z] %f",measurement.accelerometer_G[0],
																measurement.accelerometer_G[1],
																measurement.accelerometer_G[2]);
	}
	catch(exception& err){
		ESP_LOGW(BMI160APP_TAG,"{destructor}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(BMI160APP_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
	}
}


float BMI160App::convertRawGyro(int gRaw,gyroScaling_ForRange_t scaleRange) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767

  float g = (gRaw * (scaleRange*1.0)) / 32768.0;

  return g;
}


float BMI160App::convertRawAccel(int gRaw,accelScaling_ForRange_t scaleRange) {

  float g = (gRaw /(scaleRange*1.0));

  return g;
}
