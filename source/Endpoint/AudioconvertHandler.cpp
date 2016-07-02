#include "platform.h"
#include "AudioconvertHandler.h"


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	void AudioconvertHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	void AudioconvertHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	void AudioconvertHandler::onEOM() noexcept
	{
		proxygen::ResponseBuilder responseBuilder(downstream_);

		responseBuilder.status(200, "OK");

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
