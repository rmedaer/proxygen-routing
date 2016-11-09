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
#include "Router.hpp"

namespace proxygen {
namespace routing {

Router::Router(std::vector<std::shared_ptr<AbstractRoute>> routes) :
	tree(routes.size()),
	routes(routes)
{
	char *errstr = NULL;

	LOG(INFO) << "Initializing request router ...";

	// Add each route in r3::tree
	for (auto it = routes.begin(); it != routes.end(); it++) {
		auto route = *it;
		LOG(INFO) << "Adding route: " << route->path;

		if (this->tree.insert_route(
			route->r3_method(),
			route->c_path(),
			(void *) route.get(),
			&errstr) == NULL)
		{
			LOG(ERROR) << "Failed to add route: " << route->path << "(" << errstr << ")";
			delete errstr;
		}
	}

	if (this->tree.compile(&errstr) != 0) {
		LOG(ERROR) << "Router compilation failed (" << errstr << ")";
		delete errstr;
		abort();
	}
}

void Router::onServerStart(folly::EventBase*) noexcept
{
}

void Router::onServerStop() noexcept {
}

RequestHandler* Router::onRequest(RequestHandler*, HTTPMessage* message) noexcept {
	auto path = message->getURL();
	MatchEntry entry(path.c_str());

	auto method = message->getMethod();
	if (method) {
		entry.set_request_method(Route<void>::r3_method_from_proxygen(method.get()));
	}

	r3::Route match = this->tree.match_route(entry);

	if (!match) {
		LOG(ERROR) << "Route not found: " << path;
		return new NotFoundHandler(message);
	}

	LOG(INFO) << "Route found: " << path;
	return ((AbstractRoute*) match.data())->handler(message);
}

}
}
