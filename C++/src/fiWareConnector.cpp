/*
 * fiWareConnector.cpp
 *
 *  Created on: 14/9/2015
 *      Author: soportemovilforum
 */

#include "fiWareConnector.h"
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <string.h>
#include <curl/curl.h>

using namespace std;

string FIWARE_APIKEY = "YOUR API KEY";
string FIWARE_DEVICE = "THE NAME OF YOUR DEVICE";
string FIWARE_SERVER = "test.ttcloud.net";
string FIWARE_PORT = "8082";
string url="http://"+FIWARE_SERVER+":"+FIWARE_PORT+"/iot/d?i="+FIWARE_DEVICE+"&k="+FIWARE_APIKEY;


void FiWareConnector::post_measures(Table measures){

	string body="";

	for (Table::const_iterator it = measures.begin(); it != measures.end(); ++it) {
			//add measures separator "#" to the body only when it is not the last measure
			if (body != "") {
				 body += "#";
			}
			//FIWARE IoT Stack body message
			body += it->first + "|" + it->second;
	}


		string url="http://"+FIWARE_SERVER+":"+FIWARE_PORT+"/iot/d?i="+FIWARE_DEVICE+"&k="+FIWARE_APIKEY;

		char bodyChar[body.length()];
		strcpy(bodyChar, body.c_str());

		char urlChar[url.length()];
		strcpy(urlChar, url.c_str());

		CURL *curl = curl_easy_init();

		//Send body to IoT Stack platform
		if(curl) {
			cout << "Sending -> " << body << endl;

			curl_easy_setopt(curl,CURLOPT_URL,urlChar);
			struct curl_slist *headers=NULL;
			headers = curl_slist_append(headers, "Content-Type:");
			curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, bodyChar);

			curl_easy_perform(curl);

		}
		curl_global_cleanup();
		// Clean body before the following iteration
		body="";






}


