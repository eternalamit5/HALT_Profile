/*
 * BME280App.h
 *
 *  Created on: Dec 1, 2019
 *      Author: karsh
 */

#ifndef COMPONENTS_BME280_TEST_BME280APP_H_
#define COMPONENTS_BME280_TEST_BME280APP_H_

#include "../components/BME280/BME280.h"

using namespace std;

typedef struct{
	float temperature;
	float pressure;
	float altitude;
	float humidity;
}BMEMeasurement_t;

class BME280App{
private:
	Adafruit_BME280* sensor;
	float seaLevelPressure_HPA;
public:
	/*
	 * Constructor
	 * @param seaLevelPressure_HPA: sea level presuure in HPA units
	 */
	BME280App(float seaLevelPressure_HPA);


	virtual ~BME280App();

	/*
	 * Take measurement from BME 280 (sensor measurement is taken here)
	 * @param measurement: BMEmeasurement contains
	 * 						> temperature,
	 * 						> pressure,
	 * 						> altitude,
	 * 						> humidity
	 */
	bool measure(BMEMeasurement_t* measurement);

	/*
	 * Display measurement stored measurement (measurement is not taken here)
	 * @param measurement: BMEmeasurement contains
	 * 						> temperature,
	 * 						> pressure,
	 * 						> altitude,
	 * 						> humidity
	 */
	void displayMeasurement(BMEMeasurement_t measurement);
};

#endif /* COMPONENTS_BME280_TEST_BME280APP_H_ */
