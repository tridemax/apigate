#pragma once

#include "../../HttpDispatcher/HttpDispatcher.h"


namespace ApiGate
{
	//-------------------------------------------------------------------------------------------------
	/// SpeechStorageHandler
	//-------------------------------------------------------------------------------------------------
	class SpeechStorageHandler
	{
	public:
		void BindToDispatcher(HttpDispatcher& httpDispatcher);

	private:
		int32_t SelectUtterances(UrlArgumentMap& urlArguments, HttpContentType requestContentType, std::vector<byte>& requestContent, HttpContentType& responseContentType, Aux::ChunkedStorage<byte>& responseContent);
		int32_t SelectUtterancesStatistics(UrlArgumentMap& urlArguments, HttpContentType requestContentType, std::vector<byte>& requestContent, HttpContentType& responseContentType, Aux::ChunkedStorage<byte>& responseContent);
	};
}
