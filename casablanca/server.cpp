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

bool Server::startListener(){
	std::cout << "Starting REST-route "<<serverUri << std::endl;
	this->listener = http_listener(utility::conversions::to_string_t(serverUri)); 

	listener.support(methods::POST, [this](http_request req)
	{

		try {
			req.extract_string(true).then([req,this](utility::string_t body)
			{
				size_t noOfParticipants=0;
				//wcout << body << endl; 

				json::value v = json::value::parse(body); 

				for (auto iter = v.as_object().cbegin(); iter != v.as_object().cend(); ++iter) {
					const string_t& key = iter->first;
					const json::value& value = iter->second;

					string jsonKey = utility::conversions::to_utf8string(key);
					vector<string> vs = vector<string>(); 
					//for(unsigned int i = 0; i < value.size() ; i
					string jsonValue= utility::conversions::to_utf8string(value.at(0).as_string());
					cout  << "jsonKey " << jsonKey<< "jsonvalue: "<< jsonValue <<endl<<endl;



					// IF looking for number of speakers
					if (jsonKey == "roomId"){

						if(this->cb2){

							noOfParticipants = this->cb2(jsonValue);
							string part_str= to_string(noOfParticipants);
							req.reply(status_codes::OK,  "{\" NoofParticipants \" : \"  "  + part_str + " \"}" , "application/json");
						}
						else throw;
					}
					// IF wanting to set speaker
					else
					{

						if(this->cb){
							this->cb(jsonKey, jsonValue);

						}
						req.reply(status_codes::OK,  "Success" , "text/plain");
					}

				}

			});


		}catch(std::exception ee){

			std::cout << "failed to start listener function from server.cpp"; 
			req.reply(status_codes::InternalError,  "Failed" , "text/plain");
		}

	});

	listener.open().wait();

	return true; 

}

bool Server::stopListener(){
	try{
		listener.close().wait();
		return true;
	}catch(std::exception ee){

		return false;  
	}

}

