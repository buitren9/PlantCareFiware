
#!/usr/bin/env python

# Developed by @franbuitragoPa

import mraa
import time
import requests
import json

import pyupm_grove as grove
from mySensors import MySensors
from fiwareConnector import FiwareConnector


#Time between measures
MEASURES_PERIOD = 2

#Setup dictionary to include measures
measures = {}

connector = FiwareConnector()
sensors = MySensors()

temperature = None
humidity = None

relay = grove.GroveRelay(2)

#check the humidity to turn on/off the relay
def checkMotor(humidity,relay):

    relay.off()
    measures ["r"] = str("0")
    if(humidity<40):
        relay.on()
        measures ["r"] = str("1")


#read the measures and store it in a HashMap
def readMeasures():

    global humidity
    humidity = sensors.readHumidity(1)
    measures["h"] = str(humidity)

    global temperature
    temperature = sensors.readTemperature(0)
    measures ["t"] = str(temperature)
    checkMotor(humidity,relay)


while True:

    readMeasures()
    sensors.showValues(temperature,humidity)
    connector.postMeasures(measures)
    measures.clear()
    time.sleep(MEASURES_PERIOD)
