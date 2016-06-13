#pragma once

#include "Miscellaneous.h"
#include "../../Postgresql/PostgresqlTemplate.h"
#include "../../Postgresql/PostgresqlStatement.h"


namespace TrainingDataProvider
{
	//-------------------------------------------------------------------------------------------------
	/// BaseUtterancesTemplate
	//-------------------------------------------------------------------------------------------------
	template <class Extender>
	class BaseUtterancesTemplate
	{
	protected:
		mutable std::string			m_templateCode;
		uint64_t					m_templateHash;
		uint32_t					m_templateComponents;

	protected:
		static constexpr uint32_t	Filter_PrimaryKey				= 0x00000001u;
		static constexpr uint32_t	Filter_PrimaryKeyList			= 0x00000002u;
		static constexpr uint32_t	Filter_DurationMin				= 0x00000004u;
		static constexpr uint32_t	Filter_DurationMax				= 0x00000008u;
		static constexpr uint32_t	Filter_SpecificLanguage			= 0x00000010u;
		static constexpr uint32_t	Filter_SpecificLanguageList		= 0x00000020u;
		static constexpr uint32_t	Filter_MustHaveTranscribes		= 0x00000040u;
		static constexpr uint32_t	Filter_Ordering					= 0x00000080u;
		static constexpr uint32_t	Filter_SkipAndLimit				= 0x00000100u;

	protected:
		//---------------------------------------------------------------------------------------------
		inline BaseUtterancesTemplate() : m_templateHash(0u), m_templateComponents(0u)
		{
		}

	public:
		//---------------------------------------------------------------------------------------------
		inline uint64_t GetHash() const
		{
			return m_templateHash;
		}
	};

	//-------------------------------------------------------------------------------------------------
	/// LoadUtterancesTemplate
	//-------------------------------------------------------------------------------------------------
	template <class Extender>
	class LoadUtterancesTemplate : public BaseUtterancesTemplate<Extender>, public Postgresql::IncrementalBinder, public NonCopyable
	{
	private:
		const IdVector&				m_idVector;
		const int64_t				m_skip;
		const int64_t				m_limit;

		using BaseTemplate = BaseUtterancesTemplate<Extender>;
		using BaseTemplate::m_templateCode;
		using BaseTemplate::m_templateHash;
		using BaseTemplate::m_templateComponents;
		using BaseTemplate::Filter_PrimaryKey;
		using BaseTemplate::Filter_PrimaryKeyList;
		using BaseTemplate::Filter_DurationMin;
		using BaseTemplate::Filter_DurationMax;
		using BaseTemplate::Filter_SpecificLanguage;
		using BaseTemplate::Filter_SpecificLanguageList;
		using BaseTemplate::Filter_MustHaveTranscribes;
		using BaseTemplate::Filter_Ordering;
		using BaseTemplate::Filter_SkipAndLimit;

	public:
		inline LoadUtterancesTemplate(const IdVector& idVector, int64_t skip = 0, int64_t limit = 0);

		inline const char* GetCode() const;

		template <class ArgumentsBinder>
		inline void BindArguments(ArgumentsBinder& binder) const
		{
			// Bind primary key
			if (m_templateComponents & Filter_PrimaryKey)
			{
				binder.BindArgument(m_idVector.front());
			}

			// Bind list of primary keys
			if (m_templateComponents & Filter_PrimaryKeyList)
			{
				for (uint32_t idIndex = 0u; idIndex != m_idVector.size(); ++idIndex)
				{
					binder.BindArgument(m_idVector[idIndex]);
				}
			}

			// Bind skip and limit
			if (m_templateComponents & Filter_SkipAndLimit)
			{
				binder.BindArgument(m_limit);
				binder.BindArgument(m_skip);
			}
		}
	};

	//-------------------------------------------------------------------------------------------------
	/// SelectUtterancesTemplate
	//-------------------------------------------------------------------------------------------------
	template <class Extender>
	class SelectUtterancesTemplate : public BaseUtterancesTemplate<Extender>, public Postgresql::IncrementalBinder, public NonCopyable
	{
	private:
		const UtteranceFilter&		m_utteranceFilter;
		const int64_t				m_skip;
		const int64_t				m_limit;

		using BaseTemplate = BaseUtterancesTemplate<Extender>;
		using BaseTemplate::m_templateCode;
		using BaseTemplate::m_templateHash;
		using BaseTemplate::m_templateComponents;
		using BaseTemplate::Filter_PrimaryKey;
		using BaseTemplate::Filter_PrimaryKeyList;
		using BaseTemplate::Filter_DurationMin;
		using BaseTemplate::Filter_DurationMax;
		using BaseTemplate::Filter_SpecificLanguage;
		using BaseTemplate::Filter_SpecificLanguageList;
		using BaseTemplate::Filter_MustHaveTranscribes;
		using BaseTemplate::Filter_Ordering;
		using BaseTemplate::Filter_SkipAndLimit;

	public:
		inline SelectUtterancesTemplate(const UtteranceFilter& utteranceFilter, int64_t skip = 0, int64_t limit = 0);

		inline const char* GetCode() const;

		template <class ArgumentsBinder>
		inline void BindArguments(ArgumentsBinder& binder) const
		{
			// Bind "DurationMin"
			if (m_templateComponents & Filter_DurationMin)
			{
				binder.BindArgument(m_utteranceFilter.m_durationMin);
			}

			// Bind "DurationMax"
			if (m_templateComponents & Filter_DurationMax)
			{
				binder.BindArgument(m_utteranceFilter.m_durationMax);
			}

			// Bind "SpecificLanguage"
			if (m_templateComponents & Filter_SpecificLanguage)
			{
				binder.BindArgument(LanguageStringifier::ToString(m_utteranceFilter.m_languageList.front()));
			}

			// Bind "SpecificLanguageList"
			if (m_templateComponents & Filter_SpecificLanguageList)
			{
				for (uint32_t languageIndex = 0u; languageIndex != m_utteranceFilter.m_languageList.size(); ++languageIndex)
				{
					binder.BindArgument(LanguageStringifier::ToString(m_utteranceFilter.m_languageList[languageIndex]));
				}
			}

			// Bind "SkipAndLimit"
			if (m_templateComponents & Filter_SkipAndLimit)
			{
				binder.BindArgument(m_limit);
				binder.BindArgument(m_skip);
			}
		}
	};

	//-------------------------------------------------------------------------------------------------
	/// Extenders
	//-------------------------------------------------------------------------------------------------
	class SelectUtterancesColumns
	{
	public:
		static const char			Header[];

		static constexpr bool		GroupBy = false;
		static constexpr bool		OrderBy = true;
		static constexpr bool		SkipAndLimit = true;
	};

	class SelectUtterancesStatistics
	{
	public:
		static const char			Header[];

		static constexpr bool		GroupBy = false;
		static constexpr bool		OrderBy = false;
		static constexpr bool		SkipAndLimit = false;
	};

	class ExplainSelectionOfUtterancesColumns
	{
	public:
		static const char			Header[];

		static constexpr bool		GroupBy = false;
		static constexpr bool		OrderBy = true;
		static constexpr bool		SkipAndLimit = true;
	};

	class ExplainSelectionOfUtterancesStatistics
	{
	public:
		static const char			Header[];

		static constexpr bool		GroupBy = false;
		static constexpr bool		OrderBy = false;
		static constexpr bool		SkipAndLimit = false;
	};
}
