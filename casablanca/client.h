/*
 * File:   client.h
 
 * Purpose: Header file for Client part of NODEJS <-->TP REST API.
 * Created: 2014-11-28.
 */

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <functional>
#include <vector>

// Declaring functions for Graph class
class Client
{
public:
	virtual void auth_user(std::string cookie, std::string room, std::function<void(int, std::string)> cb) = 0;
	// virtual void layout_change(int room_id, int layout[], size_t sz)=0;
	virtual void layout_change(std::string room_id, std::vector<int> layout)=0;
	virtual ~Client(){};
};

// Client::~Client(){}
#endif