/*
 * lpg_wifidriver.c
 *
 *  Created on: Nov 25, 2019
 *      Author: karsh
 */



#include "esp_log.h"
#include "lpg_wifidriver.h"


#define EXAMPLE_ESP_WIFI_SSID      CONFIG_ESP_WIFI_SSID
#define EXAMPLE_ESP_WIFI_PASS      CONFIG_ESP_WIFI_PASSWORD
#define EXAMPLE_ESP_MAXIMUM_RETRY  CONFIG_ESP_MAXIMUM_RETRY

EventGroupHandle_t s_wifi_event_group;

static const char *WIFI_STATION_TAG = "wifi station";


bool wifi_init_sta()
{
	bool ret=true;

	if(ret){
		//Task 1: Create event group for wifi
		s_wifi_event_group = xEventGroupCreate();

		//Task 2: Init TCPIP adapter
		tcpip_adapter_init();

		//Task 3: create default event loop for wifi
		if(esp_event_loop_create_default()!=ESP_OK){
			ret=false;
			ESP_LOGW(WIFI_STATION_TAG,"{wifi_init_sta}, fail to create event loop, Fail");
		}
	}

	if(ret){
		//Task 4: set init configuration
		wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
		if(esp_wifi_init(&cfg)!=ESP_OK){
			ret=false;
			ESP_LOGW(WIFI_STATION_TAG,"{wifi_init_sta}, fail to set config, Fail");
		}
	}

	if(ret){
		//Task 5: Set handler for any Event related to WIFI
		if(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, wifi_event_handler, NULL)!=ESP_OK){
			ret=false;
			ESP_LOGW(WIFI_STATION_TAG,"{wifi_init_sta}, fail to set handler for all events, Fail");
		}
	}

	if(ret){
		//Task 6: Set handler for receiving IP
		if(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, wifi_event_handler, NULL)!=ESP_OK){
			ret=false;
			ESP_LOGW(WIFI_STATION_TAG,"{wifi_init_sta}, fail to set handler for IP receive, Fail");
		}
	}


	if(ret){
		//Task 7: set mode
		if(esp_wifi_set_mode(WIFI_MODE_STA)!=ESP_OK){
			ret=false;
			ESP_LOGW(WIFI_STATION_TAG,"{wifi_init_sta}, fail to set mode wifi-station, Fail");
		}
	}

	if(ret){
		//Task 8: set mode configuration
		wifi_config_t wifi_config = {
			.sta = {
				.ssid = CONFIG_ESP_WIFI_SSID,
				.password = CONFIG_ESP_WIFI_PASSWORD
			},
		};
		if(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config)!=ESP_OK){
			ret=false;
			ESP_LOGW(WIFI_STATION_TAG,"{wifi_init_sta}, fail to set password and ssid, Fail");
		}
	}

	if(ret){
		//Task 9: wifi start
		if(esp_wifi_start()!=ESP_OK){
			ret=false;
			ESP_LOGW(WIFI_STATION_TAG,"{wifi_init_sta}, fail to start wifi, Fail");
		}
	}

    if(ret)
    	return true;
    else
    	return false;
}


char* convertIPToString(ip_event_got_ip_t* event){
	return ip4addr_ntoa(&event->ip_info.ip); // @suppress("Field cannot be resolved")
}


