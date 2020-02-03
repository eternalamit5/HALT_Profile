/*
 * errorHandler.cpp
 *
 *  Created on: Sep 21, 2019
 *  Author: karsh
 */
#include <errorHandler.h>
#include "esp_log.h"


static char ERR_HANDLER_TAG[]="Error handler: ";


/***************************************
	class: errorHandler
***************************************/

/**
 * @brief
 * @details
 *
 * @param[]
 *
 *
 * @return
 *
 * @see
 *
 */
errorHandler::errorHandler(){
	this->latestErrorHandlerCode=EMU_ERR_A_0000;
}


/**
 * @brief
 * @details
 *
 * @param[]
 *
 *
 * @return
 *
 * @see
 *
 */
errorHandler::~errorHandler(){

}


/**
 * @brief
 * @details
 *
 * @param[]
 *
 *
 * @return
 *
 * @see
 *
 */
void errorHandler::handleError(emu_err_handler_code code, void *contextData,
        contextCallback userContextCallbackFunc){

	switch(EMU_ERR_A_0000){
		case EMU_ERR_A_0000:
			//do nothing, error code for "No error"
			if(userContextCallbackFunc!=NULL){
				userContextCallbackFunc(contextData);
			}
		break;
		default:
			break;
	}
}



/**
 * @brief
 * @details
 *
 * @param[]
 *
 *
 * @return
 *
 * @see
 *
 */
emu_err_handler_code errorHandler::getLatestErrorHandlerCode() const{
	return this->latestErrorHandlerCode;
}

void errorHandler::displayAttributes(){
	ESP_LOGI(ERR_HANDLER_TAG,"---- Displaying attributes ------");

	ESP_LOGI(ERR_HANDLER_TAG,"---- done ------");
}


const char* errorHandler::printError(emu_err_t err){
	string str="";
	switch(err){
	case EMU_SUCCESS:
		str="#EMU_SUCCESS";
	break;
	case EMU_FAILURE:
		str="#EMU_FAILURE";
	break;
	case EMU_NO_MATCHING:
		str="#EMU_NO_MATCHING";
	break;
	case EMU_WARN_NO_CALLBACK:
		str="#EMU_WARN_NO_CALLBACK";
	break;
	case EMU_ERR_INVALID_ARG:
		str="#EMU_ERR_INVALID_ARG";
	break;
	case EMU_ERR_ACCESS_DENIED:
		str="#EMU_ERR_ACCESS_DENIED";
	break;
	case EMU_ERR_OUT_OF_MEMORY:
		str="#EMU_ERR_OUT_OF_MEMORY";
	break;
	case EMU_ERR_NULL:
		str="#EMU_ERR_NULL";
	break;
	case EMU_ERR_ILLEGAL_ACCESS:
		str="#EMU_ERR_ILLEGAL_ACCESS";
	break;
	case EMU_ERR_EVT_HANDLER_REGISTRATION:
		str="#EMU_ERR_EVT_HANDLER_REGISTRATION";
		break;
	case EMU_ERR_EVT_HANDLER_DEREGISTRATION:
		str="#EMU_ERR_EVT_HANDLER_DEREGISTRATION";
		break;
	case EMU_ERR_EVT_TASK_CREATION:
		str="#EMU_ERR_EVT_TASK_CREATION";
		break;
	case EMU_ERR_GENERIC:
		str="#EMU_ERR_GENERIC";
	break;
	default:
		str="UNKNOWN, FORGOT";
	}
	return str.c_str();
}

