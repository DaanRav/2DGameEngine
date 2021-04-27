#include "SoundSystem.h"
#include "audio.c"
#include <iostream>

SdlSoundSystem::SdlSoundSystem()
{
	initAudio();
}

SdlSoundSystem::~SdlSoundSystem()
{
	endAudio();
}

void SdlSoundSystem::PlayMusic(const char* fileName, const float volume)
{
	playMusic(fileName, (int)volume);
}

void SdlSoundSystem::PlaySound(const char* fileName, const float volume)
{
	playSound(fileName, (int)volume);
}

LoggingSoundSystem::LoggingSoundSystem(SoundSystem* ss, bool muted)
	:m_pRealSs{ss}
	, m_Muted{muted}
{
}

void LoggingSoundSystem::PlayMusic(const char* fileName, const float volume)
{
	if (!m_Muted)
		m_pRealSs->PlayMusic(fileName, volume);

	std::cout << "LoggingSoundSystem: Playing music " << fileName << " at volume " << (int)volume << '\n';
}

void LoggingSoundSystem::PlaySound(const char* fileName, const float volume)
{
	if (!m_Muted)
		m_pRealSs->PlaySound(fileName, volume);

	std::cout << "LoggingSoundSystem: Playing sound " << fileName << " at volume " << (int)volume << '\n';
}
