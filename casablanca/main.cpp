#include "client.h"
#include "server.h"


#include <cpprest/http_listener.h>
#include <cpprest/json.h>

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

int main(int argc, char*argv[])
{

	http_listener listener(L"http://localhost/restdemo");

	 
	 
}
