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

		bool Run(const HandlerFactories& handlerFactories);
		bool Stop();
	};
}
