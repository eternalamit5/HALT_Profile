/*
 * lpg_wifi.h
 *
 *  Created on: Nov 25, 2019
 *      Author: karsh
 */

#ifndef COMPONENTS_LPG_WIFI_LPG_WIFI_H_
#define COMPONENTS_LPG_WIFI_LPG_WIFI_H_



#include "string"
#include "../components/ErrorHandler/errorHandler.h"
extern "C"{
#include "lpg_wifidriver.h"
}

typedef enum{
	WIFI_CONNECTED=0,
	WIFI_DISCONNECTED=1
}wifi_connect_status_t;

using namespace std;

class lpg_wifi{
private:
	static lpg_wifi* instance;
	string ssid;
	string password;
	string ip;
	uint8_t reconnectAttempt;
	wifi_connect_status_t connectionStatus;

private:
	lpg_wifi();
	lpg_wifi(const lpg_wifi& refObj)=delete;
	lpg_wifi& operator=(const lpg_wifi& refObj)=delete;
public:
	static lpg_wifi* startService();
	static lpg_wifi* getInstance();
	virtual ~lpg_wifi();
	static emu_err_t disconnect();
	static emu_err_t reconnect();

	//getter and setter
	bool isConnectionStatus() const;
	void setConnectionStatus(wifi_connect_status_t connectionStatus);
	const string& getIp() const;
	void setIp(const string &ip);
	const string& getPassword() const;
	void setPassword(const string &password);
	const string& getSsid() const;
	void setSsid(const string &ssid);
	wifi_connect_status_t getConnectionStatus() const;
	uint8_t getReconnectAttempt() const;
	void setReconnectAttempt(uint8_t reconnectAttempt);
};

#endif /* COMPONENTS_LPG_WIFI_LPG_WIFI_H_ */
