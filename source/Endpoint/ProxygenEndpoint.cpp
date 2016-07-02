#include "platform.h"
#include "ProxygenEndpoint.h"
#include "AudioconvertHandler.h"
#include "ExceptionHandler.h"


namespace apigate
{
/*
void EchoHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept {
if (body_) {
body_->prependChain(std::move(body));
} else {
body_ = std::move(body);
}
}

void EchoHandler::onEOM() noexcept {

folly::EventBase* evb = folly::EventBaseManager::get()->getExistingEventBase();

auto* downstream = downstream_;

std::thread t([evb, downstream]()
{
	evb->runInEventBaseThread([downstream](){
		ResponseBuilder(downstream)
		  .status(200, "OK")
		  .header("Content-Type", "text/plain")
		  .body(std::string("Slava Urkaine!"))
		  .sendWithEOM();
	});
});
t.detach();
}
*/


	//-------------------------------------------------------------------------------------------------
	void ProxygenEndpoint::onServerStart(folly::EventBase* eventBase) noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	void ProxygenEndpoint::onServerStop() noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	proxygen::RequestHandler* ProxygenEndpoint::onRequest(proxygen::RequestHandler* requestHandler, proxygen::HTTPMessage* httpMessage) noexcept
	{
		if (strcasecmp(httpMessage->getPath().c_str(), "audioconvert") == 0)
		{
			return new AudioconvertHandler();
		}
		return new ExceptionHandler(HTTPStatusCode::NotFound);
	}
}
