//################# LIBRARIES ################   
var mraa = require("mraa");

var DEBUG = false;

/** That function is used to read the Humidity of the ground */
var readHumidity =  function (pin){

	//put the pin into analogic pin 1
	var humiditySensor = new mraa.Aio(pin);
	var humidity = humiditySensor.read();
	humidity = (5/1024)*humidity;
	if (DEBUG)
		console.log("volt value: " + humidity+"V");
	//calculate the per cent of the humidity
	humidity = (1/humidity)*100;
	if (DEBUG)
		console.log("Humidity: " + humidity+"%");
	return humidity;

}
/** Code to use the ultrasonic sensor HCSR04return the distance in cm to the obstacle*/ 
var readDistanceUltrasonicHCSR04 = function(pinOutput,pinInput){
	var mySensorOutput = new mraa.Gpio(pinOutput);	
	var mySensorInput = new mraa.Gpio(pinInput);
	mySensorInput.mode(mraa.DIR_IN);
	mySensorOutput.mode(mraa.DIR_OUT);
	mySensorOutput.write(0);

	mySensorOutput.write(1);

	var date = new Date();
	var init = date.getMilliseconds();
	var exit = false;
	var end;
	mySensorInput.isr(1,function(init){
		var date = new Date();
		end = date.getMilliseconds();
		exit = true;
		var duration = end - init;
		if (DEBUG)
			console.log("Duration: " + duration);
		var distance = (0.017*duration);
		if (DEBUG)
			console.log("Distance: " + distance);
		return distance;

	});	
}

//function map 
function map(x,in_min, in_max, out_min, out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/** Code to use the ultrasonic sensor E18-D50NK return the distance in cm to the obstacle*/ 
var readUltrasonicSensorE18D50NK = function(pin){
	// Conect the sensor to de analog input 5
	var sensor = new mraa.Aio(pin);
	var distance = 0;
	if (DEBUG)
		console.log("Sensor: " + sensor.read());
	distance = map(sensor.read(),0,1023,3,80);
	if (DEBUG)
		console.log("Distance " + distance);
	return distance;
	
}

/** Read temperature Inputs->pin:number of the pin isCelsius:True for Celsius, false for fahrenheit */
var readTemperature = function(pin,isCelsius){
	var B = 3975;
	var temperatureSensor = new mraa.Aio(pin);
	var a = temperatureSensor.read();
  	var resistance = (1023 - a) * 10000 / a; //get the resistance of the sensor;
    var celsius_temperature = 1 / (Math.log(resistance / 10000) / B + 1 / 298.15) - 273.15;//convert to temperature via datasheet ;
	var fahrenheit_temperature = (celsius_temperature * (9 / 5)) + 32;
	if (isCelsius)
		return celsius_temperature;
	else
		return fahrenheit_temperature;
	
	
}

module.exports = {
	readHumiditySensor: readHumidity,
	readDistanceUltrasonicHCSR04 : readDistanceUltrasonicHCSR04,
	readDistanceUltrasonicE18D50NK : readUltrasonicSensorE18D50NK,
	readTemperature: readTemperature
};


