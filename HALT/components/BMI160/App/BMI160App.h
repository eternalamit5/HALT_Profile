/*
 * BMI160App.h
 *
 *  Created on: Dec 1, 2019
 *      Author: karsh
 */

#ifndef COMPONENTS_BMI160_APP_BMI160APP_H_
#define COMPONENTS_BMI160_APP_BMI160APP_H_

#include "../components/BMI160/BMI160Gen.h"
#include "../components/ErrorHandler/errorHandler.h"
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


typedef struct{
	float accelerometer_G[3];
	float gyroscope_RPS[3];
}BMIMeasurement_t;


class BMI160App{
private:
	BMI160GenClass* sensor;
	gyroScaling_ForRange_t gyroScaling;
	accelScaling_ForRange_t accelScaling;

	float convertRawGyro(int gRaw,gyroScaling_ForRange_t scaleRange);
	float convertRawAccel(int gRaw,accelScaling_ForRange_t scaleRange);

public:
	/*
	 * Constructor
	 * @param seaLevelPressure_HPA: sea level presuure in HPA units
	 */
	BMI160App(int i2cAddress,gyroScaling_ForRange_t gyroScaling,accelScaling_ForRange_t accelScaling);


	virtual ~BMI160App();

	/*
	 * Take measurement from BME 280 (sensor measurement is taken here)
	 * @param measurement: BMEmeasurement contains
	 * 						> temperature,
	 * 						> pressure,
	 * 						> altitude,
	 * 						> humidity
	 */
	bool measure(BMIMeasurement_t* measurement);

	/*
	 * Display measurement stored measurement (measurement is not taken here)
	 * @param measurement: BMEmeasurement contains
	 * 						> temperature,
	 * 						> pressure,
	 * 						> altitude,
	 * 						> humidity
	 */
	void displayMeasurement(BMIMeasurement_t measurement);
};




#endif /* COMPONENTS_BMI160_APP_BMI160APP_H_ */
