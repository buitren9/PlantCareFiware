

//################# LIBRARIES ################   
var mraa = require("mraa");
var fiwareConnector = require("./fiWareConnector");
var mySensors = require("./mySensors");
var LCD  = require ('jsupm_i2clcd');
var numberOfIterationsPUmp = 0;
var groveSensor = require('jsupm_grove');





//################# VARIABLES ################   
var temperatureSensor = new mraa.Aio(0);
var humiditySensor = new mraa.Aio(1);
var relay = new groveSensor.GroveRelay(4);
var myLCD = new LCD.Jhd1313m1(6, 0x3E, 0x62);

var measures = {};


function startSensorWatch() {
    setInterval(function () {
		//read the data from the sensors
		var plantHumidity = mySensors.readHumiditySensor(1).toFixed(1);
		var celsius_temperature = mySensors.readTemperature(0,true).toFixed(1);
		
		console.log("plant humidity:"+plantHumidity +"%");
		console.log ("temperature:"+celsius_temperature + "Cº");
		console.log("Date "+new Date().toISOString().replace(/T/, ' ').replace(/\..+/, ''));
		
		checkMotor(plantHumidity);
		
		//show them in the LCD display
		myLCD.clear();
		myLCD.setCursor(0,0);
		myLCD.write("Humidity:"+plantHumidity+"%");
     	myLCD.setCursor(1,0);
		myLCD.write("Temperature:"+celsius_temperature);
		
		//light value 
		
		
		//upload to the Fi-Ware Platform
		measures["t"] = 28;
		measures["h"]= plantHumidity;
		measures["r"]= relay.isOn();
		fiwareConnector.postMeasures(measures);

    }, 60000);
}


startSensorWatch();

var isWater = true;
//check the humidity and put the relay ON/OFF
function checkMotor(humidity){


	if (humidity < 25 && numberOfIterationsPUmp < 2 && isWater){
		relay.on();
		numberOfIterationsPUmp++;
		myLCD.write("Pump: On");
	}else{
		relay.off();
		myLCD.write("Pump: Off");
		if (humidity < 30 && numberOfIterationsPUmp >2)
			isWater =false;
		else
			numberOfIterationsPUmp =0;
		if (humidity>25)
			isWater=true;
	}
}
