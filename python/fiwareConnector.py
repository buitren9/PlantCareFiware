#!/usr/bin/python
#This is an adaptation of the code: https://github.com/telefonicaid/fiware-edison/tree/develop/python
import requests
import json

#Time between measures
MEASURES_PERIOD = 2
FIWARE_SERVER = "YOUR_FIWARE_SERVER_ADDRESS"
FIWARE_PORT = "xxxx"
FIWARE_APIKEY = "xxxxxxx"
FIWARE_DEVICE = "myEdison"
class FiwareConnector:
################ FIWARE VARIABLES ################
    @staticmethod
    def postMeasures(measures):

        first = True
        payload = ""
        received_commands=[]
        #Parse chain of commands
        for key,value in measures.items():
            #Measures payload format is alias1|value1#alias2|value2#....
            #Add measures separator "#" to the request payload only when it is not the first measure
            if(first):
                first = False
            else:
                payload = payload + "#"

            payload = payload + key + "|" + value

        print('Sending measures to FIWARE IoT Stack '+payload)

        url = "http://" + FIWARE_SERVER+ ":" +FIWARE_PORT+ "/iot/d"
        querystring = {"i": FIWARE_DEVICE, "k": FIWARE_APIKEY, "getCmd":"1"}
        try:
            r = requests.post(url, data=payload, params=querystring)
            print "Response Status Code: "+str(r.status_code)
        except:
            print "Error chek your URL or Connection, please"
