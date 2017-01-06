#ifndef DEFAULT_ROUTE_HANDLER_H
#define DEFAULT_ROUTE_HANDLER_H

#include <proxygen/httpserver/ResponseBuilder.h>
#include <proxygen/httpserver/RequestHandler.h>

using std::unique_ptr;

namespace proxygen {
namespace routing {

class DefaultRouteHandler : public RequestHandler
{
private:
    int code;
    const char *message;

public:
    explicit DefaultRouteHandler(int code, const char *message);

    void onRequest(unique_ptr<HTTPMessage> headers) noexcept override;

    void onBody(unique_ptr<folly::IOBuf> body) noexcept override;

    void onEOM() noexcept override;

    void onUpgrade(UpgradeProtocol protocol) noexcept override;

    void requestComplete() noexcept override;

    void onError(ProxygenError error) noexcept override;
};

}
}

#endif // DEFAULT_ROUTE_HANDLER_H
