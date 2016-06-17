#pragma once


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	/// HttpStatusCode
	//-------------------------------------------------------------------------------------------------
	enum class HttpStatusCode : uint16_t
	{
		Unauthorized	= 401,
		Forbidden		= 403,
		NotFound		= 404
	};

	//-------------------------------------------------------------------------------------------------
	/// IHandlerFactory
	//-------------------------------------------------------------------------------------------------
	class IHandlerFactory
	{
	public:
		virtual proxygen::RequestHandler* CreateHandler(proxygen::HTTPMessage* httpMessage) noexcept = 0;
	};

	typedef std::vector<IHandlerFactory*> HandlerFactories;
}
