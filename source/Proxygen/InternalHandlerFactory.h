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
		const HandlerFactories&		m_handlerFactories;

	public:
		inline InternalHandlerFactory(const HandlerFactories& handlerFactories) : m_handlerFactories(handlerFactories)
		{
		}

		virtual void onServerStart(folly::EventBase* eventBase) noexcept override;
		virtual void onServerStop() noexcept override;
		virtual proxygen::RequestHandler* onRequest(proxygen::RequestHandler* requestHandler, proxygen::HTTPMessage* httpMessage) noexcept override;
	};
}
