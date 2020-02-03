/*
 * errorHandler.h
 *
 *  Created on: Sep 21, 2019
 *  Author: karsh
 */

#ifndef MAIN_ERRORHANDLER_ERRORHANDLER_H_
#define MAIN_ERRORHANDLER_ERRORHANDLER_H_


#include "stddef.h"
#include "stdlib.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/FreeRTOS.h"
#include "esp_system.h"
#include "freertos/queue.h"
#include "string"

using namespace std;

/*****************************
	Callback typedef
*******************************/
/**
 * @brief
 * @details
 *
 *
 * @see
 *
 */
typedef void (contextCallback)(void*);


/*****************************
	enumeration: emu_err_t
*******************************/
/**
 * @brief
 * @details
 *
 *
 * @see
 *
 */
typedef enum{
	EMU_SUCCESS=0,
	EMU_FAILURE=-1,
	EMU_NO_MATCHING=-2,
	EMU_WARN_NO_CALLBACK=-3,	/**< WARNING NO CALLBACK ATTACHED*/
	EMU_ERR_INVALID_ARG=-4,		/**< ERR INVALID ARG*/
	EMU_ERR_ACCESS_DENIED=-5,	/**< ERROR ACCESS DENIED*/
	EMU_ERR_OUT_OF_MEMORY=-6,	/**< ERROR OUT OF MEMORY*/
	EMU_ERR_NULL=-7,			/**< ERROR NULL*/
	EMU_ERR_ILLEGAL_ACCESS=-8,
	EMU_ERR_EVT_HANDLER_REGISTRATION=-9,
	EMU_ERR_EVT_HANDLER_DEREGISTRATION=-10,
	EMU_ERR_EVT_TASK_CREATION=-11,
	EMU_ERR_EVT_LOOP_CREATION=-12,
	EMU_ERR_WIFI_DISCONNECTION=-13,
	EMU_ERR_WIFI_CONNECTION=-14,
	EMU_ERR_NULL_INSTANCE=-15,
	EMU_ERR_TEST_FAILED=-16,
	EMU_ERR_MQTT_CLIENT_PUB=-17,
	EMU_ERR_MQTT_CLIENT_SUB=-18,
	EMU_ERR_GENERIC=-19			/**< GENERIC ERROR*/
}emu_err_t;



/***************************************
	enumeration: emu_err_handler_code
***************************************/
/**
 * @brief
 * @details
 *
 *
 * @see
 *
 */
typedef enum{
	EMU_ERR_A_0000=0
}emu_err_handler_code;

/***************************************
	class: errorHandler
***************************************/
/**
 * @brief
 * @details
 *
 *
 * @see
 *
 */
class errorHandler{
		emu_err_handler_code latestErrorHandlerCode;
	public:
		errorHandler();
		virtual ~errorHandler();
		static const char* printError(emu_err_t err);
		void handleError(emu_err_handler_code code, void* contextData, contextCallback func);
		emu_err_handler_code getLatestErrorHandlerCode()const;
		virtual void displayAttributes();
};


#endif /* MAIN_ERRORHANDLER_ERRORHANDLER_H_ */
