#!/usr/bin/python

import pyupm_i2clcd as lcd
import mraa
import math
from time import sleep


class MySensors:

    @staticmethod
    def readHumidity(pin):
        
        sensor = mraa.Aio(pin)
        humidity = sensor.read()
        humidity = (2.4/767)*humidity;
        humidity = (1/humidity)*100
        return humidity

    @staticmethod
    def readTemperature(pin):

        B = 3975
        sensor = mraa.Aio(pin)
        aValue = sensor.read()
        resistance = (1023 - aValue) * 10000 / aValue
        celsiusTmp = 1 / (math.log(resistance / 10000) / B + 1 / 298.15 ) - 273.15
        return celsiusTmp

    @staticmethod
    def showValues (temperature, humidity):

        # Initialize Jhd1313m1 at 0x3E (LCD_ADDRESS) and 0x62 (RGB_ADDRESS)
        myLcd = lcd.Jhd1313m1(0, 0x3E, 0x62)
        myLcd.setCursor(0,0)
        myLcd.write('Temperature ')
        myLcd.write(str(temperature))
        myLcd.setCursor(1,0)
        myLcd.write('Humidty ')
        myLcd.write(str(humidity))
        sleep(30)
