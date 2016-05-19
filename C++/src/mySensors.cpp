/*
 * mySensors.cpp
 *
 *  Created on: 11/9/2015
 *      Author: soportemovilforum
 */

#include "mySensors.h"
#include "mraa.hpp"
#include "grove.h"
#include "iostream"
const bool DEBUG = false;
using namespace std;

/***
 * Load temperature using groove sensor
 * @param pin : number of pin
 */
float MySensors::load_temperature(int pin){

	upm::GroveTemp* temp_sensor = new upm::GroveTemp(0);
	float temperature = temp_sensor->value();

	return temperature;
}

/***
 * Load the humidity
 * @param pin : number of input pin
 */
float MySensors::load_humidity(int pin){

	mraa::Aio* humiditySensor = new mraa::Aio(pin);
	float humidity = humiditySensor->read();
	humidity = (5*humidity/1024);
	humidity = (1/humidity)*100;

	return humidity;
}
