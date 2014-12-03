#include "client.h"
#include "server.h"
#include "cpprest/containerstream.h"
#include "cpprest/filestream.h"
#include "cpprest/http_client.h"
#include "cpprest/json.h"
#include "cpprest/producerconsumerstream.h"
#include <iostream>
#include <sstream>
#include <cpprest/http_listener.h>

using namespace ::pplx;
using namespace utility;
using namespace concurrency::streams;
using namespace web;
using namespace web::http::client;
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web::json;
using namespace std;

int main(int argc, char*argv[]){

	Server s; 
	s.set([](string r, vector<string> v){
		cout << "success"<<endl;
	});
	s.startListener();
}