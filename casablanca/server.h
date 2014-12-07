/*
* File:   server.h
* Purpose: Header file for Server part of NODEJS <-->TP REST API.
* Created: 2014-11-28.
*/

#ifndef SERVER_H
#define SERVER_H

#include <cpprest/http_listener.h>
#include <functional>
#include <vector>
#include <string>
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace web;
using namespace std;

// Declaring functions for Graph class
class Server
{
public:
	Server(string uri);
	~Server();

	std::function<void(string,string)> cb;
	std::function<size_t(string)> cb2;
	
	bool startListener();
	bool stopListener();
	void setSpeakerListenerCallback(std::function<void(string ,string)> cb){this->cb = cb;}
	void setParticipantsListenerCallback(std::function<size_t(string)> cb2){this->cb2 = cb2;}

private:
	http_listener listener;
	string serverUri; 
 

};

#endif