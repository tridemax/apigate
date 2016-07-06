#include "platform.h"
#include "AudioconvertHandler.h"
#include "Miscellaneous.h"


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	void AudioconvertHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept
	{
		auto& queryParams = headers->getQueryParams();

		auto inputFormat = queryParams.find("in");
		auto outputFormat = queryParams.find("out");
	}

	//-------------------------------------------------------------------------------------------------
	void AudioconvertHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept
	{
	}

/*	//-------------------------------------------------------------------------------------------------
	void AudioconvertHandler::onEOM() noexcept
	{
		proxygen::ResponseBuilder responseBuilder(downstream_);

		responseBuilder.status(static_cast<uint16_t>(HTTPStatusCode::Ok), HTTPStatusCodeToString(HTTPStatusCode::Ok));

		responseBuilder.sendWithEOM();
	}

	//-------------------------------------------------------------------------------------------------
	void AudioconvertHandler::onUpgrade(proxygen::UpgradeProtocol protocol) noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	void AudioconvertHandler::requestComplete() noexcept
	{
		delete this;
	}

	//-------------------------------------------------------------------------------------------------
	void AudioconvertHandler::onError(proxygen::ProxygenError error) noexcept
	{
		delete this;
	}
}
