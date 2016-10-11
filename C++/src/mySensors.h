/*
 * mySensors.h
 *
 *  Created on: 11/9/2015
 *      Author: soportemovilforum
 */

class MySensors{
public:
	/**
	 * @param pin input pin
	 */
	static float load_temperature(int pin);
	static float load_humidity(int pin);

};
