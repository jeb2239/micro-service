//
//  Created by Ivan Mejia on 12/24/16.
//
// MIT License
//
// Copyright (c) 2016 ivmeroLabs.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#if 1
#include <iostream>

#include <usr_interrupt_handler.hpp>
#include <runtime_utils.hpp>

#include "microsvc_controller.hpp"

using namespace web;
using namespace cfx;

int main(int argc, const char * argv[]) {
    InterruptHandler::hookSIGINT();

    MicroserviceController server;
    server.setEndpoint("http://localhost:3456/restdemo");
    
    try {
        // wait for server initialization...
        server.accept().wait();
        std::cout << "Modern C++ Microservice now listening for requests at: " << server.endpoint() << '\n';
        
        InterruptHandler::waitForUserInterrupt();

        server.shutdown().wait();
    }
    catch(std::exception & e) {
        std::cerr << "somehitng wrong happen! :(" << '\n';
    }
    catch(...) {
        RuntimeUtils::printStackTrace();
    }

    return 0;
}
#endif

#if 0
#include <string>
#include <cpprest/http_listener.h>
#include <cpprest/json.h>
#include <pplx/pplxtasks.h>
 
using namespace web;
using namespace http;
using namespace http::experimental::listener;

#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
 
#define TRACE(msg)            cerr << msg
#define TRACE_ACTION(a, k, v) cerr << a << L" (" << k << L", " << v << L")\n"
 
map<utility::string_t, utility::string_t> dictionary;
 
/* handlers implementation */
void handle_get(http::http_request request)
{
cout<<"hello"<<endl;
    
   web::json::value answer;
 
   for(auto const & p : dictionary)
   {
      answer[p.first]=json::value(p.second);
   }
 
   request.reply(status_codes::OK, answer);
}

int main()
{
   http_listener listener(uri("http://localhost:3456/restdemo"));
 
   listener.support(http::methods::GET, handle_get);
//    listener.support(methods::POST, handle_post);
//    listener.support(methods::PUT, handle_put);
//    listener.support(methods::DEL, handle_del);
 
   try
   {
      listener
         .open()
         .then([&listener](){
             cout<<"Starting To Listen"<<endl;
         })
         .wait();
 
      while (true);
   }
   catch (exception const & e)
   {
      wcout << e.what() << endl;
   }
 
   return 0;
}
#endif