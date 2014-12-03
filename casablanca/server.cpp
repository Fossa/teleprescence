/*
* File:   server.cpp
* Purpose: function file for Server part of NODEJS <-->TP REST API.
* Created: 2014-11-28.
*/
#include "server.h"
#include <iostream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>


using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;
using namespace utility;
using namespace std;


Server::Server() { 

	this->listener = http_listener(L"http://localhost:2001/path1");


}
Server::~Server() { }

void Server::startListener(){


	//http_listener listener(L"http://localhost:2001/path1");

	listener.support(methods::POST, [this](http_request req)
	{
		cout << "Serving POST" <<endl;
		req.extract_string(true).then([req,this](utility::string_t body)
		{
			wcout << body << endl; 

			json::value v = json::value::parse(body); 

			for (auto iter = v.as_object().cbegin(); iter != v.as_object().cend(); ++iter) {
				const string_t& key = iter->first;
				const json::value& value = iter->second;


				std::wcout << L"Key: " << key << L", Value: " << value.serialize() ;
				
				string roomId =   utility::conversions::to_utf8string(key);

				vector<string> vs = vector<string>(); 
			 
				
				for(unsigned int i = 0; i < value.size() ; i++){
				 
					string s = utility::conversions::to_utf8string(value.at(i).as_string());

					vs.push_back(s);

					cout <<"vector" << vs.at(0) << endl;

				}
				cout<< "calling cb"<<endl;
				if(this->cb){
					this->cb(roomId, vs);
				}

				//web::json::array h = value.as_array;
				//cout << ;
				//vector <int> vs = vector<int>();
				 
			}
			req.reply(status_codes::OK, U("Success"), U("text/html"));
		});
	});

	listener.open().wait();
	fgetc(stdin);
	listener.close().wait();
}
void Server::stopListener(){



}
//void Server::takeCustomers()
//{
//    utility::string_t str = U("http://localhost/CustomerAPI/api/customers");
//    RequestJSONValueAsync(str).wait();
//}




//void Server::auth (json::value val){
//}

void handleSpeaker(){
}
void initRestListener(){

}