#include "client.h"
#include "node_consumer_impl.h"
#include "server.h"
#include "cpprest/containerstream.h"
#include "cpprest/filestream.h"
#include "cpprest/http_client.h"
#include "cpprest/json.h"
#include "cpprest/producerconsumerstream.h"
#include <iostream>
#include <sstream>
 
#include <cpprest/http_listener.h>

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <memory>
#include <cassert>
#include "node_consumer_impl.h"
#include <vector>

using namespace pplx;
using namespace utility;
using namespace concurrency::streams;

using namespace web;
using namespace web::http::client;
using namespace web::http::experimental::listener;
using namespace web::http;
using namespace std;


void testAuthUser(std::string cookie, std::string room_id);
void testLayoutChange(std::string roomId, std::string layout[], size_t sz);
int main(int argc, char*argv[])
{
	bool runTestServer = false;	
	bool runTestAuth = true;
	bool runLayoutChange = true;

	if(runTestServer){
		
		// Server s("http://localhost:3010/api/tp");

		// Server t("http://localhost:3010/api/tp2");
		// s.set([](string r, vector<string> v){
		// 	cout <<r<< "::"<<  v.at(0)  <<endl;
		// });

		//  int i = t.set2([](string r, vector<string> v){
			  
		// });
		//  	 	cout << "::"<<  i  <<endl;

		// s.startListener();
		// t.startListener();

		// fgetc(stdin);
		// s.stopListener();
		// t.stopListener();
	}

	if(runTestAuth){
		// std::string kaka = "{"
		// 											"\"express\": {"
		// 												"\"sid\": \"s%3AvGJhHCwmjFiekH_89FSeGaHMZzqGNNon.uOrJjSr370lRXakwmIa3zersugTyvxFqxinAQHIqTOk\""
		// 											"}"
		// 										"}";
		std::string kaka = "s%3AvGJhHCwmjFiekH_89FSeGaHMZzqGNNon.uOrJjSr370lRXakwmIa3zersugTyvxFqxinAQHIqTOk";
		testAuthUser(kaka, "1");
	}

	if(runLayoutChange){
		std::string layout[] = {"1", "2", "3"};
		testLayoutChange("1", layout, 3);
	}
	return 0;
}

void testAuthUser(std::string cookie, std::string room_id){
	std::unique_ptr<Client> client_api(new node_consumer_impl("http://localhost:3005"));
	// client_api->auth_user(cookie, room_id, [=](std::string res){
	// 	if(!res.empty())
	// 		std::cout<<"TestAuthUser passed!"<<std::endl;
	// 	else
	// 		std::cout << "Failed!" << std::endl;
	// });
	std::cout << client_api->auth_user(cookie, room_id) <<std::endl;
}

void testLayoutChange(std::string roomId, std::string layout[], size_t sz){
	std::unique_ptr<Client> client_api(new node_consumer_impl("http://localhost:3005"));
	// client_api->layout_change(roomId, layout, sz);
	client_api->layout_change(roomId, std::vector<std::string>(layout, layout + sz));
}