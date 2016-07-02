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
}
