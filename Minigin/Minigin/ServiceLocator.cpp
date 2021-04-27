#include "ServiceLocator.h"
#include "SoundSystem.h"

NullSoundSystem ServiceLocator::m_DefaultSs{};
SoundSystem* ServiceLocator::m_SsInstance = &ServiceLocator::m_DefaultSs;

SoundSystem& ServiceLocator::GetSoundSystem()
{
	return *m_SsInstance;
}

void ServiceLocator::RegisterSoundSystem(SoundSystem* ss)
{
	if (ss == nullptr)
	{
		m_SsInstance = &m_DefaultSs;
	}
	else
		m_SsInstance = ss;
}
