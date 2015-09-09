"use strict";

//################# LIBRARIES ################   
var request = require("request");

//################ FIWARE VARIABLES ################
var FIWARE_APIKEY = //YOUR API KEY ;
//Device´s name
var FIWARE_DEVICE = //YOUR DEVICE NAME ;
var FIWARE_SERVER = 'test.ttcloud.net';
var FIWARE_PORT = '8082';
var STATUS_CODE_OK = 200;


	
var postMeasures = function(measures){

var body=""; //FIWARE IoT Stack body message
var counter = Object.keys(measures).length; //number of sensors
	
for (var sensor in measures) { 
	body = body + sensor + '|' + measures[sensor];
	//add measures separator "#" to the body only when it is not the last measure
	if(counter>1){
		body = body +"#";
		counter--;
	}
}
    
console.log('--Sending measures to FIWARE IoT Stack '+body);



var options = { 
  method: 'POST',
  url: 'http://'+FIWARE_SERVER+':'+FIWARE_PORT+'/iot/d',
  qs: { i: FIWARE_DEVICE, k: FIWARE_APIKEY },
  body: body 
};

request(options, function (error, response, body) {
	if (error){
		console.log('--ERROR connectivity problems');	
	}else{
		if (response.statusCode = STATUS_CODE_OK){
			console.log('--Data uploaded to FIWARE IoT Stack');
		}else{
			console.log('--ERROR Status Code: '+response.statusCode);
		}
	}
});
	
};


module.exports = {
    postMeasures: postMeasures
};


