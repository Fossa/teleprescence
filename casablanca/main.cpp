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
	const bool testServer = false;
	const bool testLayout = true;
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

	// testAuthUser("kaka", "1");
	if(testLayout){
		int arr[]={3,2,1};
		testLayoutChange("1", arr, 3);
	}
	if(testServer){
		uri_builder uri(U("http://localhost:2001/")); //20080
	
		http_listener listener(uri.to_uri());
	
		auto fileStream = make_shared<Concurrency::streams::ostream>();
	
	
	
		listener.support(methods::POST,[&](http_request req)
		{
	
			req.body().read_to_end(fileStream->streambuf()).then([&](size_t){
			fileStream -> print(cout);
	
	
				return fileStream->close();
	
			});
			 
	        // Write response body into the file.
	 
	
	
			cout << "Serving POST" << "obj:" <<  endl;
	
		//auto post = 
			//cout << "Received a POST of " << req.extract_json().get().serialize().c_str(); // << posted.is_string()<< endl;
			//auto post = 
			cout << "Received a POST of " << req.body(); // << posted.is_string()<< endl;
		
		//req.extract_json().then([=](web::json::value posted){
			//	cout << "Received a POST of " ;// << posted.is_string()<< endl;
			//});
		 
			//for (auto iter = posted.as_array().begin(); iter != posted.as_array.end(); ++iter) {
	
			//}
			//json:value b =  req.extract_json() 
			//cout << "type of a: " << typeid(v).name << '\n';
	
			
			req.reply(status_codes::OK, U( "<html><body><h1>It works!</h1>(Casablanca, that is a PUT Request.)</body></html>"), U("text/html"));
		});
	
		listener.open().wait();
		fgetc(stdin);
		listener.close().wait();
	}
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