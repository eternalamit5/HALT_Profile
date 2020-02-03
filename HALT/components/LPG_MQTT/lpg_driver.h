/*
 * lpg_driver.h
 *
 *  Created on: Nov 27, 2019
 *      Author: karsh
 */

#ifndef COMPONENTS_LPG_MQTT_LPG_DRIVER_H_
#define COMPONENTS_LPG_MQTT_LPG_DRIVER_H_

extern "C"{
esp_mqtt_client_handle_t mqtt_app_start(const char* uri,int port,int keepAliveInterval,int lastWillQos,
		bool enableCleanSession,bool enableAutoReconnect,const char* lastWillTopic, const char* lastWillMsg);
}

#endif /* COMPONENTS_LPG_MQTT_LPG_DRIVER_H_ */
