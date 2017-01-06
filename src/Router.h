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

#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <memory>
#include <map>
#include <string>
#include <r3.hpp>
#include <folly/io/async/EventBase.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>

#include "AbstractRoute.h"
#include "DefaultRouteHandler.h"

using namespace std;

/* Nested namespace proxygen::routing */
namespace proxygen {
namespace routing {

/*!
 * \brief Dispatch incoming request to route handler.
 *
 * Router class is an implementation of proxygen RequestHandlerFactory.
 * It's using libr3 backend to route incoming request towards targeted
 * route.
 */
class Router : public RequestHandlerFactory
{
private:
    r3::Tree tree;

public:
    map<string, string> settings;

    /*!
     * \brief Router constructor; initialize a Router object.
     *
     * \param routes the routes/handlers to register.
     */
    Router(vector<shared_ptr<AbstractRoute>> routes);

    Router(vector<shared_ptr<AbstractRoute>> routes, map<string, string> settings);

    void addRoute(vector<shared_ptr<AbstractRoute>> routes);

    void addRoute(shared_ptr<AbstractRoute> route);

    /*!
     * \brief Compile r3::tree with given routes.
     */
    void compile();

    /*!
     * Callback function when server start. Not implemented.
     */
    void onServerStart(folly::EventBase*) noexcept override;

    /*!
     * Callback function when server stop. Not implemented.
     */
    void onServerStop() noexcept override;

    /*!
     * Invoked when server receive an incoming request.
     *
     * \param handler the upstream RequestHandler.
     * \param message the HTTP message.
     */
    RequestHandler* onRequest(RequestHandler* handler, HTTPMessage* message) noexcept override;
};

}
}

#endif // ROUTER_HPP
