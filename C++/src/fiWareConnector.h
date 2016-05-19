#include <stdio.h>
#include <curl/curl.h>
#include "mraa.hpp"
#include <map>
#include <unistd.h>
#include <iostream>
#include <sstream>

using namespace std;

class FiWareConnector{

public:

	typedef map <string,string> Table;
	static void post_measures(Table measures);





};
