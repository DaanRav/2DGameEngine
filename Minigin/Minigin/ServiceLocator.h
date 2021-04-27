#pragma once

class SoundSystem;
class NullSoundSystem;

class ServiceLocator final
{
public:
	//sound
	static SoundSystem& GetSoundSystem();
	static void RegisterSoundSystem(SoundSystem* ss);
	//input
private:
	//sound
	static SoundSystem* m_SsInstance;
	static NullSoundSystem m_DefaultSs;
	//input
};

