#include "stdafx.h"
#include "TemplatesForUtterances.h"


namespace TrainingDataProvider
{
	//-------------------------------------------------------------------------------------------------
	template <class Extender>
	inline LoadUtterancesTemplate<Extender>::LoadUtterancesTemplate(const IdVector& idVector, int64_t skip, int64_t limit) :
		m_idVector(idVector),
		m_skip(skip),
		m_limit(limit)
	{
		HashMurmur3<uint64_t> hasher;

		// Check for "PrimaryKey" and "PrimaryKeyList" filters
		if (!m_idVector.empty())
		{
			if (m_idVector.size() == 1u)
			{
				m_templateComponents |= Filter_PrimaryKey;
			}
			else
			{
				m_templateComponents |= Filter_PrimaryKeyList;
			}

			hasher.Add(m_idVector.size());
		}

		// Check for ordering
		if (Extender::OrderBy)
		{
			m_templateComponents |= Filter_Ordering;
		}

		// Check for skip and limit
		if (Extender::SkipAndLimit && limit != 0)
		{
			m_templateComponents |= Filter_SkipAndLimit;
		}

		// Compute template hash
		hasher.Add(m_templateComponents);
		hasher.Add(reinterpret_cast<const void*>(Extender::Header));

		m_templateHash = hasher.GetInternalValue();
	}

	//-------------------------------------------------------------------------------------------------
	template <class Extender>
	inline const char* LoadUtterancesTemplate<Extender>::GetCode() const
	{
		if (!m_templateCode.empty())
		{
			return m_templateCode.c_str();
		}

		m_templateCode.reserve(512u);
		m_templateCode.assign(Extender::Header);

		char indexConvBuffer[16];
		uint32_t indexCurrentValue = 0u;

		// Add code for "PrimaryKey" filter
		if (m_templateComponents & Filter_PrimaryKey)
		{
			m_templateCode.append("utterance_id = $");
			m_templateCode.append(indexConvBuffer, Detail::u32toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);
			m_templateCode.append(" and ");
		}

		// Add code for "PrimaryKeyList" filter
		if (m_templateComponents & Filter_PrimaryKeyList)
		{
			m_templateCode.append("utterance_id in (");

			for (uint32_t idIndex = 0u; idIndex != m_idVector.size(); ++idIndex)
			{
				m_templateCode.append(1, '$');
				m_templateCode.append(indexConvBuffer, Detail::u32toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);

				if (idIndex != m_idVector.size() - 1u)
				{
					m_templateCode.append(1, ',');
				}
			}

			m_templateCode.append(") and ");
		}

		// Drop trailing "where " or "and "
		if (m_templateCode.size() == _countof(Extender::Header) - 1u)
		{
			m_templateCode.resize(m_templateCode.size() - 6u);
		}
		else
		{
			m_templateCode.resize(m_templateCode.size() - 4u);
		}

		// Add code for ordering
		if (m_templateComponents & Filter_Ordering)
		{
			m_templateCode.append("order by utterance_id ");
		}

		// Add code for skip and limit
		if (m_templateComponents & Filter_SkipAndLimit)
		{
			m_templateCode.append("limit $");
			m_templateCode.append(indexConvBuffer, Detail::i64toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);
			m_templateCode.append(" offset $");
			m_templateCode.append(indexConvBuffer, Detail::i64toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);
		}

		// Add finalizer
		m_templateCode.append(1, ';');

		return m_templateCode.c_str();
	}

	//-------------------------------------------------------------------------------------------------
	template <class Extender>
	inline SelectUtterancesTemplate<Extender>::SelectUtterancesTemplate(const UtteranceFilter& utteranceFilter, int64_t skip, int64_t limit) :
		m_utteranceFilter(utteranceFilter),
		m_skip(skip),
		m_limit(limit)
	{
		HashMurmur3<uint64_t> hasher;

		// Check for "DurationMin" filter
		if (m_utteranceFilter.m_durationMin != 0u)
		{
			m_templateComponents |= Filter_DurationMin;
		}

		// Check for "DurationMax" filter
		if (m_utteranceFilter.m_durationMax != 0u)
		{
			m_templateComponents |= Filter_DurationMax;
		}

		// Check for "SpecificLanguage" and "SpecificLanguageList" filters
		if (!m_utteranceFilter.m_languageList.empty())
		{
			if (m_utteranceFilter.m_languageList.size() == 1u)
			{
				m_templateComponents |= Filter_SpecificLanguage;
			}
			else
			{
				m_templateComponents |= Filter_SpecificLanguageList;
			}

			hasher.Add(m_utteranceFilter.m_languageList.size());
		}

		// Check for "MustHaveTranscribes" filter
		if (m_utteranceFilter.m_mustHaveTranscribes)
		{
			m_templateComponents |= Filter_MustHaveTranscribes;
		}

		// Check for ordering
		if (Extender::OrderBy)
		{
			m_templateComponents |= Filter_Ordering;
		}

		// Check for skip and limit
		if (Extender::SkipAndLimit && limit != 0)
		{
			m_templateComponents |= Filter_SkipAndLimit;
		}

		// Compute template hash
		hasher.Add(m_templateComponents);
		hasher.Add(Extender::Header);

		m_templateHash = hasher.GetInternalValue();
	}

	//-------------------------------------------------------------------------------------------------
	template <class Extender>
	inline const char* SelectUtterancesTemplate<Extender>::GetCode() const
	{
		if (!m_templateCode.empty())
		{
			return m_templateCode.c_str();
		}

		m_templateCode.reserve(512u);
		m_templateCode.assign(Extender::Header);

		char indexConvBuffer[16];
		uint32_t indexCurrentValue = 0u;

		// Add code for "DurationMin" filter
		if (m_templateComponents & Filter_DurationMin)
		{
			m_templateCode.append("time_duration >= $");
			m_templateCode.append(indexConvBuffer, Detail::u32toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);
			m_templateCode.append(" and ");
		}

		// Add code for "DurationMax" filter
		if (m_templateComponents & Filter_DurationMax)
		{
			m_templateCode.append("time_duration <= $");
			m_templateCode.append(indexConvBuffer, Detail::u32toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);
			m_templateCode.append(" and ");
		}

		// Add code for "SpecificLanguage" filter
		if (m_templateComponents & Filter_SpecificLanguage)
		{
			m_templateCode.append("language = $");
			m_templateCode.append(indexConvBuffer, Detail::u32toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);
			m_templateCode.append(" and ");
		}

		// Add code for "SpecificLanguageList" filter
		if (m_templateComponents & Filter_SpecificLanguageList)
		{
			m_templateCode.append("language in (");

			for (uint32_t languageIndex = 0u; languageIndex != m_utteranceFilter.m_languageList.size(); ++languageIndex)
			{
				m_templateCode.append(1, '$');
				m_templateCode.append(indexConvBuffer, Detail::u32toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);

				if (languageIndex != m_utteranceFilter.m_languageList.size() - 1u)
				{
					m_templateCode.append(1, ',');
				}
			}

			m_templateCode.append(") and ");
		}

		// Add code for "MustHaveTranscribes" filter
		if (m_templateComponents & Filter_MustHaveTranscribes)
		{
			m_templateCode.append("transcribes is not null and transcribes != '{}' and ");
		}

		// Drop trailing "where " or "and "
		if (m_templateCode.size() == _countof(Extender::Header) - 1u)
		{
			m_templateCode.resize(m_templateCode.size() - 6u);
		}
		else
		{
			m_templateCode.resize(m_templateCode.size() - 4u);
		}

		// Add code for ordering
		if (m_templateComponents & Filter_Ordering)
		{
			m_templateCode.append("order by utterance_id ");
		}

		// Add code for skip and limit
		if (m_templateComponents & Filter_SkipAndLimit)
		{
			m_templateCode.append("limit $");
			m_templateCode.append(indexConvBuffer, Detail::i64toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);
			m_templateCode.append(" offset $");
			m_templateCode.append(indexConvBuffer, Detail::i64toa(++indexCurrentValue, indexConvBuffer) - indexConvBuffer);
		}

		// Add finalizer
		m_templateCode.append(1, ';');

		return m_templateCode.c_str();
	}

	//-------------------------------------------------------------------------------------------------
	template class LoadUtterancesTemplate<SelectUtterancesColumns>;
	template class LoadUtterancesTemplate<ExplainSelectionOfUtterancesColumns>;

	template class SelectUtterancesTemplate<SelectUtterancesColumns>;
	template class SelectUtterancesTemplate<SelectUtterancesStatistics>;
	template class SelectUtterancesTemplate<ExplainSelectionOfUtterancesColumns>;
	template class SelectUtterancesTemplate<ExplainSelectionOfUtterancesStatistics>;


	const char SelectUtterancesColumns::Header[] =
		"select utterance_id, content, audio_format, time_start, time_duration, language, transcribes[1] "
		"from utterances where ";

	const char SelectUtterancesStatistics::Header[] =
		"select count(*), coalesce(max(utterance_id), 0) "
		"from utterances where ";

	const char ExplainSelectionOfUtterancesColumns::Header[] =
		"explain select utterance_id, content, audio_format, time_start, time_duration, language, transcribes[1] "
		"from utterances where ";

	const char ExplainSelectionOfUtterancesStatistics::Header[] =
		"explain select count(*), coalesce(max(utterance_id), 0) "
		"from utterances where ";
}
