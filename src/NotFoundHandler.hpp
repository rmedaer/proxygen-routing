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
#ifndef NOTFOUNDHANDLER_HPP
#define NOTFOUNDHANDLER_HPP

#include <memory>
#include <folly/io/IOBuf.h>
#include <proxygen/lib/http/HTTPConstants.h>
#include <proxygen/lib/http/HTTPMessage.h>
#include <proxygen/lib/http/ProxygenErrorEnum.h>
#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>

using proxygen::RequestHandler;
using proxygen::HTTPMessage;
using proxygen::UpgradeProtocol;
using proxygen::ProxygenError;
using proxygen::ResponseBuilder;
using std::unique_ptr;
using folly::IOBuf;

/* Proxygen nested namespace proxygen::routing */
namespace proxygen {
namespace routing {

class NotFoundHandler : public RequestHandler {
public:
	NotFoundHandler(HTTPMessage* message);
	void onRequest(unique_ptr<HTTPMessage> headers) noexcept override;
	void onBody(unique_ptr<IOBuf> body) noexcept override;
	void onEOM() noexcept override;
	void onUpgrade(UpgradeProtocol protocol) noexcept override;
	void requestComplete() noexcept override;
	void onError(ProxygenError error) noexcept override;
};

}
}

#endif
