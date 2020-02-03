/*
 * mqtt_test.cpp
 *
 *  Created on: Nov 27, 2019
 *      Author: karsh
 */

#include "../components/LPG_MQTT/lpg_mqtt.h"
#include "../components/LPG_WIFI/lpg_wifi.h"
extern "C"{
#include "../components/LPG_MQTT/lpg_driver.h"
}

static char MQTT_TEST_TAG[]={"MQTT Test: "};

void mqttTest(void* arg){
	ESP_LOGI(MQTT_TEST_TAG,"{mqttTest} Test started !!!");
	int count=0;
	const int MAX_COUNT=5;
	const int TICK_DELAY=500;
	try{


		//Start WIFI service
		lpg_wifi::startService();
		lpg_wifi* wifi=lpg_wifi::getInstance();
		ESP_LOGI(MQTT_TEST_TAG,"{mqttTest} Connecting to WIFI !!!");
		vTaskDelay(1000);



		if(wifi->getConnectionStatus()==WIFI_CONNECTED){
			ESP_LOGI(MQTT_TEST_TAG,"IP: %s,Connected, %d/%d",wifi->getIp().c_str(),count,MAX_COUNT);


			//start MQTT client service
			ESP_LOGI(MQTT_TEST_TAG,"{mqttTest} Start service !!!");
			count=0;
			lpg_mqtt_client::startService("mqtt://192.168.0.102:1883",1883,1000,NULL,1,true,true,"","");
			lpg_mqtt_client* mqttClient=lpg_mqtt_client::getInstance();
			do{
				if(mqttClient->getConnectionStatus()==MQTT_CONNECTED){
					ESP_LOGI(MQTT_TEST_TAG,"{mqttTest}, connected, %d/%d",count,MAX_COUNT);
				}else{
					ESP_LOGI(MQTT_TEST_TAG,"{mqttTest}, disconnected %d/%d",count,MAX_COUNT);
				}
				vTaskDelay(TICK_DELAY);
				count++;
			}while(count<=MAX_COUNT);




			//start MQTT client Publish
			ESP_LOGI(MQTT_TEST_TAG,"{mqttTest} Publish !!!");
			count=0;
			string pubstr="published: occurrence =>";
			do{
				if(mqttClient->getConnectionStatus()==MQTT_CONNECTED){
					pubstr+=" * ";
					mqttClient->publish("mqtt/test/pub",pubstr);
					ESP_LOGI(MQTT_TEST_TAG,"{mqttTest}, connected, %d/%d",count,MAX_COUNT);
				}else{
					ESP_LOGI(MQTT_TEST_TAG,"{mqttTest}, disconnected, %d/%d",count,MAX_COUNT);
				}
				vTaskDelay(TICK_DELAY);
				count++;
			}while(count<=MAX_COUNT);




			//start MQTT client Subscribe
			ESP_LOGI(MQTT_TEST_TAG,"{mqttTest} Subscribe !!!");
			count=0;
			mqttClient->subscribe("mqtt/test/sub");
			ESP_LOGI(MQTT_TEST_TAG,"{mqttTest}, waiting for data on topic {mqtt/test/sub} from broker");
			do{
				if(mqttClient->getConnectionStatus()==MQTT_CONNECTED){
					ESP_LOGI(MQTT_TEST_TAG,"{mqttTest}, connected, %d/%d",count,MAX_COUNT);
				}else{
					ESP_LOGI(MQTT_TEST_TAG,"{mqttTest}, disconnected, %d/%d",count,MAX_COUNT);
				}
				vTaskDelay(TICK_DELAY);
				count++;
			}while(count<=MAX_COUNT);




			//start MQTT client Stop
			ESP_LOGI(MQTT_TEST_TAG,"{mqttTest} Stop service !!!");
			count=0;
			mqttClient->stopService();
			do{
				if(mqttClient->getConnectionStatus()==MQTT_CONNECTED){
					ESP_LOGI(MQTT_TEST_TAG,"{mqttTest}, connected, %d/%d",count,MAX_COUNT);
				}else{
					ESP_LOGI(MQTT_TEST_TAG,"{mqttTest}, disconnected %d/%d",count,MAX_COUNT);
				}
				vTaskDelay(TICK_DELAY);
				count++;
			}while(count<=MAX_COUNT);



			ESP_LOGI(MQTT_TEST_TAG,"{mqttTest} Test ended !!!");


		}
		else{
			ESP_LOGI(MQTT_TEST_TAG,"IP: %s,disconnected %d/%d",wifi->getIp().c_str(),count,MAX_COUNT);
		}
	}
	catch(exception& err){
		ESP_LOGW(MQTT_TEST_TAG,"{mqttTest}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(MQTT_TEST_TAG,"{mqttTest}, Exception: %s",errorHandler::printError(err));
	}

	vTaskDelete(NULL);
}


void mqttTest2(void* arg){
	lpg_wifi::startService();
	//lpg_wifi* wifi=lpg_wifi::getInstance();
	ESP_LOGI(MQTT_TEST_TAG,"{mqttTest} Connecting to WIFI !!!");
	vTaskDelay(100);

	//mqtt_app_start2();
	while(1){
		vTaskDelay(1000);
		ESP_LOGI(MQTT_TEST_TAG,"{mqttTest} running !!!");
	}
}
