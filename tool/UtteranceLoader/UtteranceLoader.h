#pragma once


extern "C"
{
	//-------------------------------------------------------------------------------------------------
	/// Language
	//-------------------------------------------------------------------------------------------------
	enum class Language : uint32_t
	{
		LanguageUnknown = 0u,
		enUS,
		deDE,
		frFR,
		esES,
		itIT,
		arSA,
		heIL,
		plPL,
		ruRU,
		ukUA,
		trTR
	};

	//-------------------------------------------------------------------------------------------------
	/// UtterancesFilter
	//-------------------------------------------------------------------------------------------------
#pragma pack(push, 1)
	struct UtterancesFilter
	{
		uint32_t					m_durationMin;					///< in milliseconds
		uint32_t					m_durationMax;					///< in milliseconds
		const Language*				m_languages;
		uint32_t					m_languagesCount;
		bool						m_mustHaveTranscribes;
	};
#pragma pack(pop)

	//-------------------------------------------------------------------------------------------------
	/// UtteranceData
	//-------------------------------------------------------------------------------------------------
#pragma pack(push, 1)
	struct UtteranceData
	{
		uint64_t					m_uniqueId;
		Language					m_language;
		const char*					m_text;
		uint32_t					m_textLength;
		uint32_t					m_timeStart;					///< in milliseconds
		uint32_t					m_timeDuration;					///< in milliseconds
		const byte*					m_audioData;
		uint32_t					m_audioDataLength;
	};
#pragma pack(pop)

	//-------------------------------------------------------------------------------------------------
	/// RestructureOperation
	//-------------------------------------------------------------------------------------------------
	enum class RestructureOperation : uint32_t
	{
		Unknown = 0u,
		Vacuum,
		VacuumAndAnalyze,
		CreateIndices,
		DeleteIndices,
		ReindexIndices
	};

	//-------------------------------------------------------------------------------------------------
	/// UtterancesEnumerator
	//-------------------------------------------------------------------------------------------------
	typedef bool(* UtterancesEnumerator)(const UtteranceData* utteranceData, void* userData);

	//-------------------------------------------------------------------------------------------------
	void* UtteranceLoader_Allocate();

	//-------------------------------------------------------------------------------------------------
	void UtteranceLoader_Free(void* utteranceLoader);

	//-------------------------------------------------------------------------------------------------
	void UtteranceLoader_ExplainQueries(void* utteranceLoader, bool explainQueries);

	//-------------------------------------------------------------------------------------------------
	bool UtteranceLoader_LoadUtterances(void* utteranceLoader, const uint64_t* identifiers, uint32_t identifiersCount);

	//-------------------------------------------------------------------------------------------------
	bool UtteranceLoader_SelectUtterances(void* utteranceLoader, const UtterancesFilter* utterancesFilter, int64_t skip, int64_t limit);

	//-------------------------------------------------------------------------------------------------
	bool UtteranceLoader_SelectUtterancesStatistics(void* utteranceLoader, const UtterancesFilter* utterancesFilter, uint64_t* filteredUtterancesQuantity, uint64_t* greatestUtteranceId);

	//-------------------------------------------------------------------------------------------------
	uint32_t UtteranceLoader_GetUtterancesCount(void* utteranceLoader);

	//-------------------------------------------------------------------------------------------------
	bool UtteranceLoader_EnumerateUtterances(void* utteranceLoader, UtterancesEnumerator utterancesEnumerator, void* userData);

	//-------------------------------------------------------------------------------------------------
	bool UtteranceLoader_RestructureDatabase(void* utteranceLoader, RestructureOperation restructureOperation);

	//-------------------------------------------------------------------------------------------------
	const char* UtteranceLoader_LastError(void* utteranceLoader);
}
