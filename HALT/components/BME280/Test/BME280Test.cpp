/*
 * BME280Test.cpp
 *
 *  Created on: Nov 29, 2019
 *      Author: karsh
 */
#include "stdlib.h"
#include "../components/BME280/BME280.h"
#include "../components/arduino-esp32/libraries/Wire/src/Wire.h"
#include "../components/Adafruit_Common_Sensor/Adafruit_Sensor.h"

using namespace std;

static char BME280_TAG[]="BME280: ";

#define SEALEVELPRESSURE_HPA (1013.25)

void takeMeasurement(Adafruit_BME280& bme){
    ESP_LOGI(BME280_TAG,"Temperature = %f (C)",bme.readTemperature());
    ESP_LOGI(BME280_TAG,"Pressure = %f (hPa)",bme.readPressure() / 100.0F);
    ESP_LOGI(BME280_TAG,"Approx. Altitude = %f (m)",bme.readAltitude(SEALEVELPRESSURE_HPA));
    ESP_LOGI(BME280_TAG,"Humidity = %f (%%)",bme.readHumidity());
}

void bmeTask(void* arg) {

	try{
		//Create BME instance
		Adafruit_BME280* bmeInstance=new Adafruit_BME280;
		Adafruit_BME280& bme=*bmeInstance;

		//Init bme in I2C mode
		if (!bme.begin()) {
			ESP_LOGW(BME280_TAG,"{BME280_I2C_setup}, begin failed, FAIL");
			vTaskDelete(NULL);
		}
		vTaskDelay(1000);

		while(1){
			takeMeasurement(bme);
			vTaskDelay(100);
		}
	}
	catch(exception& err){
		ESP_LOGW(BME280_TAG,"{addTopic}, Exception: %s",err.what());
		//ret=EMU_FAILURE;
	}

	vTaskDelete(NULL);

}
