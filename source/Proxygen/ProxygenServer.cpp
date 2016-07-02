#include "platform.h"
#include "ProxygenServer.h"


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	ProxygenServer::ProxygenServer()
	{
	}

	//-------------------------------------------------------------------------------------------------
	ProxygenServer::~ProxygenServer()
	{
	}

	//-------------------------------------------------------------------------------------------------
	bool ProxygenServer::Run(proxygen::RequestHandlerFactory* handlerFactory)
	{
		std::vector<proxygen::HTTPServer::IPConfig> IPs = {
			{ folly::SocketAddress("127.0.0.1", 11000, true), proxygen::HTTPServer::Protocol::HTTP},
			{ folly::SocketAddress("127.0.0.1", 11001, true), proxygen::HTTPServer::Protocol::SPDY},
			{ folly::SocketAddress("127.0.0.1", 11002, true), proxygen::HTTPServer::Protocol::HTTP2},
		};

		proxygen::HTTPServerOptions options;
		options.threads = std::thread::hardware_concurrency();
		options.idleTimeout = std::chrono::milliseconds(60000);
		options.shutdownOn = {SIGINT, SIGTERM};
		options.enableContentCompression = false;
		options.handlerFactories.emplace_back(std::unique_ptr<proxygen::RequestHandlerFactory>(handlerFactory));

		proxygen::HTTPServer server(std::move(options));

		server.bind(IPs);

		// Start HTTPServer mainloop in a separate thread
		std::thread t([&] () {
		  server.start();
		});

		t.join();

		return true;
	}

	//-------------------------------------------------------------------------------------------------
}

