#include "platform.h"
#include "ExceptionHandler.h"


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	void ExceptionHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	void ExceptionHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	void ExceptionHandler::onEOM() noexcept
	{
		proxygen::ResponseBuilder responseBuilder(downstream_);

		switch (m_statusCode)
		{
		case HttpStatusCode::Unauthorized:
			responseBuilder.status(static_cast<uint16_t>(HttpStatusCode::Unauthorized), "Unauthorized");
			break;

		case HttpStatusCode::Forbidden:
			responseBuilder.status(static_cast<uint16_t>(HttpStatusCode::Forbidden), "Forbidden");
			break;

		case HttpStatusCode::NotFound:
			responseBuilder.status(static_cast<uint16_t>(HttpStatusCode::NotFound), "Not Found");
			break;
		}

		responseBuilder.sendWithEOM();
	}

	//-------------------------------------------------------------------------------------------------
	void ExceptionHandler::onUpgrade(proxygen::UpgradeProtocol protocol) noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	void ExceptionHandler::requestComplete() noexcept
	{
		delete this;
	}

	//-------------------------------------------------------------------------------------------------
	void ExceptionHandler::onError(proxygen::ProxygenError error) noexcept
	{
		delete this;
	}
}


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
