/*
 * lpg_driver.cpp
 *
 *  Created on: Nov 27, 2019
 *      Author: karsh
 */





#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "tcpip_adapter.h"


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

static char LPG_MQTT_DRIVER_TAG[]={"MQTT: "};

esp_mqtt_client_handle_t mqtt_app_start(const char* uri,int port,int keepAliveInterval,int lastWillQos,
		bool enableCleanSession,bool enableAutoReconnect,const char* lastWillTopic, const char* lastWillMsg)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = uri,
		//.port=port,
		.keepalive=keepAliveInterval,
		.disable_clean_session=!enableCleanSession,
        .disable_auto_reconnect=!enableAutoReconnect,
		.lwt_msg=lastWillMsg,
		.lwt_topic=lastWillTopic,
		.lwt_qos=lastWillQos,
    };


    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    if(client==NULL){
    	ESP_LOGW(LPG_MQTT_DRIVER_TAG,"{mqtt_app_start}, Init configuration failed");
    }else{
    	ESP_LOGI(LPG_MQTT_DRIVER_TAG,"{mqtt_app_start}, Init configuration, OK");
    }
    return client;
}
