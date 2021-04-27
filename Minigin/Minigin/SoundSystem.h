#pragma once
#define UNREFERENCED_PARAMETER(P) (P)

class SoundSystem
{
public:
	virtual ~SoundSystem() = default;

	virtual void PlayMusic(const char* fileName, const float volume) = 0;
	virtual void PlaySound(const char* fileName, const float volume) = 0;
};

class NullSoundSystem final : public SoundSystem
{
private:
	void PlayMusic(const char* fileName, const float volume) override 
	{ 
		UNREFERENCED_PARAMETER(fileName);
		UNREFERENCED_PARAMETER(volume);
	};
	void PlaySound(const char* fileName, const float volume) override
	{
		UNREFERENCED_PARAMETER(fileName);
		UNREFERENCED_PARAMETER(volume);
	};
};

class SdlSoundSystem final : public SoundSystem
{
public:
	SdlSoundSystem();
	~SdlSoundSystem();

	void PlayMusic(const char* fileName, const float volume) override;
	void PlaySound(const char* fileName, const float volume) override;
private:

};

class LoggingSoundSystem final : public SoundSystem
{
public:
	LoggingSoundSystem(SoundSystem* ss, bool muted = false);
	~LoggingSoundSystem();
	
	void Mute() { m_Muted = true; };
	void UnMute() { m_Muted = false; };

	void PlayMusic(const char* fileName, const float volume) override;
	void PlaySound(const char* fileName, const float volume) override;
private:
	SoundSystem* m_pRealSs;
	bool m_Muted{ false };
};

