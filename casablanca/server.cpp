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


Server::Server(string uri) { 

	 serverUri = uri;

}

Server::~Server() { }

void Server::startListener(){

	this->listener = http_listener(utility::conversions::to_string_t(serverUri)); 

	listener.support(methods::POST, [this](http_request req)
	{
		req.extract_string(true).then([req,this](utility::string_t body)
		{
			wcout << body << endl; 

			json::value v = json::value::parse(body); 

			for (auto iter = v.as_object().cbegin(); iter != v.as_object().cend(); ++iter) {
				const string_t& key = iter->first;
				const json::value& value = iter->second;

				string roomId =   utility::conversions::to_utf8string(key);

				vector<string> vs = vector<string>(); 


				for(unsigned int i = 0; i < value.size() ; i++){

					string s = utility::conversions::to_utf8string(value.at(i).as_string());

					vs.push_back(s);					 
				}
				 
				if(this->cb){
					this->cb(roomId, vs);
				}

			}
			req.reply(status_codes::OK, U("Success"), U("text/html"));
		});
	});

	listener.open().wait();
 	
}
void Server::stopListener(){

	listener.close().wait();
}
 
