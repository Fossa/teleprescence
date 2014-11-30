/*
 * File:   client.h
 
 * Purpose: Header file for Client part of NODEJS <-->TP REST API.
 * Created: 2014-11-28.
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace web;
using namespace web::http;
using namespace web::http::client;


using namespace std;

// Declaring functions for Graph class
class Client
{
public:
	Client();
    ~Client();

	//TODO: add constructor with parameters




};

#endif