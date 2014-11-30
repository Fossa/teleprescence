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

using namespace web;
using namespace web::http;
using namespace web::http::client;


using namespace std;

// Declaring functions for Graph class
class Server
{
public:
	Server();
    ~Server();

	//TODO: add constructor with parameters

	void auth(json::value val);

	void setSpeaker();
};

#endif