#pragma once

#include "PostgresqlConnection.h"


namespace Postgresql
{
	//-------------------------------------------------------------------------------------------------
	/// PostgresqlClient
	//-------------------------------------------------------------------------------------------------
	class PostgresqlClient : public NonCopyable
	{
	private:
		typedef tbb::enumerable_thread_specific<PostgresqlConnection> ConnectionCache;

	private:
		ConnectionCache				m_connectionCache;

	public:
		PostgresqlClient();
		~PostgresqlClient();

		PostgresqlConnection& GetConnection(const char* dbConnectionParams);

	public:
		//---------------------------------------------------------------------------------------------
		static inline PostgresqlClient& Instance()
		{
			static PostgresqlClient instance;
			return instance;
		}
	};
}
