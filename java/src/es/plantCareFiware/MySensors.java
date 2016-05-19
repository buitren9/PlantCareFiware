package es.plantCareFiware;

import upm_grove.GroveTemp;
import mraa.Aio;


public class MySensors {
	
	/**
	 * Load temperature using groove sensor
	 * @param pin : number of pin 
	 * @return float value 
	 */
	public static float loadTemperature(int pin){
		
		GroveTemp tempSensor = new GroveTemp(pin);
		float temperature = tempSensor.value();
		
		return temperature;
		
	}
	
	/**
	 * Load the humidity based in the relative moisture of the ground
	 * @param pin number of input pin
	 * @return float value that represents % of humidity
	 */
	public static float  loadHumidity ( int pin){
		
		Aio humiditySensor = new Aio(pin);
		float humidity = humiditySensor.readFloat();
		humidity = (5*humidity/1024);
		humidity = (1/humidity)*100;
		
		return humidity;
	}

}
