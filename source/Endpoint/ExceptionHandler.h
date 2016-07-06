#pragma once

#include "Miscellaneous.h"


namespace apigate
{
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

	public:
		virtual void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;
		virtual void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;
		virtual void onEOM() noexcept override;
		virtual void onUpgrade(proxygen::UpgradeProtocol protocol) noexcept override;
		virtual void requestComplete() noexcept override;
		virtual void onError(proxygen::ProxygenError error) noexcept override;
	};
}
