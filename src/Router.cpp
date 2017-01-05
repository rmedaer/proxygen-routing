/*
    Copyright 2016 Raphael Medaer <rme@escaux.com>

    This file is part of proxygen-routing (libproxygenrouting).

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

#include "Router.h"

namespace proxygen {
namespace routing {

Router::Router(
    std::vector<std::shared_ptr<AbstractRoute>> routes)
    : tree(routes.size()), settings()
{
    this->addRoute(routes);
    this->compile();
}

Router::Router(
    vector<shared_ptr<AbstractRoute>> routes,
    map<string, string> settings)
    : tree(routes.size()), settings(settings)
{
    this->addRoute(routes);
    this->compile();
}

void
Router::addRoute(vector<shared_ptr<AbstractRoute>> routes)
{
    // Add each route to r3::tree
    for (auto route = routes.begin(); route != routes.end(); ++route)
    {
        this->addRoute(*route);    
    }
}

void
Router::addRoute(shared_ptr<AbstractRoute> route)
{
    char *errstr = NULL;

    LOG(INFO) << "Adding route \"" << route->path << "\"";

    if (this->tree.insert_route(
        route->r3_method(),
        route->c_path(),
        (void *) route.get(),
        &errstr) == NULL)
    {
        LOG(ERROR) << "Failed to add route \""
                   << route->path
                   << "\": "
                   << errstr;
        delete errstr;
    }
}

void
Router::compile()
{
    char *errstr = NULL;;;;
    if (this->tree.compile(&errstr) != 0)
    {
        LOG(ERROR) << "Compilation failed: " << errstr;
        delete errstr;
        abort();
    }
}

void
Router::onServerStart(
    folly::EventBase*) noexcept
{
    /* XXX Should we compile at server start ? */
}

void
Router::onServerStop() noexcept
{
}

RequestHandler*
Router::onRequest(
    RequestHandler* handler,
    HTTPMessage* message) noexcept
{
    // Handling incoming request
    auto path = message->getURL();
    r3::MatchEntry entry(path.c_str());

    auto method = message->getMethod();
    if (!method)
    {
        LOG(ERROR) << "Method not found in HTTPMessage";
        // INTERNAL SERVER ERROR
        return NULL;
    }

    entry.set_request_method(AbstractRoute::proxygen_to_r3_method(method.get()));

    r3::Route match = this->tree.match_route(entry);
    if (!match)
    {
        LOG(WARNING) << "Route not found";
        // ROUTE NOT FOUND
        return NULL;
    }

    LOG(INFO) << "Routing \"" << path << "\"";

    auto entry_ptr = entry.get();
    auto params = ParameterSet();
    for (size_t i = 0; i < entry_ptr->vars.tokens.size; i++)
    {
        // Get token and slug from entry
        char token[entry_ptr->vars.tokens.entries[i].len + 1] = {0};
        char slug[entry_ptr->vars.slugs.entries[i].len + 1] = {0};
        strncpy(token, entry_ptr->vars.tokens.entries[i].base, entry_ptr->vars.tokens.entries[i].len);
        strncpy(slug, entry_ptr->vars.slugs.entries[i].base, entry_ptr->vars.slugs.entries[i].len);

        params.insert(make_pair(string(slug), string(token)));
    }
    return ((AbstractRoute *) match.data())->handler(this, message, params);
}

}
}
