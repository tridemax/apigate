#pragma once


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	/// HTTPStatusCode
	//-------------------------------------------------------------------------------------------------
	enum class HTTPStatusCode : uint16_t
	{
		Unauthorized	= 401,
		Forbidden		= 403,
		NotFound		= 404
	};

	//-------------------------------------------------------------------------------------------------
	/// IProxygenFactory
	//-------------------------------------------------------------------------------------------------
	class IProxygenFactory
	{
	public:
		virtual proxygen::RequestHandler* CreateHandler(proxygen::HTTPMessage* httpMessage) noexcept = 0;
	};

	typedef std::vector<IProxygenFactory*> ProxygenFactories;
}
