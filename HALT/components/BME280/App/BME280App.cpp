/*
 * BME280App.cpp
 *
 *  Created on: Dec 1, 2019
 *      Author: karsh
 */
#include "BME280App.h"
#include "../components/ErrorHandler/errorHandler.h"

static char BME280_APP_TAG[]="BME280 APP: ";


BME280App::BME280App(float seaLevelPressure_HPA) {
	try{
		this->sensor=new Adafruit_BME280;
		this->sensor->begin();
		this->seaLevelPressure_HPA=seaLevelPressure_HPA;
	}
	catch(exception& err){
		ESP_LOGW(BME280_APP_TAG,"{destructor}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(BME280_APP_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
	}
}

BME280App::~BME280App() {
	try{
		if(this->sensor!=NULL){
			delete this->sensor;
		}
	}
	catch(exception& err){
		ESP_LOGW(BME280_APP_TAG,"{destructor}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(BME280_APP_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
	}
}

void BME280App::displayMeasurement(BMEMeasurement_t measurement){

	try{
		ESP_LOGI(BME280_APP_TAG,"Temperature = %f (C)",measurement.temperature);
		ESP_LOGI(BME280_APP_TAG,"Pressure = %f (hPa)",measurement.pressure);
		ESP_LOGI(BME280_APP_TAG,"Approx. Altitude = %f (m)",measurement.altitude);
		ESP_LOGI(BME280_APP_TAG,"Humidity = %f (%%)",measurement.humidity);
	}
	catch(exception& err){
		ESP_LOGW(BME280_APP_TAG,"{destructor}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(BME280_APP_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
	}
}

bool BME280App::measure(BMEMeasurement_t *measurement) {

	try{
		measurement->temperature=this->sensor->readTemperature();
		measurement->altitude=this->sensor->readAltitude(this->seaLevelPressure_HPA);
		measurement->pressure=this->sensor->readPressure()/100.0F;
		measurement->humidity=this->sensor->readHumidity();

		return true;
	}
	catch(exception& err){
		ESP_LOGW(BME280_APP_TAG,"{destructor}, Exception: %s",err.what());
		return false;
	}
	catch(emu_err_t& err){
		ESP_LOGW(BME280_APP_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
		return false;
	}

}
