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
