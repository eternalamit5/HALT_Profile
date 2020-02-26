#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "../components/LPG_WIFI/Test/wifiTest.h"
#include "../components/LPG_MQTT/Test/mqttTest.h"
#include "../components/BME280/Test/BME280Test.h"
#include "../arduino-esp32/cores/esp32/Arduino.h"
#include "../components/UtilityTools/i2cScanner.h"
#include "../components/BMI160/Test/BMI160Test.h"
#include "../components/BMI160/Test/BMI160Test.h"
#include "../components/arduino-esp32/libraries/Wire/src/Wire.h"
#include "../components/MatildaApp/matildaApp.h"
#include "../components/servo/servoApp.h"
#include "../components/servo/PWMtest.h"
#include "../components/servo/PCA9685Test/PCA9685test.h"
#include "../components/servo/Oscillator/oscillator.h"

extern "C" {
void app_main(void) {
	//Initialize NVS
	esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	/*
	 * Initialize Arduino
	 */
	initArduino();

	/*Initialize Serial UART communication
	 Tx: GPIO 1
	 Rx: GPIO 3
	 Baud rate: 115200
	 */
	Serial.begin(115200);

	/*Initialize I2C communication
	 SDA: GPIO 23
	 SCL: GPIO 22
	 Clock: 400*1000 Hz
	 */
	Wire.begin(23,22,50*1000);

	//Wire.begin();

	//xTaskCreate(wifiTestTask,"testWIFITask",10000,NULL,1,NULL);
	//xTaskCreate(mqttTest,"testMQTTTask",10000,NULL,1,NULL);
	//xTaskCreate(bmeTask,"testbme280Task",10000,NULL,1,NULL);
	//xTaskCreate(I2CScannerTask,"i2cScannerTask",10000,NULL,1,NULL);
	//xTaskCreate(testTask,"testbmi160Task",10000,NULL,1,NULL);

	//xTaskCreate(matidaTask, "matildaMotionTestTask", 20000, NULL, 1, NULL);

	//xTaskCreate(matidaENVsensorTask, "matildaEnvironmentSensorTestTask", 20000, NULL, 1, NULL);
	//xTaskCreate(matidaMotionTask, "matildaMotionTestTask", 20000, NULL, 1, NULL);


	//xTaskCreate(ServoMotorTask,"testServoTask",10000,NULL,1,NULL);
	//printf("8 channel Servo test main!");
	//xTaskCreate(PWMtask,"testPWMtask",10000,NULL,1,NULL);
	xTaskCreate(PCA9685Task,"testPCA9685Task",10000,NULL,1,NULL);
	//xTaskCreate(OscillatorTask,"OscillatorTask",10000,NULL,1,NULL);


}
}
