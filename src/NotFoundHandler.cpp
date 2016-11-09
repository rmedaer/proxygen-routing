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
