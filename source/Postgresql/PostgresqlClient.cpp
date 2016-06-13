#include "stdafx.h"
#include "PostgresqlClient.h"


namespace Postgresql
{
	//-------------------------------------------------------------------------------------------------
	PostgresqlClient::PostgresqlClient()
	{
	}

	//-------------------------------------------------------------------------------------------------
	PostgresqlClient::~PostgresqlClient()
	{
		for (auto& connection : m_connectionCache)
		{
			connection.CloseConnection();
		}
	}

	//-------------------------------------------------------------------------------------------------
	PostgresqlConnection& PostgresqlClient::GetConnection(const char* dbConnectionParams)
	{
		auto& connection = m_connectionCache.local();

		if (!connection.IsOpen())
		{
			connection.OpenConnection(dbConnectionParams);
			assert(connection.IsOpen());
		}

		return connection;
	}
}
