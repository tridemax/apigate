#pragma once

#include "UtteranceLoaderAPI.h"


namespace TrainingDataProvider
{
	//-------------------------------------------------------------------------------------------------
	/// IdVector
	//-------------------------------------------------------------------------------------------------
	typedef std::vector<uint64_t> IdVector;

	//-------------------------------------------------------------------------------------------------
	/// UtteranceFilter
	//-------------------------------------------------------------------------------------------------
	class UtteranceFilter : public ISerializableStruct
	{
	public:
		uint32_t					m_durationMin;
		uint32_t					m_durationMax;
		std::vector<Language>		m_languageList;
		bool						m_mustHaveTranscribes;

	public:
		inline UtteranceFilter() : m_durationMin(0u), m_durationMax(0u), m_mustHaveTranscribes(false)
		{
		}

		template <class SerializerType>
		inline bool Serialize(SerializerType* serializer)
		{
			bool result = true;

			result &= serializer->Value("durationMin", m_durationMin);
			result &= serializer->Value("durationMax", m_durationMax);
			result &= serializer->Value("languageList", m_languageList);
			result &= serializer->Value("mustHaveTranscribes", m_mustHaveTranscribes);

			return result;
		}
	};

	//-------------------------------------------------------------------------------------------------
	/// Utterance
	//-------------------------------------------------------------------------------------------------
	class Utterance : public ISerializableStruct
	{
	public:
		uint64_t					m_utteranceId;
		std::vector<byte>			m_content;
		AudioFormat					m_audioFormat;
		uint32_t					m_timeStart;
		uint32_t					m_timeDuration;
		Language					m_language;
		std::string					m_transcribe;
	};

	//-------------------------------------------------------------------------------------------------
	/// AudioFormatStringifier
	//-------------------------------------------------------------------------------------------------
	class AudioFormatStringifier
	{
	public:
		static const char			AudioWave_String[];
		static const char			AudioMp3_String[];
		static const char			AudioAac_String[];
		static const char			AudioFlac_String[];
		static const char			AudioOpus_String[];
		static const char			AudioVorbis_String[];

	public:
		static inline AudioFormat FromString(const std::string& audioFormat);
		static inline const char* ToString(AudioFormat audioFormat);
	};

	//-------------------------------------------------------------------------------------------------
	DECLSPEC_SELECTANY const char AudioFormatStringifier::AudioWave_String[] = "wave";
	DECLSPEC_SELECTANY const char AudioFormatStringifier::AudioMp3_String[] = "mp3";
	DECLSPEC_SELECTANY const char AudioFormatStringifier::AudioAac_String[] = "aac";
	DECLSPEC_SELECTANY const char AudioFormatStringifier::AudioFlac_String[] = "flac";
	DECLSPEC_SELECTANY const char AudioFormatStringifier::AudioOpus_String[] = "opus";
	DECLSPEC_SELECTANY const char AudioFormatStringifier::AudioVorbis_String[] = "vorbis";

	//-------------------------------------------------------------------------------------------------
	inline AudioFormat AudioFormatStringifier::FromString(const std::string& audioFormat)
	{
		if (memcmp(audioFormat.data(), AudioWave_String, std::min(audioFormat.size(), sizeof(AudioWave_String) - 1u)) == 0)
		{
			return AudioFormat::AudioWave;
		}
		if (memcmp(audioFormat.data(), AudioFlac_String, std::min(audioFormat.size(), sizeof(AudioFlac_String) - 1u)) == 0)
		{
			return AudioFormat::AudioFlac;
		}
		return AudioFormat::AudioUnknown;
	}

	//-------------------------------------------------------------------------------------------------
	inline const char* AudioFormatStringifier::ToString(AudioFormat audioFormat)
	{
		switch (audioFormat)
		{
		case AudioFormat::AudioWave:
			return AudioWave_String;
		case AudioFormat::AudioMp3:
			return AudioMp3_String;
		case AudioFormat::AudioAac:
			return AudioAac_String;
		case AudioFormat::AudioFlac:
			return AudioFlac_String;
		case AudioFormat::AudioOpus:
			return AudioOpus_String;
		case AudioFormat::AudioVorbis:
			return AudioVorbis_String;
		}
		return "";
	}

	//-------------------------------------------------------------------------------------------------
	/// LanguageStringifier
	//-------------------------------------------------------------------------------------------------
	class LanguageStringifier
	{
	public:
		static const char			enUS_String[];
		static const char			deDE_String[];
		static const char			frFR_String[];
		static const char			esES_String[];
		static const char			itIT_String[];
		static const char			arSA_String[];
		static const char			heIL_String[];
		static const char			plPL_String[];
		static const char			ruRU_String[];
		static const char			ukUA_String[];
		static const char			trTR_String[];

	public:
		static inline Language FromString(const std::string& language);
		static inline const char* ToString(Language language);
	};

	//-------------------------------------------------------------------------------------------------
	DECLSPEC_SELECTANY const char LanguageStringifier::enUS_String[] = "en-US";
	DECLSPEC_SELECTANY const char LanguageStringifier::deDE_String[] = "de-DE";
	DECLSPEC_SELECTANY const char LanguageStringifier::frFR_String[] = "fr-FR";
	DECLSPEC_SELECTANY const char LanguageStringifier::esES_String[] = "es-ES";
	DECLSPEC_SELECTANY const char LanguageStringifier::itIT_String[] = "it-IT";
	DECLSPEC_SELECTANY const char LanguageStringifier::arSA_String[] = "ar-SA";
	DECLSPEC_SELECTANY const char LanguageStringifier::heIL_String[] = "he-IL";
	DECLSPEC_SELECTANY const char LanguageStringifier::plPL_String[] = "pl-PL";
	DECLSPEC_SELECTANY const char LanguageStringifier::ruRU_String[] = "ru-RU";
	DECLSPEC_SELECTANY const char LanguageStringifier::ukUA_String[] = "uk-UA";
	DECLSPEC_SELECTANY const char LanguageStringifier::trTR_String[] = "tr-TR";

	//-------------------------------------------------------------------------------------------------
	inline Language LanguageStringifier::FromString(const std::string& language)
	{
		if (memcmp(language.data(), enUS_String, std::min(language.size(), sizeof(enUS_String) - 1u)) == 0)
		{
			return Language::enUS;
		}
		return Language::LanguageUnknown;
	}

	//-------------------------------------------------------------------------------------------------
	inline const char* LanguageStringifier::ToString(Language language)
	{
		switch (language)
		{
		case Language::enUS:
			return enUS_String;
		case Language::deDE:
			return deDE_String;
		case Language::frFR:
			return frFR_String;
		case Language::esES:
			return esES_String;
		case Language::itIT:
			return itIT_String;
		case Language::arSA:
			return arSA_String;
		case Language::heIL:
			return heIL_String;
		case Language::plPL:
			return plPL_String;
		case Language::ruRU:
			return ruRU_String;
		case Language::ukUA:
			return ukUA_String;
		case Language::trTR:
			return trTR_String;
		}
		return "";
	}
}
