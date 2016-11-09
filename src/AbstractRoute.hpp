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
