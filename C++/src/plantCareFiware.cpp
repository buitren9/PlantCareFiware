/*
 *
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "grove.h"
#include "jhd1313m1.h"
#include <climits>
#include <iostream>
#include "mySensors.h"
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include "iostream"
#include "fiWareConnector.h"

/*
 * Grove Starter Kit example
 *
 * Demonstrate the usage of various component types using the UPM library.
 *
 *
 * Additional linker flags: -lupm-i2clcd -lupm-grove -lCurl
 */

/***
 * Convert a float into string
 */
std::string Convert (float number){
    std::ostringstream buff;
    buff<<number;
    return buff.str();
}
/***
 * check if the humidity is under 40% turn on the water pump with the relay
 */
void Check_pump_status(float humidity,upm::GroveRelay* relay){

	if (humidity>40){
		relay->off();
	}else{
		relay->on();
	}
}


/***
 * 	Prepare the data for the upload key-value
 */
FiWareConnector::Table prepareData(float humidity, float temperature, bool relayStatus){
	FiWareConnector::Table measures;
	measures["h"] = Convert(humidity);
	measures["t"] = Convert(temperature);
	measures["r"]=  (relayStatus == true) ? "true" : "false";
	return measures;


}
int main()
{
	// check that we are running on Galileo or Edison
	mraa_platform_t platform = mraa_get_platform_type();
	if ((platform != MRAA_INTEL_GALILEO_GEN1) &&
			(platform != MRAA_INTEL_GALILEO_GEN2) &&
			(platform != MRAA_INTEL_EDISON_FAB_C)) {
		std::cerr << "Unsupported platform, exiting" << std::endl;
		return MRAA_ERROR_INVALID_PLATFORM;
	}


	// temperature sensor connected to A0 (analog in)
	upm::GroveTemp* temp_sensor = new upm::GroveTemp(0);

	// LCD connected to the default I2C bus
	upm::Jhd1313m1* lcd = new upm::Jhd1313m1(0);
	std::stringstream row_1, row_2;
	upm::GroveRelay* relay = new upm::GroveRelay(4);

	// simple error checking
	if ((temp_sensor == NULL) || (lcd == NULL) || (relay == NULL)) {
		std::cerr << "Can't create all objects, exiting" << std::endl;
		return MRAA_ERROR_UNSPECIFIED;
	}

	// loop forever updating the temperature values every second
	for (;;) {

		float temperature = MySensors::load_temperature(0);
		float humidity = MySensors::load_humidity(1);

		row_1.str(std::string());
		row_2.str(std::string());
		row_2 << "Temperature " << std::fixed << std::setprecision(2) <<temperature << "Cº";
		row_1 << "Humidity "<< std::fixed << std::setprecision(0) << humidity << "\%";

		//write in the LCD
		lcd->setCursor(0,0);
		lcd->write(row_1.str());
		lcd->setCursor(1,0);
		lcd->write(row_2.str());


		//clear LCD
		row_1.str(std::string());
		row_2.str(std::string());

		Check_pump_status(humidity,relay);

		//Prepare data to upload to Fi-Ware
		FiWareConnector::Table measures = prepareData(humidity,temperature,relay->isOn());
		//Upload data to Fi-Ware
		FiWareConnector::post_measures(measures);

		sleep(20);

	}

	return MRAA_SUCCESS;
}



