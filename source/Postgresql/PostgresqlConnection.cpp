#include "stdafx.h"
#include "PostgresqlConnection.h"


namespace Postgresql
{
	//-------------------------------------------------------------------------------------------------
	PostgresqlConnection::PostgresqlConnection() : m_internalConnection(nullptr)
	{
	}

	//-------------------------------------------------------------------------------------------------
	PostgresqlConnection::~PostgresqlConnection()
	{
		CloseConnection();
	}

	//-------------------------------------------------------------------------------------------------
	bool PostgresqlConnection::OpenConnection(const char* dbConnectionParams)
	{
		// Close currently opened connection
		CloseConnection();

		// Try to open connection
		m_internalConnection = PQconnectdb(dbConnectionParams);

		return PQstatus(m_internalConnection) != CONNECTION_OK;
	}

	//-------------------------------------------------------------------------------------------------
	void PostgresqlConnection::CloseConnection()
	{
		if (m_internalConnection)
		{
			PQfinish(m_internalConnection);
			m_internalConnection = nullptr;
		}

		m_statementCache.clear();
	}
}
