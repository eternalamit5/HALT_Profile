/*
 * lpg_mqtt.h
 *
 *  Created on: Nov 27, 2019
 *      Author: karsh
 */

#ifndef COMPONENTS_LPG_MQTT_LPG_MQTT_H_
#define COMPONENTS_LPG_MQTT_LPG_MQTT_H_

#include "mqtt_client.h"

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"

#include "list"
#include "../components/ErrorHandler/errorHandler.h"

using namespace std;

typedef enum{
	MQTT_CONNECTED=0,
	MQTT_DISCONNECTED=1
}mqtt_connect_status_t;

class lpg_mqtt_client{
private:
	static lpg_mqtt_client* instance;
	esp_mqtt_client_handle_t handle;
	esp_mqtt_client_config_t configuration;
	mqtt_connect_status_t connectionStatus;
	mqtt_event_callback_t appEventCB;
private:

	/**
	 * @brief constructor
	 * @details sets configuration and starts mqtt service.
	 * 			Following are tasks performed in this function
	 * 			#Task 1: set MQTT configuration
	 * 			#Task 2: set handle
	 * 			#Task 3: clear topic list
	 *
	 *
	 *
	 * @param uri:  universal resource indicator of endpoint (mqtt-broker) to which mqtt-client need to be connected.
	 * @param port: port number of endpoint (mqtt-broker) to which mqtt-client need to be connected.
	 * @param keepAliveInterval: time interval in seconds for sending keepAlive messages
	 * @param qos: quality of service (0,1,2)
	 * 					0: At most once
	 * 					1: At least once
	 * 					2: Exactly once
	 * @param enableCleanSession:
	 * 							True: 	When the clean session flag is set to true, the client does not want a persistent session.
	 * 									If the client disconnects for any reason, all information and messages that are queued from a
	 * 									previous persistent session are lost.
	 *
	 * 							False:  When the clean session flag is set to false, the broker creates a persistent session for the client.
	 * 									All information and messages are preserved until the next time that the client requests a clean session.
	 * 									If the clean session flag is set to false and the broker already has a session available for the client,
	 * 									it uses the existing session and delivers previously queued messages to the client.
	 * @param enableAutoReconnect:
	 * 							True:	Automatically tries to connect MQTT broker( endpoint) if connection is lost
	 * 							False:  Does not try to reconnect if connection is lost.
	 * @param lastWillTopic: last will topic is the last message topic sent to the mqtt broker (endpoint) before disconnection.
	 * @param lastWillMsg: last will message is the last message sent using last will topic to the mqtt broker (endpoint) before disconnection.
	 *
	 * @return None
	 * @see
	 *
	 */
	lpg_mqtt_client(string uri,int port,int keepAliveTimeout,mqtt_event_callback_t appEventCB,int qos=0,bool enableCleanSession=true,
			bool enableAutoReconnect=true,string lastWillTopic="", string lastWillMsg="");

	//Non copyable class
	lpg_mqtt_client(const lpg_mqtt_client& refObj)=delete;
	lpg_mqtt_client& operator=(const lpg_mqtt_client& refObj)=delete;
public:

	/**
	 * @brief startService
	 * @details sets configuration and starts mqtt service.
	 * 			Following are the tasks performed in this function
	 * 			#Task 1: check if mqtt-client service instance exists
	 * 			#Task 2: If not, the create a new instance for mqtt-client
	 * 			#Task 3: start mqtt-client service, if mqtt-service is not running.
	 *
	 * @param uri:  universal resource indicator of endpoint (mqtt-broker) to which mqtt-client need to be connected.
	 * @param port: port number of endpoint (mqtt-broker) to which mqtt-client need to be connected.
	 * @param keepAliveInterval: time interval in seconds for sending keepAlive messages
	 * @param qos: quality of service (0,1,2)
	 * 					0: At most once
	 * 					1: At least once
	 * 					2: Exactly once
	 * @param enableCleanSession:
	 * 							True: 	When the clean session flag is set to true, the client does not want a persistent session.
	 * 									If the client disconnects for any reason, all information and messages that are queued from a
	 * 									previous persistent session are lost.
	 *
	 * 							False:  When the clean session flag is set to false, the broker creates a persistent session for the client.
	 * 									All information and messages are preserved until the next time that the client requests a clean session.
	 * 									If the clean session flag is set to false and the broker already has a session available for the client,
	 * 									it uses the existing session and delivers previously queued messages to the client.
	 * @param enableAutoReconnect:
	 * 							True:	Automatically tries to connect MQTT broker( endpoint) if connection is lost
	 * 							False:  Does not try to reconnect if connection is lost.
	 * @param lastWillTopic: last will topic is the last message topic sent to the mqtt broker (endpoint) before disconnection.
	 * @param lastWillMsg: last will message is the last message sent using last will topic to the mqtt broker (endpoint) before disconnection.
	 *
	 * @return
	 * 			EMU_SUCCESS: On success
	 * 			EMU_FAILURE: On failure(Already running) or exception
	 * @see
	 *
	 */
	static emu_err_t startService(string uri,int port,int keepAliveTimeout,mqtt_event_callback_t appEventCB,int qos=0,bool enableCleanSession=true,
			bool enableAutoReconnect=true,string lastWillTopic="", string lastWillMsg="");


	static emu_err_t stopService();

	/**
	 * @brief gets instance of mqtt-client
	 * @details
	 * @return
	 * 			pointer to the mqtt-client instance, if mqtt-client service not started or destroyed the returns NULL
	 * @see
	 *
	 */
	static lpg_mqtt_client* getInstance();

	/**
	 * @brief destructor to mqtt-client
	 * @details Following task are performed in this function
	 * 			#Task 1: Stop mqtt client service
	 * 			#Task 2: delete the mqtt-client instance
	 * @return None
	 *
	 * @see
	 *
	 */
	virtual ~lpg_mqtt_client();

	/**
	 * @brief
	 * @details
	 *
	 *
	 * @see
	 *
	 */
	emu_err_t publish(string topic,string message);

	/**
	 * @brief
	 * @details
	 *
	 *
	 * @see
	 *
	 */
	emu_err_t subscribe(string topic);

	/**
	 * @brief
	 * @details
	 *
	 *
	 * @see
	 *
	 */
	const esp_mqtt_client_config_t& getConfiguration() const;

	/**
	 * @brief
	 * @details
	 *
	 *
	 * @see
	 *
	 */
	mqtt_connect_status_t getConnectionStatus() const;

	/**
	 * @brief
	 * @details
	 *
	 *
	 * @see
	 *
	 */
	void setConnectionStatus(mqtt_connect_status_t connectionStatus);

	/**
	 * @brief
	 * @details
	 *
	 *
	 * @see
	 *
	 */
	esp_mqtt_client_handle_t getHandle() const;

	/**
	 * @brief
	 * @details
	 *
	 *
	 * @see
	 *
	 */
	mqtt_event_callback_t getAppEventCb() const;
};
#endif /* COMPONENTS_LPG_MQTT_LPG_MQTT_H_ */
