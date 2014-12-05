#include "client.h"
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
#include "docopt.h"
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

// static const char USAGE[] = 
// R"(Testing the node interface for telepresence.
// 	Usage:
// 	main --auth
// )";

void testAuthUser(std::string cookie, std::string room_id);
void testLayoutChange(std::string roomId, int layout[], size_t sz);
int main(int argc, char*argv[])
{
	Server s("http://localhost:3010/api/tp");

	Server t("http://localhost:3010/api/tp2");
	s.set([](string r, vector<string> v){
		cout <<r<< "::"<<  v.at(0)  <<endl;
	});

	 int i = t.set2([](string r, vector<string> v){
		  
	});
	 	 	cout << "::"<<  i  <<endl;

	s.startListener();
	t.startListener();

	fgetc(stdin);
	s.stopListener();
	t.stopListener();
	
	
	
	//Listener function
	//	Server s; 
	//s.set([](string r, vector<string> v){
	//	cout << "success"<<endl;
	//});
	//s.startListener();
	
	// std::map<std::string, docopt::value> args
	// 	= docopt::docopt(USAGE,
	// 										{argv + 1, argv + argc},
	// 										true,
	// 										"v.0.0.1"
	// 		);
	// std::map<std::string, docopt::value>::iterator opt_it;
	// if((opt_it = args.find("--auth")) != args.end()){
	// 	std::cout << opt_it->first << " " << opt_it->second << std::endl;
	// 	testAuthUser(opt_it->second.asString(), 1);
	// }


	
	return 0;
}


//
//#include <cpprest/http_listener.h>
//#include <cpprest/json.h>
//
//#include <iostream>
//#include <iostream>
//#include <map>
//#include <set>
//#include <string>
//
//using namespace web;
//using namespace web::http;
//using namespace web::http::experimental::listener;
//
//
//using namespace std;
//
//int main(int argc, char*argv[])
//{
//
//	http_listener listener(L"http://thewire.deckmar.net:3000/api/tp/rooms/:room_id");
//	getchar();
//	return 0;
//
//}
void testAuthUser(std::string cookie, std::string room_id){
	std::unique_ptr<Client> client_api(new node_consumer_impl("http://localhost:3005"));
	client_api->auth_user(cookie, room_id, [=](int status, std::string res){
		assert(status == 200);
		std::cout<<"TestAuthUser passed!"<<std::endl;
	});
}

void testLayoutChange(std::string roomId, int layout[], size_t sz){
	std::unique_ptr<Client> client_api(new node_consumer_impl("http://localhost:3005"));
	// client_api->layout_change(roomId, layout, sz);
	client_api->layout_change(roomId, std::vector<int>(layout, layout + sz));
}