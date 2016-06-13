#pragma once


namespace Postgresql
{
	//-------------------------------------------------------------------------------------------------
	/// PostgresqlTemplate
	//-------------------------------------------------------------------------------------------------
	class PostgresqlTemplate : public NonCopyable
	{
	private:
		const char*					m_templateCode;
		const uint64_t				m_templateHash;

	public:
		//---------------------------------------------------------------------------------------------
		__forceinline PostgresqlTemplate(const char* templateCode) : m_templateCode(templateCode), m_templateHash(HashMurmur3<uint64_t>(templateCode).GetInternalValue())
		{
		}

		//---------------------------------------------------------------------------------------------
		__forceinline const char* GetCode() const
		{
			return m_templateCode;
		}

		//---------------------------------------------------------------------------------------------
		__forceinline uint64_t GetHash() const
		{
			return m_templateHash;
		}
	};
}
