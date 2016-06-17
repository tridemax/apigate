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
		for (auto* handlerFactory : m_handlerFactories)
		{
			if (auto* requestHandler = handlerFactory->CreateHandler(httpMessage))
			{
				return requestHandler;
			}
		}

		return new ExceptionHandler(HttpStatusCode::NotFound);
	}
}
