#include "DefaultRouteHandler.h"

using std::unique_ptr;
using namespace proxygen;

namespace proxygen {
namespace routing {

DefaultRouteHandler::DefaultRouteHandler(
    int code,
    const char *message)
    : code(code), message(message)
{
}

void
DefaultRouteHandler::onRequest(
    unique_ptr<HTTPMessage> headers) noexcept
{
}

void
DefaultRouteHandler::onBody(
    unique_ptr<folly::IOBuf> body) noexcept
{
}

void
DefaultRouteHandler::onEOM() noexcept
{
    ResponseBuilder(this->downstream_)
        .status(this->code, this->message)
        .sendWithEOM();
}

void
DefaultRouteHandler::onUpgrade(
    UpgradeProtocol protocol) noexcept
{
    // Does not support Upgrade
}

void
DefaultRouteHandler::requestComplete() noexcept
{
    delete this;
}

void
DefaultRouteHandler::onError(ProxygenError error) noexcept
{
    delete this;
}

}
}
