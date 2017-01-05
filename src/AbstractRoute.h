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

#ifndef ABSTRACTROUTE_HPP
#define ABSTRACTROUTE_HPP

#include <string>
#include <map>
#include <utility>
#include <ostream>
#include <proxygen/lib/http/HTTPMethod.h>
#include <proxygen/lib/http/HTTPMessage.h>
#include <proxygen/httpserver/RequestHandler.h>
#include <r3.hpp>

using namespace std;

namespace proxygen {
namespace routing {

using Parameter = pair<string, string>;
using ParameterSet = map<string, string>;

class Router;

class AbstractRoute
{
public:
    std::string path;
    HTTPMethod method;

    /*!
     * \brief AbstractRoute constructor.
     */
    explicit AbstractRoute(HTTPMethod method, const std::string path) :
        method(method), path(path)
    {
    }

    virtual ~AbstractRoute()
    {
    }

    /*!
     * \brief Instance new handler.
     *
     * \param router Upstream router. 
     * \param message HTTP message.
     * \param params a list of string from slugs.
     */
    virtual RequestHandler *handler(
        Router *router,
        HTTPMessage *message,
        ParameterSet params) const = 0;

    /*!
     * \brief Return C string from path.
     *
     * \return const char *
     */
    const char *c_path() const
    {
        return this->path.c_str();
    }

    /*!
     * \brief Return r3 int method.
     *
     * \return int
     */
    int r3_method() const
    {
        return AbstractRoute::proxygen_to_r3_method(this->method);
    }

    /*!
     * \brief Return representing method string.
     */
    const string str_method() const
    {
        switch (method)
        {
            case HTTPMethod::GET:     return "GET";
            case HTTPMethod::POST:    return "POST";
            case HTTPMethod::OPTIONS: return "OPTIONS";
            case HTTPMethod::DELETE:  return "DELETE";
            case HTTPMethod::HEAD:    return "HEAD";
            case HTTPMethod::PUT:     return "PUT";
            default:                  return NULL;
        }
    }

    const char *c_method() const
    {
        return this->str_method().c_str();
    }

    /*!
     * \brief Convert proxygen::HTTPMethod (enum) to r3 int.
     */
    static int proxygen_to_r3_method(HTTPMethod method)
    {
        switch (method)
        {
            case HTTPMethod::GET:     return METHOD_GET;
            case HTTPMethod::POST:    return METHOD_POST;
            case HTTPMethod::OPTIONS: return METHOD_OPTIONS;
            case HTTPMethod::DELETE:  return METHOD_DELETE;
            case HTTPMethod::HEAD:    return METHOD_HEAD;
            case HTTPMethod::PUT:     return METHOD_PUT;
            default:                  return 0;
        }
    }

    /*!
     * \brief toString method.
     */
    friend ostream&
    operator<< (ostream& stream, const AbstractRoute& route)
    {
        return stream << route.str_method() << ' ' << route.path;
    }


};

}
}

#endif // ABSTRACTROUTE_HPP
