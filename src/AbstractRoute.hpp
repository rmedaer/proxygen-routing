/*
    Copyright 2016 Raphael Medaer <rme@escaux.com>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
#ifndef ABSTRACTROUTE_HPP
#define ABSTRACTROUTE_HPP

#include <string>
#include <proxygen/lib/http/HTTPMessage.h>
#include <proxygen/httpserver/RequestHandler.h>
#include <r3/r3.hpp>

using std::string;
using proxygen::HTTPMethod;
using proxygen::RequestHandler;

/* Proxygen nested namespace proxygen::routing */
namespace proxygen {
namespace routing {

class AbstractRoute {
public:
	string path;
	HTTPMethod method;

	explicit AbstractRoute(string path, HTTPMethod method) : path(path), method(method) { }
	virtual ~AbstractRoute() { }


	virtual RequestHandler *handler(HTTPMessage* message) const = 0;

	const char *c_path()
	{
		return this->path.c_str();
	}

	int r3_method()
	{
		return AbstractRoute::r3_method_from_proxygen(this->method);
	}

	static int r3_method_from_proxygen(HTTPMethod method)
	{
		switch (method)
		{
			case HTTPMethod::GET: return METHOD_GET;
			case HTTPMethod::POST: return METHOD_POST;
			case HTTPMethod::OPTIONS: return METHOD_OPTIONS;
			case HTTPMethod::DELETE: return METHOD_DELETE;
			case HTTPMethod::HEAD: return METHOD_HEAD;
			case HTTPMethod::PUT: return METHOD_PUT;
			default:
				return 0;
		}
	}

};

}
}

#endif
