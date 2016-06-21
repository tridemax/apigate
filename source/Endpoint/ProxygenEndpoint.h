#pragma once


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	/// ProxygenEndpoint
	//-------------------------------------------------------------------------------------------------
	class ProxygenEndpoint : public boost::noncopyable, public proxygen::RequestHandlerFactory
	{
	private:
//		const ProxygenFactories&	m_factories;

	public:
		//---------------------------------------------------------------------------------------------
		/// RequestHandlerFactory

		virtual void onServerStart(folly::EventBase* eventBase) noexcept override;
		virtual void onServerStop() noexcept override;
		virtual proxygen::RequestHandler* onRequest(proxygen::RequestHandler* requestHandler, proxygen::HTTPMessage* httpMessage) noexcept override;
	};
}
