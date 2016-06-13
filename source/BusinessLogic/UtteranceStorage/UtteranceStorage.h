#pragma once

#include "Miscellaneous.h"
#include "../../Postgresql/PostgresqlClient.h"


namespace TrainingDataProvider
{
	//-------------------------------------------------------------------------------------------------
	/// UtteranceLoader
	//-------------------------------------------------------------------------------------------------
	class UtteranceLoader : public NonCopyable
	{
	private:
		bool						m_explainQueries;
		std::string					m_lastError;

		static const char			m_dbConnectionParams[];

	public:
		UtteranceLoader();
		~UtteranceLoader();

		void ExplainQueries(bool explainQueries);
		bool LoadUtterances(const IdVector& idVector, std::list<Utterance>& utteranceList);
		bool SelectUtterances(const UtteranceFilter& utteranceFilter, int64_t skip, int64_t limit, std::list<Utterance>& utteranceList);
		bool SelectUtterancesStatistics(const UtteranceFilter& utteranceFilter, uint64_t& filteredUtterancesQuantity, uint64_t& greatestUtteranceId);
		bool VacuumUtterances();
		bool VacuumAndAnalyzeUtterances();
		bool CreateIndicesForUtterances();
		bool DeleteIndicesForUtterances();
		bool ReindexIndicesForUtterances();
		const std::string& LastError() const;

	private:
		template <class TemplateType>
		bool ExplainQueryPlan(Postgresql::PostgresqlConnection& connection, const TemplateType& explainQueryPlanTemplate);
	};
}
