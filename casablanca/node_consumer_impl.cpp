#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/http_client.h>
//#include <cpprest/filestream.h>

#include "node_consumer_impl.h"

// using namespace utility;
// using namespace web::http;
// using namespace web::http::client;

using namespace web;
using namespace web::http;
using namespace web::http::client;

std::string int_array_to_string(int int_array[], int size_of_array);

void node_consumer_impl::auth_user(std::string cookie, std::string room, std::function<void(int, std::string)> cb){
// 	std::string url = "http://localhost:3005/";
// 	auto status_code = std::make_shared<web::http::status_code*const>();

// 	auto  stream = std::make_shared<std::ostringstream>();

// 	web::http::client::http_client client(U(url));
// 	web::uri_builder route_builder(U("/api/getme"));
// 	route_builder.append_query(U("cookie"), U(cookie));
// 	route_builder.append_query(U("room_id"), room);

// 	client.request(web::http::methods::GET, "", route_builder.to_string())
// 	.then([&](web::http::http_response response){
// 		return response.extract_json(stream);
// 	})
// 	.then([=] (json::value data)->task<void>{
// 		auto obj = v[L"user"];
// 		if(obj.has_field(L"user_id")){
// 			cb(1, obj[L"user_id"]);
// 		}else{
// 			cb(0, NULL);
// 		}
// 		return;
// 	}, cb(0, NULL));
}

void display_field_map_json(web::json::value  jvalue)
{
   if (!jvalue.is_null())
   {
      for (auto const & e : jvalue.as_object())
      {
         std::wcout 
         	/*<< typeid(e.first).name()*/ 
         	// << e.first/*.as_string()*/ 
         	<< L" : " 
         	/*<< typeid(e.second.as_string()).name()*/ 
         	// << e.second.as_string() 
         	<< std::endl;
      	// std::wcout << e.as_string() << std::endl;
      }
   }
}

void node_consumer_impl::layout_change(std::string room_id, std::vector< int > layout){
	// // std::string url = "http://localhost:3005/";
	// auto arr = json::value::array();
	// for(int i = 0; i<sz; ++i){
	// 	arr[i] = json::value(layout[i]);
	// }
	// // std::vector<std::pair<::utility::string_t, json::value>> obj;
	// // obj.push_back(std::pair<::utility::string_t,json::value>(L"layout", arr);
	// // auto jvalue = json::value::object(obj);
	// auto jvalue = json::value::parse("{ 'layout' : [] }");
	// jvalue[std::string("layout")] = arr;

	std::vector<web::json::value> arr = std::vector<web::json::value>();
	for(auto id : layout){
		arr.push_back(json::value(id));
	}
	web::json::value jvalue;
	jvalue["layout"] = web::json::value::array(arr);

	http_client client(U(this->url));
	client.request(methods::POST,(const ::utility::string_t) "/api/tp/"+room_id+"/layoutchange", (json::value const &)jvalue)
      .then([](http_response response)
      {
         if (response.status_code() == status_codes::OK)
         {
         		std::cout << "Successfully sent layoutchange."<<std::endl;
            return response.extract_json();
         }
         // return pplx::task_from_result(web::json::value());
         else{
         	std::cout << "Failed to send layoutchange." 
         		<< response.status_code() 
         		<< std::endl;
         }
         return pplx::task_from_result(web::json::value());
      })
      .then([](pplx::task<web::json::value> previousTask)
      {
         try
         {

            display_field_map_json(previousTask.get());
         }
         catch (http_exception const & e)
         {
            std::wcout << e.what() << std::endl;
         }
      })
      .wait();
	// http::status_code status_code;

	// auto  stream = std::make_shared<std::ostringstream>();



	// http_client client(U(url));
	// uri_builder builder(U("/api/tp/"+boost::lexical_cast<std::string>(room_id)+"/layoutchange"));
	// builder.append_query(U("layout"), U(int_array_to_string(layout));
	// client.request(methods::GET, "", builder.toString())
	// // Handle response headers
	// .then([=](http_response response){
	// 	status_code = response.status_code;
	// 	return response.body().read_to_end(stream);
	// })
	// // Close the stream
	// .then([=] (size_t){
	// 	stream->close();
	// 	cb(status_code(), stream.str);
	// 	return;
	// });	
}

// void make_request(http_client & client, method mtd,  json::value const & jvalue)
// {
//    client.request(mtd, jvalue)
//       .then([](http_response response)
//       {
//          if (response.status_code() == status_codes::OK)
//          {
//             return response.extract_json();
//          }
//          return pplx::task_from_result(json::value());
//       })
//       .then([](pplx::task<json::value> previousTask)
//       {
//          try
//          {
//             display_field_map_json(previousTask.get());
//          }
//          catch (http_exception const & e)
//          {
//             wcout << e.what() << endl;
//          }
//       })
//       .wait();
// }

// std::string int_array_to_string(int int_array[], int size_of_array) {
//   ostringstream oss("");
//   for (int temp = 0; temp < size_of_array; temp++)
//     oss << int_array[temp];
//   return oss.str()
// }