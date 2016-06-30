#include "platform.h"
#include "../../source/Proxygen/ProxygenServer.h"
#include "../../source/Endpoint/ProxygenEndpoint.h"


//-------------------------------------------------------------------------------------------------
/// main
//-------------------------------------------------------------------------------------------------
int main(int argc, const char** argv)
{
	// Parse command line
	for (int32_t argumentIndex = 1; argumentIndex < argc; ++argumentIndex)
	{
		if (boost::starts_with(argv[argumentIndex], "--avconvert"))
		{
			return 0;
		}
	}

	// Run the proxygen server
	std::unique_ptr<apigate::ProxygenServer> proxygenServer(new apigate::ProxygenServer());

	if (!proxygenServer->Run(new apigate::ProxygenEndpoint()))
	{
		assert(false);
		return 1;
	}

	// Terminal loop
	while (true)
	{
		sleep(1);
	}

	return 0;
}
