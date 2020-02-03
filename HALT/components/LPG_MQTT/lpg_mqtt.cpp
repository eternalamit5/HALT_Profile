/*
 * lpg_mqtt.cpp
 *
 *  Created on: Nov 27, 2019
 *      Author: karsh
 */
#include "lpg_mqtt.h"
#include "lpg_driver.h"
#include "esp_log.h"

static char MQTT_TAG[]={"MQTT: "};


lpg_mqtt_client* lpg_mqtt_client::instance=NULL;


/**
 * @brief mqtt_event_handler is the event handler for mqtt client
 *
 * @details Following are tasks performed in this function
 * 			#Task 1: get mqtt instance and check for NULL
 * 			#Task 2: Update parameters based on the event received
 * 			#Task 3: Call application specific event CB
 *
 * @param event: event received by the mqtt-client
 * @return
 * 			ESP_OK: if success
 * 			ESP_FAIL: On failure or exception
 *
 * @see
 *
 */



/*
 *
 */
void mqtt_event_CB(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    //ESP_LOGI(MQTT_TAG, "Event dispatched from event loop base=%s, event_id=%d", base, event_id);

    //emu_err_t ret=EMU_SUCCESS;

    esp_mqtt_event_t* event=(esp_mqtt_event_t*)event_data;

    try{
		//Task 1: get mqtt instance and check for NULL
		lpg_mqtt_client* client=lpg_mqtt_client::getInstance();
		if(client==NULL){
			throw EMU_ERR_NULL_INSTANCE;
		}

		//Task 2: Update parameters based on the event recieved
		switch (event->event_id) {
			case MQTT_EVENT_CONNECTED:
				ESP_LOGI(MQTT_TAG, "{mqtt_event_handler}, {event:connected}");
				//Update the status
				client->setConnectionStatus(MQTT_CONNECTED);
				break;

			case MQTT_EVENT_DISCONNECTED:
				ESP_LOGI(MQTT_TAG, "{mqtt_event_handler}, {event:disconnected}");
				//update the status
				client->setConnectionStatus(MQTT_DISCONNECTED);
				break;

			case MQTT_EVENT_SUBSCRIBED:
				ESP_LOGI(MQTT_TAG, "{mqtt_event_handler}, {event:subscribed} msg_id=%d", event->msg_id);
				break;

			case MQTT_EVENT_UNSUBSCRIBED:
				ESP_LOGI(MQTT_TAG, "{mqtt_event_handler}, {event:un-subscribed} msg_id=%d", event->msg_id);
				break;

			case MQTT_EVENT_PUBLISHED:
				ESP_LOGI(MQTT_TAG, "{mqtt_event_handler}, {event:published} msg_id=%d", event->msg_id);
				break;

			case MQTT_EVENT_DATA:
				ESP_LOGI(MQTT_TAG, "{mqtt_event_handler}, {event:received data}: TOPIC=%.*s\r\n DATA=%.*s\r\n", event->topic_len,
						event->topic,event->data_len, event->data);
				break;

			case MQTT_EVENT_ERROR:
				ESP_LOGI(MQTT_TAG, "{mqtt_event_handler}, {event: error}");
				break;

			case MQTT_EVENT_BEFORE_CONNECT:
				ESP_LOGI(MQTT_TAG, "{mqtt_event_handler}, {event:before connect}");
				break;

			default:
				ESP_LOGI(MQTT_TAG, "{mqtt_event_handler}, {event:unknown}");
				break;
		}

		//Task 3: Call application specific event CB
		if(client->getAppEventCb()!=NULL){
			client->getAppEventCb()(event);
		}

		//Update ret
		//ret=EMU_SUCCESS;
    }
	catch(exception& err){
		ESP_LOGW(MQTT_TAG,"{addTopic}, Exception: %s",err.what());
		//ret=EMU_FAILURE;
	}
	catch(emu_err_t& err){
		ESP_LOGW(MQTT_TAG,"{addTopic}, Exception: %s",errorHandler::printError(err));
		//ret=EMU_FAILURE;
	}
}




/**
 * @brief constructor
 * @details sets configuration and starts mqtt service.
 * 			Following are tasks performed in this function
 * 			#Task 1: set MQTT configuration
 * 			#Task 2: set handle
 * 			#Task 3: add application event Handle
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
lpg_mqtt_client::lpg_mqtt_client(string uri, int port, int keepAliveInterval,mqtt_event_callback_t appEventCB,int lastWillQos,
		bool enableCleanSession,bool enableAutoReconnect,string lastWillTopic, string lastWillMsg):
				handle(NULL),
				connectionStatus(MQTT_DISCONNECTED),
				appEventCB(NULL)
{
	ESP_LOGI(MQTT_TAG,"{constructor},CALL");

	try{
		//Task 1: set MQTT configuration
		this->configuration.uri = uri.c_str();
		this->configuration.port=port;
		this->configuration.keepalive = keepAliveInterval;
		this->configuration.lwt_topic = lastWillTopic.c_str();
		this->configuration.lwt_msg = lastWillMsg.c_str();
		this->configuration.lwt_qos = lastWillQos;
		this->configuration.disable_clean_session =!enableCleanSession;
		this->configuration.disable_auto_reconnect = !enableAutoReconnect;

		//Task 2: set handle
		ESP_LOGI(MQTT_TAG,"{constructor},Set handle");
		//esp_mqtt_client_handle_t testHandle = esp_mqtt_client_init(&(this->configuration));
		//this->handle=testHandle;
		this->handle=mqtt_app_start(uri.c_str(),port,keepAliveInterval,
				this->configuration.lwt_qos,enableCleanSession,enableAutoReconnect,lastWillTopic.c_str(),lastWillMsg.c_str());


		//Task 3: add application event Handle
		ESP_LOGI(MQTT_TAG,"{constructor},Set event handler");
		if(this->appEventCB!=NULL){
			this->appEventCB=appEventCB;
		}

		ESP_LOGI(MQTT_TAG,"{constructor},All done");
	}
	catch(exception& err){
		ESP_LOGW(MQTT_TAG,"{constructor}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(MQTT_TAG,"{constructor}, Exception: %s",errorHandler::printError(err));
	}
}




/**
 * @brief destructor to mqtt-client
 * @details Following task are performed in this function
 * 			#Task 1: Stop mqtt client service
 * 			#Task 2: Destroy the mqtt client handle
 * 			#Task 3: delete the mqtt-client instance
 * @return None
 *
 * @see
 *
 */
lpg_mqtt_client::~lpg_mqtt_client()
{
	ESP_LOGI(MQTT_TAG,"{destructor},CALL");

	try{

		if(this->handle!=NULL){
			//Task 1: stop mqtt service for the mqtt client
			esp_mqtt_client_stop(this->handle);

			//Task 2: Destroy the mqtt client handle
			esp_mqtt_client_destroy(this->handle);
		}

		//Task 3: delete the mqtt-client instance
		if(this->instance!=NULL){
			delete this->instance;
		}
	}
	catch(exception& err){
		ESP_LOGW(MQTT_TAG,"{destructor}, Exception: %s",err.what());
	}
	catch(emu_err_t& err){
		ESP_LOGW(MQTT_TAG,"{destructor}, Exception: %s",errorHandler::printError(err));
	}
}






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
emu_err_t lpg_mqtt_client::startService(string uri, int port,int keepAliveTimeout, mqtt_event_callback_t appEventCB,int qos, bool enableCleanSession,
		bool enableAutoReconnect, string lastWillTopic, string lastWillMsg) {

	emu_err_t ret=EMU_SUCCESS;

	try{

		//Task 1: check if mqtt-client service instance exists
		if(lpg_mqtt_client::instance==NULL){

			//Task 2: If not, the create a new instance for mqtt-client
			lpg_mqtt_client::instance=new lpg_mqtt_client(uri,port,keepAliveTimeout,appEventCB,qos,enableCleanSession,
					enableAutoReconnect,lastWillTopic,lastWillMsg);
		}

		//Task 3: start mqtt-client service, if mqtt-service is not running.
		if(lpg_mqtt_client::instance->connectionStatus==MQTT_DISCONNECTED){
			esp_mqtt_client_register_event(lpg_mqtt_client::instance->handle, MQTT_EVENT_ERROR,
					mqtt_event_CB, (void*)lpg_mqtt_client::instance->handle);

			esp_mqtt_client_register_event(lpg_mqtt_client::instance->handle, MQTT_EVENT_CONNECTED,
					mqtt_event_CB, (void*)lpg_mqtt_client::instance->handle);

			esp_mqtt_client_register_event(lpg_mqtt_client::instance->handle, MQTT_EVENT_DISCONNECTED,
					mqtt_event_CB, (void*)lpg_mqtt_client::instance->handle);

			esp_mqtt_client_register_event(lpg_mqtt_client::instance->handle, MQTT_EVENT_SUBSCRIBED,
					mqtt_event_CB, (void*)lpg_mqtt_client::instance->handle);

			esp_mqtt_client_register_event(lpg_mqtt_client::instance->handle, MQTT_EVENT_UNSUBSCRIBED,
					mqtt_event_CB, (void*)lpg_mqtt_client::instance->handle);

			esp_mqtt_client_register_event(lpg_mqtt_client::instance->handle, MQTT_EVENT_PUBLISHED,
					mqtt_event_CB, (void*)lpg_mqtt_client::instance->handle);

			esp_mqtt_client_register_event(lpg_mqtt_client::instance->handle, MQTT_EVENT_DATA,
					mqtt_event_CB, (void*)lpg_mqtt_client::instance->handle);

			esp_mqtt_client_register_event(lpg_mqtt_client::instance->handle, MQTT_EVENT_BEFORE_CONNECT,
					mqtt_event_CB, (void*)lpg_mqtt_client::instance->handle);

			esp_mqtt_client_start(lpg_mqtt_client::instance->handle);
		}

		//Update ret
		ret=EMU_SUCCESS;
	}
	catch(exception& err){
		ESP_LOGW(MQTT_TAG,"{startService}, Exception: %s",err.what());
		ret=EMU_FAILURE;
	}
	catch(emu_err_t& err){
		ESP_LOGW(MQTT_TAG,"{startService}, Exception: %s",errorHandler::printError(err));
		ret=EMU_FAILURE;
	}

	return ret;
}


/*
 *
 */
emu_err_t lpg_mqtt_client::stopService() {

	emu_err_t ret=EMU_SUCCESS;
	try{
		//Task 1: stop mqtt client (does not destroy the handle)
		lpg_mqtt_client* client=lpg_mqtt_client::getInstance();
		if(client==NULL){
			throw EMU_ERR_NULL_INSTANCE;
		}
		esp_mqtt_client_stop(client->handle);
		client->setConnectionStatus(MQTT_DISCONNECTED);
	}
	catch(exception& err){
		ESP_LOGW(MQTT_TAG,"{subscribe}, Exception: %s",err.what());
		ret=EMU_FAILURE;
	}
	catch(emu_err_t& err){
		ESP_LOGW(MQTT_TAG,"{subscribe}, Exception: %s",errorHandler::printError(err));
		ret=EMU_FAILURE;
	}

	return ret;
}



/**
 * @brief gets instance of mqtt-client
 * @details
 * @return
 * 			pointer to the mqtt-client instance, if mqtt-client service not started or destroyed the returns NULL
 * @see
 *
 */
lpg_mqtt_client* lpg_mqtt_client::getInstance() {
	return lpg_mqtt_client::instance;
}

/**
 * @brief Publishes the mqtt message given the topic and message
 * @details Following are task performed in this function
 * 			#Task 1: get mqtt instance and check for NULL
 * 			#Task 2: publish the topic with msg
 *
 *
 * @param topic: mqtt topic that is to be published
 * @param message: mqtt topic that is to be published in the topic
 *
 * @return
 * 			EMU_SUCCESS: On success
 * 			EMU_FAILURE: On failure or exception
 * @see
 *
 */
emu_err_t lpg_mqtt_client::publish(string topic,string message) {

	emu_err_t ret=EMU_SUCCESS;

	ESP_LOGI(MQTT_TAG,"{publish},CALL");

	try{
		//Task 1: get mqtt instance and check for NULL
		lpg_mqtt_client* client=lpg_mqtt_client::getInstance();
		if(client==NULL){
			throw EMU_ERR_NULL_INSTANCE;
		}

		//Task 2: publish the topic with msg
		/* About Data len : (last but two argument in 'esp_mqtt_client_publish' set as 0 by me)
		 * 					If set to 0 then message length is automatically set based on the payload.
		 * 					If fixed length messages are required then this parameter should be non-zero.
		 *
		 * About retain flag:(last argument in 'esp_mqtt_client_publish' set as false by me)
		 *
		 * 		Retained messages is used to store the “Last Good Message” on a topic. Usually,
		 * 		if an MQTT client subscribes to a topic on a broker it will not recieve any of the messages
		 * 		published on it before subscription. If a client publishes a message to a topic with the
		 * 		retain flag set to True then the broker will save that message as the “Last Good Message” on that topic.
		 * 		This message will be received by any client who subscribes to that topic.
		 */
		if(esp_mqtt_client_publish(client->handle,topic.c_str(),message.c_str(),0,client->configuration.lwt_qos,false)==0){
			throw EMU_ERR_MQTT_CLIENT_PUB;
		}

	}
	catch(exception& err){
		ESP_LOGW(MQTT_TAG,"{publish}, Exception: %s",err.what());
		ret=EMU_FAILURE;
	}
	catch(emu_err_t& err){
		ESP_LOGW(MQTT_TAG,"{publish}, Exception: %s",errorHandler::printError(err));
		ret=EMU_FAILURE;
	}

	return ret;
}



/**
 * @brief Subscribes the mqtt message given the topic with mqtt-broker described by endpoint
 * @details Following are task performed in this function
 * 			#Task 1: get mqtt instance and check for NULL
 * 			#Task 2: subscribe the topic with msg
 *
 *
 * @param topic: mqtt topic that is to be subscribed *
 *
 * @return
 * 			EMU_SUCCESS: On success
 * 			EMU_FAILURE: On failure or exception
 * @see
 *
 */
emu_err_t lpg_mqtt_client::subscribe(string topic) {

	emu_err_t ret=EMU_SUCCESS;

	ESP_LOGI(MQTT_TAG,"{subscribe},CALL");

	try{

		//Task 1: get mqtt instance and check for NULL
		lpg_mqtt_client* client=lpg_mqtt_client::getInstance();
		if(client==NULL){
			throw EMU_ERR_NULL_INSTANCE;
		}

		//Task 2: subscribe the topic with msg
		if(esp_mqtt_client_subscribe(client->handle,topic.c_str(),client->configuration.lwt_qos)==-1){
			throw EMU_ERR_MQTT_CLIENT_SUB;
		}

	}
	catch(exception& err){
		ESP_LOGW(MQTT_TAG,"{subscribe}, Exception: %s",err.what());
		ret=EMU_FAILURE;
	}
	catch(emu_err_t& err){
		ESP_LOGW(MQTT_TAG,"{subscribe}, Exception: %s",errorHandler::printError(err));
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
const esp_mqtt_client_config_t& lpg_mqtt_client::getConfiguration() const {
	return configuration;
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
mqtt_connect_status_t lpg_mqtt_client::getConnectionStatus() const {
	return connectionStatus;
}


/**
 * @brief stop mqtt client service
 * @details This function stops mqtt client service, but does not destroy the handle
 *
 * @return
 * 			EMU_SUCCESS: on success
 * 			EMU_FAILURE: on failure or exception
 *
 *
 *
 * @see
 *
 */
void lpg_mqtt_client::setConnectionStatus(
		mqtt_connect_status_t connectionStatus) {
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
mqtt_event_callback_t lpg_mqtt_client::getAppEventCb() const {
	return appEventCB;
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
esp_mqtt_client_handle_t lpg_mqtt_client::getHandle() const {
	return handle;
}



