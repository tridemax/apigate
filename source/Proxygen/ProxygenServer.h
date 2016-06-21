#pragma once

#include "Miscellaneous.h"


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	/// ProxygenServer
	//-------------------------------------------------------------------------------------------------
	class ProxygenServer : public boost::noncopyable
	{
	public:
		ProxygenServer();
		~ProxygenServer();

		bool Run(proxygen::RequestHandlerFactory* handlerFactory);
		bool Stop();
	};
}
