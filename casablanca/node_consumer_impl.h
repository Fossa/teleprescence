#ifndef NODE_CONSUMER_IMPL_H
#define NODE_CONSUMER_IMPL_H

#include <string>

#include "client.h"

class node_consumer_impl: public Client{
private:
	std::string url;
public:
	node_consumer_impl(std::string url):url(url){}
	virtual void auth_user(std::string cookie, int room, std::function<void(int, std::string)> cb);
	// virtual void layout_change(int room_id, int layout[], size_t sz);
	virtual void layout_change( std::string room_id, std::vector< std::string > layout);
	virtual ~node_consumer_impl(){}
};

#endif