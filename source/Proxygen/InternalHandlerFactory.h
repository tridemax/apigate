#pragma once

#include "Miscellaneous.h"


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	/// InternalHandlerFactory
	//-------------------------------------------------------------------------------------------------
	class InternalHandlerFactory : public proxygen::RequestHandlerFactory
	{
	private:
		const ProxygenFactories&	m_factories;

	public:
		inline InternalHandlerFactory(const ProxygenFactories& factories) : m_factories(factories)
		{
		}

		virtual void onServerStart(folly::EventBase* eventBase) noexcept override;
		virtual void onServerStop() noexcept override;
		virtual proxygen::RequestHandler* onRequest(proxygen::RequestHandler* requestHandler, proxygen::HTTPMessage* httpMessage) noexcept override;
	};
}
