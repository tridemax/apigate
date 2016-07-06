#pragma once


namespace apigate
{
	//-------------------------------------------------------------------------------------------------
	/// AudioconvertHandler
	//-------------------------------------------------------------------------------------------------
	class AudioconvertHandler : public proxygen::RequestHandler
	{
	private:
		typedef audioconvert::AudioConverter AudioConverter;

	private:
		AudioConverter				m_audioConverter;
		audioconvert::AudioFormat	m_inputFormat;
		audioconvert::AudioFormat	m_outputFormat;
		uint32_t					m_sampleRate;

	public:
		virtual void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;
		virtual void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;
		virtual void onEOM() noexcept override;
		virtual void onUpgrade(proxygen::UpgradeProtocol protocol) noexcept override;
		virtual void requestComplete() noexcept override;
		virtual void onError(proxygen::ProxygenError error) noexcept override;

	private:
	};
}
