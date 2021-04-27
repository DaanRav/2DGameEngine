#pragma once
#include "Singleton.h"

class SoundSystem;
class NullSoundSystem;

using namespace dae;

class ServiceLocator final : public Singleton<ServiceLocator>
{
public:
	//sound
	static SoundSystem& GetSoundSystem();
	static void RegisterSoundSystem(SoundSystem* ss);
	//input
private:
	friend class Singleton<ServiceLocator>;
	ServiceLocator() = default;

	//sound
	static SoundSystem* m_SsInstance;
	static NullSoundSystem m_DefaultSs;
	//input
};

