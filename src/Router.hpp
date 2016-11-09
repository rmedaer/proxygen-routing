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
#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <memory>
#include <vector>
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>
#include <proxygen/lib/http/HTTPMessage.h>
#include <r3/r3.hpp>

#include "Route.hpp"
#include "NotFoundHandler.hpp"

using std::shared_ptr;
using std::vector;
using proxygen::RequestHandler;
using proxygen::RequestHandlerFactory;
using proxygen::HTTPMessage;
using r3::MatchEntry;
using r3::Tree;

/* Proxygen nested namespace proxygen::routing */
namespace proxygen {
namespace routing {

/*
 *
 */
class Router : public RequestHandlerFactory {
	Tree tree;
	vector<shared_ptr<AbstractRoute>> routes;

public:
	Router(vector<shared_ptr<AbstractRoute>> routes);
	void onServerStart(folly::EventBase*) noexcept override;
	void onServerStop() noexcept override;
	RequestHandler* onRequest(RequestHandler* handler, HTTPMessage* message) noexcept override;
};

}
}

#endif // ROUTER_HPP
