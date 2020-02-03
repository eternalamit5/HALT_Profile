/*
 * testApp.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: karsh
 */
#include "../components/LPG_WIFI/lpg_wifi.h"
#include "../components/LPG_WIFI/Test/wifiTest.h"
#include "esp_log.h"

#define TEST

#ifdef TEST

static char TEST_TAG[]={"Test Tag: "};

void wifiTestTask(void* arg){

	//Configure
	const int MAX_COUNT=5;
	const int TICK_DELAY=250;


	int count=0;


	ESP_LOGI(TEST_TAG,"{testTask}: Test started !!!");

	try{
		ESP_LOGI(TEST_TAG,"{testTask}: CONNECTION SEQUEUENCE !!!");
		lpg_wifi::startService();
		lpg_wifi* wifi=lpg_wifi::getInstance();

		do{
			if(wifi->getConnectionStatus()==WIFI_CONNECTED){
				ESP_LOGI(TEST_TAG,"IP: %s,Connected, %d/%d",wifi->getIp().c_str(),count,MAX_COUNT);
			}else{
				ESP_LOGI(TEST_TAG,"IP: %s,disconnected %d/%d",wifi->getIp().c_str(),count,MAX_COUNT);
			}
			vTaskDelay(TICK_DELAY);
			count++;
		}while(count<=MAX_COUNT);


		ESP_LOGI(TEST_TAG,"{testTask}: DISCONNECTION SEQUEUENCE !!!");
		wifi->disconnect();
		count=0;
		do{
			if(wifi->getConnectionStatus()==WIFI_CONNECTED){
					ESP_LOGI(TEST_TAG,"IP: %s,Connected, %d/%d",wifi->getIp().c_str(),count,MAX_COUNT);
			}else{
					ESP_LOGI(TEST_TAG,"IP: %s,disconnected %d/%d",wifi->getIp().c_str(),count,MAX_COUNT);
			}
			vTaskDelay(TICK_DELAY);
			count++;
		}while(count<=MAX_COUNT);


		ESP_LOGI(TEST_TAG,"{testTask}: RECONNECT SEQUEUENCE !!!");
		wifi->reconnect();
		count=0;
		do{
			if(wifi->getConnectionStatus()==WIFI_CONNECTED){
					ESP_LOGI(TEST_TAG,"IP: %s,Connected, %d/%d",wifi->getIp().c_str(),count,MAX_COUNT);
			}else{
					ESP_LOGI(TEST_TAG,"IP: %s,disconnected %d/%d",wifi->getIp().c_str(),count,MAX_COUNT);
			}
			vTaskDelay(TICK_DELAY);
			count++;
		}while(count<=MAX_COUNT);

		ESP_LOGI(TEST_TAG,"{testTask}: Test ended !!!");

	}
	catch(emu_err_t& err){
		ESP_LOGW(TEST_TAG,"{testTask}, Exception: %s, test failed",errorHandler::printError(err));
	}
	catch(exception& err){
		ESP_LOGW(TEST_TAG,"{testTask}, Exception: %s, test failed",err.what());

	}

	vTaskDelete(NULL);

}
#endif
