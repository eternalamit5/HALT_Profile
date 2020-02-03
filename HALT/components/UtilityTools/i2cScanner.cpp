/*
 * i2cScanner.cpp
 *
 *  Created on: Nov 29, 2019
 *      Author: karsh
 */
#include "../arduino-esp32/cores/esp32/Arduino.h"
#include "../arduino-esp32/libraries/Wire/src/Wire.h"



void I2CScannerTask(void* arg)
{
  byte error, address;
  int nDevices;

  Serial.println("Setting up for Scanning");
  Wire.begin();

  while(1){
	  Serial.println("Scanning...");
	  nDevices = 0;
	  for(address = 1; address < 127; address++ )
	  {
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();

		if (error == 0)
		{
		  Serial.print("I2C device found at address 0x");
		  if (address<16)
			Serial.print("0");
		  Serial.print(address,HEX);
		  Serial.println("  !");

		  nDevices++;
		}
		else if (error==4)
		{
		  Serial.print("Unknown error at address 0x");
		  if (address<16)
			Serial.print("0");
		  Serial.println(address,HEX);
		}
	  }
	  if (nDevices == 0)
		Serial.println("No I2C devices found\n");
	  else
		Serial.println("done\n");

	  vTaskDelay(1000);
  }

  vTaskDelete(NULL);


}


