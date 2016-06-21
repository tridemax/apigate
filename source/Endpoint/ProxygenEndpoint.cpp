#include "platform.h"
#include "ProxygenEndpoint.h"


namespace apigate
{
//-------------------------------------------------------------------------------------------------
/// HTTPStatusCode
//-------------------------------------------------------------------------------------------------
enum class HTTPStatusCode : uint16_t
{
	Unauthorized	= 401,
	Forbidden		= 403,
	NotFound		= 404
};

//-------------------------------------------------------------------------------------------------
/// ExceptionHandler
//-------------------------------------------------------------------------------------------------
class ExceptionHandler : public proxygen::RequestHandler
{
private:
	HTTPStatusCode				m_statusCode;

public:
	inline ExceptionHandler(HTTPStatusCode statusCode) : m_statusCode(statusCode)
	{
	}

	virtual void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;
	virtual void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;
	virtual void onEOM() noexcept override;
	virtual void onUpgrade(proxygen::UpgradeProtocol protocol) noexcept override;
	virtual void requestComplete() noexcept override;
	virtual void onError(proxygen::ProxygenError error) noexcept override;
};

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
	case HTTPStatusCode::Unauthorized:
		responseBuilder.status(static_cast<uint16_t>(HTTPStatusCode::Unauthorized), "Unauthorized");
		break;

	case HTTPStatusCode::Forbidden:
		responseBuilder.status(static_cast<uint16_t>(HTTPStatusCode::Forbidden), "Forbidden");
		break;

	case HTTPStatusCode::NotFound:
		responseBuilder.status(static_cast<uint16_t>(HTTPStatusCode::NotFound), "Not Found");
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
		return new ExceptionHandler(HTTPStatusCode::NotFound);
	}
}
