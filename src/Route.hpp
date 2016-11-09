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
#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <string>
#include <proxygen/lib/http/HTTPMessage.h>
#include <proxygen/httpserver/RequestHandler.h>

#include "AbstractRoute.hpp"

using std::string;
using proxygen::HTTPMethod;
using proxygen::RequestHandler;

/* Proxygen nested namespace proxygen::routing */
namespace proxygen {
namespace routing {

template<typename T>
class Route : public AbstractRoute {
public:
	Route(string path, HTTPMethod method) : AbstractRoute(path, method) { }

	virtual RequestHandler *handler(HTTPMessage* message) const
	{
		return new T(message);
	}

};

}
}

#endif
