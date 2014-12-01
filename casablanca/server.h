/*
* File:   server.h

* Purpose: Header file for Server part of NODEJS <-->TP REST API.
* Created: 2014-11-28.
*/

#ifndef SERVER_H
#define SERVER_H


#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::http::experimental::listener;


using namespace std;

// Declaring functions for Graph class
class Server
{
public:
	Server();
	~Server();

	Server(const http::uri& url);

	//void auth(json::value val);
	void layoutChange();
	void initRestListener();
	void readerJSON();
private:
	//void handle_get(http_request request);
	//void handle_put(http_request request);
	//void handle_post(http_request request);
	//void handle_delete(http_request request);
	//http_listener m_listener;       

};

#endif