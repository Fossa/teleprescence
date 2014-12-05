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

std::string node_consumer_impl::auth_user(std::string cookie, std::string room_id){
   web::json::value j_cookie;
   web::json::value jvalue;
   try{
      const ::utility::string_t route = "/api/tp/"+room_id+"/auth";
      try{
         j_cookie = web::json::value::parse(cookie);
         jvalue["cookie"] = j_cookie;
         jvalue["room"] = web::json::value::string(room_id);
      }catch(web::json::json_exception e){
         std::cout << "Malformed json." << std::endl;
         return "";
      }
      http_client client(U(this->url));
      pplx::task<http_response> resp = client.request(
            methods::POST,
            route, 
            (json::value const &)jvalue
         );
      http_response response = resp.get();
      if (response.status_code() == status_codes::OK)
      {
            std::cout << "Successfully sent auth."<<std::endl;
            web::json::value res = response.extract_json().get();
            //display_field_map_json(previousTask.get());
            if(res.has_field("username")){
               std::string usr_name = utility::conversions::to_utf8string(res["username"].as_string());
               return usr_name;
            }else{
               std::cout<<"Username missing from response!"<<std::endl;
            }
      }
      else{
         std::cout << "Failed to send auth." 
            << response.status_code() 
            << std::endl;
      }
      return "";
   }
   catch(std::exception e){
      std::cout << "Error in auth_user." << std::endl;
      throw; 
   }
}

void node_consumer_impl::auth_user(std::string cookie, std::string room_id, std::function<void(std::string)> cb){
   try{
      web::json::value j_cookie = web::json::value::parse(cookie);
      web::json::value jvalue;
      //jvalue["cookie"] = web::json::value::string(cookie);
      jvalue["cookie"] = j_cookie;
      jvalue["room"] = web::json::value::string(room_id);

      http_client client(U(this->url));
      client.request(methods::POST,(const ::utility::string_t) "/api/tp/"+room_id+"/auth", (json::value const &)jvalue)
         .then([cb](http_response response)
         {
            if (response.status_code() == status_codes::OK)
            {
                  std::cout << "Successfully sent auth."<<std::endl;
               return response.extract_json();
            }
            else{
               std::cout << "Failed to send auth." 
                  << response.status_code() 
                  << std::endl;
            }
            return pplx::task_from_result(web::json::value());
         })
         .then([cb](pplx::task<web::json::value> previousTask)
         {
            try
            {
               web::json::value res = previousTask.get();
               //display_field_map_json(previousTask.get());
               if(res.has_field("username")){
                  std::string usr_name = utility::conversions::to_utf8string(res["username"].as_string());
                  cb(usr_name);
               }else{
                  std::cout<<"Username missing from response!"<<std::endl;
               }
            }
            catch (http_exception const & e)
            {
               std::wcout << e.what() << std::endl;
            }
         })
         .wait();
   }
   catch(std::exception e){
      std::cout << "Error in auth_user." << std::endl;
      cb("");
      throw; 
   }
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

void node_consumer_impl::layout_change(std::string room_id, std::vector< std::string > layout){
   try{
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
   }catch(std::exception e){
      std::cout << "Exception in consumer layout_change" << std::endl;
      throw;
   }
}