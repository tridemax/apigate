#pragma once


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	/// HTTPStatusCode
	//-------------------------------------------------------------------------------------------------
	enum class HTTPStatusCode : uint16_t
	{
		Ok				= 200,
		Unauthorized	= 401,
		Forbidden		= 403,
		NotFound		= 404
	};

	constexpr const char* HTTPStatusCodeToString(HTTPStatusCode statusCode)
	{
		switch (statusCode)
		{
		case HTTPStatusCode::Ok:
			return "OK";

		case HTTPStatusCode::Unauthorized:
			return "Unauthorized";

		case HTTPStatusCode::Forbidden:
			return "Forbidden";

		case HTTPStatusCode::NotFound:
			return "Not Found";
		}
		return "";
	}
}
