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
