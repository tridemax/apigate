#include "stdafx.h"
#include "UtteranceLoaderAPI.h"
#include "UtteranceLoader.h"


namespace TrainingDataProvider
{
	//-------------------------------------------------------------------------------------------------
	class UtteranceLoaderExportsStub
	{
	public:
		UtteranceLoader				m_utteranceLoader;
		void*						m_audioConverter;
		std::list<Utterance>		m_utteranceList;
		std::string					m_lastError;

	public:
		//---------------------------------------------------------------------------------------------
		inline UtteranceLoaderExportsStub() : m_audioConverter(AudioConverter_Allocate())
		{
		}

		//---------------------------------------------------------------------------------------------
		inline ~UtteranceLoaderExportsStub()
		{
			if (m_audioConverter)
			{
				AudioConverter_Free(m_audioConverter);
			}
		}
	};

	//-------------------------------------------------------------------------------------------------
	extern "C" void* UtteranceLoader_Allocate()
	{
		return new UtteranceLoaderExportsStub();
	}

	//-------------------------------------------------------------------------------------------------
	extern "C" void UtteranceLoader_Free(void* utteranceLoader)
	{
		UtteranceLoaderExportsStub* utteranceLoaderStub = reinterpret_cast<UtteranceLoaderExportsStub*>(utteranceLoader);
		assert(utteranceLoaderStub);

		delete utteranceLoaderStub;
	}

	//-------------------------------------------------------------------------------------------------
	extern "C" void UtteranceLoader_ExplainQueries(void* utteranceLoader, bool explainQueries)
	{
		UtteranceLoaderExportsStub* utteranceLoaderStub = reinterpret_cast<UtteranceLoaderExportsStub*>(utteranceLoader);
		assert(utteranceLoaderStub);

		utteranceLoaderStub->m_utteranceLoader.ExplainQueries(explainQueries);
	}

	//-------------------------------------------------------------------------------------------------
	extern "C" bool UtteranceLoader_LoadUtterances(void* utteranceLoader, const uint64_t* identifiers, uint32_t identifiersCount)
	{
		UtteranceLoaderExportsStub* utteranceLoaderStub = reinterpret_cast<UtteranceLoaderExportsStub*>(utteranceLoader);
		assert(utteranceLoaderStub);

		IdVector idVector;
		idVector.assign(identifiers, identifiers + identifiersCount);

		if (!utteranceLoaderStub->m_utteranceLoader.LoadUtterances(idVector, utteranceLoaderStub->m_utteranceList))
		{
			utteranceLoaderStub->m_lastError = utteranceLoaderStub->m_utteranceLoader.LastError();
			assert(false);
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	extern "C" bool UtteranceLoader_SelectUtterances(void* utteranceLoader, const UtterancesFilter* utterancesFilter, int64_t skip, int64_t limit)
	{
		UtteranceLoaderExportsStub* utteranceLoaderStub = reinterpret_cast<UtteranceLoaderExportsStub*>(utteranceLoader);
		assert(utteranceLoaderStub);

		UtteranceFilter utteranceFilter;
		utteranceFilter.m_durationMin = utterancesFilter->m_durationMin;
		utteranceFilter.m_durationMax = utterancesFilter->m_durationMax;
		utteranceFilter.m_languageList.assign(utterancesFilter->m_languages, utterancesFilter->m_languages + utterancesFilter->m_languagesCount);
		utteranceFilter.m_mustHaveTranscribes = utterancesFilter->m_mustHaveTranscribes;

		if (!utteranceLoaderStub->m_utteranceLoader.SelectUtterances(utteranceFilter, skip, limit, utteranceLoaderStub->m_utteranceList))
		{
			utteranceLoaderStub->m_lastError = utteranceLoaderStub->m_utteranceLoader.LastError();
			assert(false);
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	extern "C" bool UtteranceLoader_SelectUtterancesStatistics(void* utteranceLoader, const UtterancesFilter* utterancesFilter, uint64_t* filteredUtterancesQuantity, uint64_t* greatestUtteranceId)
	{
		UtteranceLoaderExportsStub* utteranceLoaderStub = reinterpret_cast<UtteranceLoaderExportsStub*>(utteranceLoader);
		assert(utteranceLoaderStub);

		UtteranceFilter utteranceFilter;
		utteranceFilter.m_durationMin = utterancesFilter->m_durationMin;
		utteranceFilter.m_durationMax = utterancesFilter->m_durationMax;
		utteranceFilter.m_languageList.assign(utterancesFilter->m_languages, utterancesFilter->m_languages + utterancesFilter->m_languagesCount);
		utteranceFilter.m_mustHaveTranscribes = utterancesFilter->m_mustHaveTranscribes;

		if (!utteranceLoaderStub->m_utteranceLoader.SelectUtterancesStatistics(utteranceFilter, *filteredUtterancesQuantity, *greatestUtteranceId))
		{
			utteranceLoaderStub->m_lastError = utteranceLoaderStub->m_utteranceLoader.LastError();
			assert(false);
			return false;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	extern "C" uint32_t UtteranceLoader_GetUtterancesCount(void* utteranceLoader)
	{
		UtteranceLoaderExportsStub* utteranceLoaderStub = reinterpret_cast<UtteranceLoaderExportsStub*>(utteranceLoader);
		assert(utteranceLoaderStub);

		return static_cast<uint32_t>(utteranceLoaderStub->m_utteranceList.size());
	}

	//-------------------------------------------------------------------------------------------------
	extern "C" bool UtteranceLoader_EnumerateUtterances(void* utteranceLoader, UtterancesEnumerator utterancesEnumerator, void* userData)
	{
		UtteranceLoaderExportsStub* utteranceLoaderStub = reinterpret_cast<UtteranceLoaderExportsStub*>(utteranceLoader);
		assert(utteranceLoaderStub);

		UtteranceData utteranceData;

		for (auto& utterance : utteranceLoaderStub->m_utteranceList)
		{
			// Decode audio if needed
			if (utterance.m_audioFormat != AudioFormat::AudioWave)
			{
				AudioConverter_SetInput(utteranceLoaderStub->m_audioConverter, utterance.m_content.data(), utterance.m_content.size(), utterance.m_audioFormat);

				if (!AudioConverter_ConvertAudio(utteranceLoaderStub->m_audioConverter, AudioFormat::AudioWave))
				{
					utteranceLoaderStub->m_lastError = AudioConverter_LastError(utteranceLoaderStub->m_audioConverter);
					assert(false);
					continue;
				}

				auto conversionResult = AudioConverter_GetResult(utteranceLoaderStub->m_audioConverter, 0u);
				assert(conversionResult.m_data && conversionResult.m_dataLength);

				utterance.m_content.resize(conversionResult.m_dataLength);
				memcpy(utterance.m_content.data(), conversionResult.m_data, conversionResult.m_dataLength);

				utterance.m_audioFormat = AudioFormat::AudioWave;
			}

			// Fill the structure
			utteranceData.m_uniqueId = utterance.m_utteranceId;
			utteranceData.m_language = utterance.m_language;
			utteranceData.m_text = utterance.m_transcribe.c_str();
			utteranceData.m_textLength = static_cast<uint32_t>(utterance.m_transcribe.size());
			utteranceData.m_timeStart = utterance.m_timeStart;
			utteranceData.m_timeDuration = utterance.m_timeDuration;
			utteranceData.m_audioData = utterance.m_content.data();
			utteranceData.m_audioDataLength = static_cast<uint32_t>(utterance.m_content.size());

			utterancesEnumerator(&utteranceData, userData);
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	extern "C" bool UtteranceLoader_RestructureDatabase(void* utteranceLoader, RestructureOperation restructureOperation)
	{
		UtteranceLoaderExportsStub* utteranceLoaderStub = reinterpret_cast<UtteranceLoaderExportsStub*>(utteranceLoader);
		assert(utteranceLoaderStub);

		switch (restructureOperation)
		{
		case RestructureOperation::Vacuum:
			if (!utteranceLoaderStub->m_utteranceLoader.VacuumUtterances())
			{
				utteranceLoaderStub->m_lastError = utteranceLoaderStub->m_utteranceLoader.LastError();
				assert(false);
				return false;
			}
			break;

		case RestructureOperation::VacuumAndAnalyze:
			if (!utteranceLoaderStub->m_utteranceLoader.VacuumAndAnalyzeUtterances())
			{
				utteranceLoaderStub->m_lastError = utteranceLoaderStub->m_utteranceLoader.LastError();
				assert(false);
				return false;
			}
			break;

		case RestructureOperation::CreateIndices:
			if (!utteranceLoaderStub->m_utteranceLoader.CreateIndicesForUtterances())
			{
				utteranceLoaderStub->m_lastError = utteranceLoaderStub->m_utteranceLoader.LastError();
				assert(false);
				return false;
			}
			break;

		case RestructureOperation::DeleteIndices:
			if (!utteranceLoaderStub->m_utteranceLoader.DeleteIndicesForUtterances())
			{
				utteranceLoaderStub->m_lastError = utteranceLoaderStub->m_utteranceLoader.LastError();
				assert(false);
				return false;
			}
			break;

		case RestructureOperation::ReindexIndices:
			if (!utteranceLoaderStub->m_utteranceLoader.ReindexIndicesForUtterances())
			{
				utteranceLoaderStub->m_lastError = utteranceLoaderStub->m_utteranceLoader.LastError();
				assert(false);
				return false;
			}
			break;
		}

		return true;
	}

	//-------------------------------------------------------------------------------------------------
	extern "C" const char* UtteranceLoader_LastError(void* utteranceLoader)
	{
		UtteranceLoaderExportsStub* utteranceLoaderStub = reinterpret_cast<UtteranceLoaderExportsStub*>(utteranceLoader);
		assert(utteranceLoaderStub);

		return utteranceLoaderStub->m_lastError.c_str();
	}
}
