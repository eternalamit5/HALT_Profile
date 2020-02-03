/*
 * lpg_wifi.cpp
 *
 *  Created on: Nov 25, 2019
 *      Author: karsh
 */

#include "lpg_wifi.h"
#include "esp_log.h"

static char LPG_WIFI_TAG[]={"LPG_WIFI "};


lpg_wifi* lpg_wifi::instance=NULL;



/**
 * @brief constructor
 * @details Inits the wifi attributes
 * 			Wifi connection is described by following attributes
 * 			#ssid: ssid of the access point
 * 			#password: password of the access point
 * 			#ip address: IP address recieved from the access point
 * 			#reconnectAttempt: Number of attempts to connect the access point
 * 			#connection status: connection status
 *
 *
 *
 * @see
 *
 */
lpg_wifi::lpg_wifi():
		ssid(CONFIG_ESP_WIFI_SSID),
		password(CONFIG_ESP_WIFI_PASSWORD),
		ip(""),
		reconnectAttempt(CONFIG_ESP_MAXIMUM_RETRY),
		connectionStatus(WIFI_DISCONNECTED){
	ESP_LOGI(LPG_WIFI_TAG,"{constructor},CALL");
}




/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
lpg_wifi::~lpg_wifi() {

	ESP_LOGI(LPG_WIFI_TAG,"{destructor},CALL");
	try{
		//Task 1: Disconnect the WIFI connection
		if(disconnect()==EMU_FAILURE){
			ESP_LOGW(LPG_WIFI_TAG,"Failed to disconnect, Force termination");
		}

		//Task 2: delete the instance
		delete this->instance;
	}
	catch(exception& err){
		ESP_LOGW(LPG_WIFI_TAG,"{destructor}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(LPG_WIFI_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
	}
}



/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
lpg_wifi* lpg_wifi::startService() {
	ESP_LOGI(LPG_WIFI_TAG,"{startService},CALL");

	try{
		//Task 1: Check instance already exists
		if(lpg_wifi::instance==NULL){

			//Task 2: Create new instance
			lpg_wifi::instance=new lpg_wifi();
			if(lpg_wifi::instance==NULL){
				throw EMU_ERR_OUT_OF_MEMORY;//Instance failed to be create
			}

			//Task 3: Wifi Init
			wifi_init_sta();
		}
		return lpg_wifi::instance;
	}
	catch(exception& err){
		ESP_LOGW(LPG_WIFI_TAG,"{startService}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(LPG_WIFI_TAG,"{startService}, Exception: %s",errorHandler::printError(err));
	}

	return NULL;
}



/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
lpg_wifi* lpg_wifi::getInstance() {
	return lpg_wifi::instance;
}



/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
emu_err_t lpg_wifi::disconnect() {

	ESP_LOGI(LPG_WIFI_TAG,"{disconnect},CALL");

	emu_err_t ret=EMU_SUCCESS;

	try
	{
		if(lpg_wifi::instance==NULL)
			throw EMU_ERR_NULL_INSTANCE;

		//stop wifi
		if(lpg_wifi::instance->connectionStatus==WIFI_CONNECTED){
			lpg_wifi::instance->reconnectAttempt=0; //Disable reconnection
			if(esp_wifi_stop()!=ESP_OK)
				throw EMU_ERR_WIFI_DISCONNECTION;
		}

		//Update ret
		ESP_LOGI(LPG_WIFI_TAG,"{disconnect},disconnected successfully");
		ret=EMU_SUCCESS;
	}
	catch(emu_err_t& err){
		ESP_LOGW(LPG_WIFI_TAG,"{disconnect}, Exception: %s",errorHandler::printError(err));
		ret=EMU_FAILURE;
	}
	catch(exception& err){
		ESP_LOGW(LPG_WIFI_TAG,"{disconnect}, Exception: %s",err.what());
		ret=EMU_FAILURE;
	}

	return ret;

}



emu_err_t lpg_wifi::reconnect() {

	ESP_LOGI(LPG_WIFI_TAG,"{reconnect},CALL");

	emu_err_t ret=EMU_SUCCESS;

	try
	{
		if(lpg_wifi::instance==NULL)
			throw EMU_ERR_NULL_INSTANCE;

		//stop wifi
		if(lpg_wifi::instance->connectionStatus==WIFI_DISCONNECTED){
			lpg_wifi::instance->reconnectAttempt=CONFIG_ESP_MAXIMUM_RETRY; //ensable reconnection
			if(esp_wifi_start()!=ESP_OK)
				throw EMU_ERR_WIFI_CONNECTION;
		}

		//Update ret
		ESP_LOGI(LPG_WIFI_TAG,"{reconnect},disconnected successfully");
		ret=EMU_SUCCESS;
	}
	catch(emu_err_t& err){
		ESP_LOGW(LPG_WIFI_TAG,"{reconnect}, Exception: %s",errorHandler::printError(err));
		ret=EMU_FAILURE;
	}
	catch(exception& err){
		ESP_LOGW(LPG_WIFI_TAG,"{reconnect}, Exception: %s",err.what());
		ret=EMU_FAILURE;
	}

	return ret;

}




/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
bool lpg_wifi::isConnectionStatus() const {
	return connectionStatus;
}


/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
void lpg_wifi::setConnectionStatus(wifi_connect_status_t connectionStatus) {
	this->connectionStatus = connectionStatus;
}


/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
const string& lpg_wifi::getIp() const {
	return ip;
}


/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
void lpg_wifi::setIp(const string &ip) {
	this->ip = ip;
}


/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
const string& lpg_wifi::getPassword() const {
	return password;
}





/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
const string& lpg_wifi::getSsid() const {
	return ssid;
}


/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
wifi_connect_status_t lpg_wifi::getConnectionStatus() const {
	return connectionStatus;
}


/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
uint8_t lpg_wifi::getReconnectAttempt() const {
	return reconnectAttempt;
}


/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
void lpg_wifi::setReconnectAttempt(uint8_t reconnectAttempt) {
	this->reconnectAttempt = reconnectAttempt;
}


/**
 * @brief
 * @details
 *
 *
 *
 * @see
 *
 */
static int s_retry_num = 0;
const int WIFI_CONNECTED_BIT = BIT0;
extern EventGroupHandle_t s_wifi_event_group;

void wifi_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
	ESP_LOGI(LPG_WIFI_TAG,"{wifi_event_handler},CALL");

	//get wifi instance
	lpg_wifi* wifi=lpg_wifi::getInstance();
	if(wifi==NULL){
		ESP_LOGW(LPG_WIFI_TAG,"{wifi_event_handler}, Exception: invalid handler");
		return;
	}

	//service the event
	if(event_base == WIFI_EVENT){
	    if (event_id == WIFI_EVENT_STA_START) {
	    	ESP_LOGI(LPG_WIFI_TAG,"{wifi_event_handler},start connection");
	        esp_wifi_connect();
	    }
	    else if(event_id == WIFI_EVENT_STA_DISCONNECTED) {
	    	ESP_LOGW(LPG_WIFI_TAG,"{wifi_event_handler},connection lost");

	    	wifi->setConnectionStatus(WIFI_DISCONNECTED);
	    	wifi->setIp("");//reset IP address

	        if (s_retry_num < wifi->getReconnectAttempt()) {
	            esp_wifi_connect();
	            xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
	            s_retry_num++;
	            ESP_LOGW(LPG_WIFI_TAG, "retry to connect to the AP");
	        }
	        ESP_LOGW(LPG_WIFI_TAG,"connect to the AP fail");

	    }
	}
    else if (event_base == IP_EVENT){
    	if(event_id == IP_EVENT_STA_GOT_IP){
            ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;

            wifi->setConnectionStatus(WIFI_CONNECTED);
            wifi->setIp(string(convertIPToString(event)));

            ESP_LOGI(LPG_WIFI_TAG, "got ip:%s",wifi->getIp().c_str());
            s_retry_num = 0;
            xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
            ESP_LOGI(LPG_WIFI_TAG,"{wifi_event_handler},connected successfully");
    	}
    }
}

