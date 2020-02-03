/*
 * lpg_wifidriver.h
 *
 *  Created on: Nov 26, 2019
 *      Author: karsh
 */

#ifndef COMPONENTS_LPG_WIFI_LPG_WIFIDRIVER_H_
#define COMPONENTS_LPG_WIFI_LPG_WIFIDRIVER_H_


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "tcpip_adapter.h"
#include "esp_event_base.h"
#include "esp_err.h"
#include "stdbool.h"
#include "sdkconfig.h"
#include <string.h>
#include "lwip/err.h"
#include "lwip/sys.h"
#include "lwip/ip_addr.h"

extern EventGroupHandle_t s_wifi_event_group;


bool wifi_init_sta();
char * convertIPToString(ip_event_got_ip_t* event);
void wifi_event_handler(void* arg, esp_event_base_t event_base,
		int32_t event_id, void* event_data);

#endif /* COMPONENTS_LPG_WIFI_LPG_WIFIDRIVER_H_ */
