#include "NotFoundHandler.hpp"

namespace proxygen {
namespace routing {

NotFoundHandler::NotFoundHandler(HTTPMessage*)
{
}

void NotFoundHandler::onRequest(unique_ptr<HTTPMessage>) noexcept
{
}

void NotFoundHandler::onBody(unique_ptr<IOBuf>) noexcept
{
}

void NotFoundHandler::onEOM() noexcept
{
	ResponseBuilder(downstream_)
	.status(404, "Not found")
	.sendWithEOM();
}

void NotFoundHandler::onUpgrade(UpgradeProtocol) noexcept
{
}

void NotFoundHandler::requestComplete() noexcept
{
	delete this;
}

void NotFoundHandler::onError(ProxygenError) noexcept
{
	delete this;
}


}
}
