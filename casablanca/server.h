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

	std::function<void(string,std::vector<string>)> cb;
	void startListener();
	void stopListener();

	

	void set(std::function<void(string ,vector<string>)> cb){this->cb = cb;}
	 
private:
	http_listener listener;
	string_t str; 
};

#endif