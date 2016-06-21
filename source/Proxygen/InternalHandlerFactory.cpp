#include "platform.h"
#include "InternalHandlerFactory.h"
#include "ExceptionHandler.h"


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	void InternalHandlerFactory::onServerStart(folly::EventBase* eventBase) noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	void InternalHandlerFactory::onServerStop() noexcept
	{
	}

	//-------------------------------------------------------------------------------------------------
	proxygen::RequestHandler* InternalHandlerFactory::onRequest(proxygen::RequestHandler* requestHandler, proxygen::HTTPMessage* httpMessage) noexcept
	{
		for (auto* factory : m_factories)
		{
			if (auto* requestHandler = factory->CreateHandler(httpMessage))
			{
				return requestHandler;
			}
		}

		return new ExceptionHandler(HttpStatusCode::NotFound);
	}
}
