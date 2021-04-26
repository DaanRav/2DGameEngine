#include "MiniginPCH.h"
#include "FpsCounter.h"
#include "Timer.h"
#include "Text.h"
#include "GameObject.h"
#include <string>

Comp::FpsCounterComp::FpsCounterComp()
	:Component{}
{
}

void Comp::FpsCounterComp::Initialize()
{
	//check if the component is attached to a game object
	if (!IsAttachedToGameObject())
		return;

	//getting the components needed for this component
	GetNeededComponents();
}

void Comp::FpsCounterComp::Update()
{
	//checking if you got all components before updating
	if (!HasAllComponents())
		return;

	m_AverageFps += int(1 / dae::Timer::GetInstance().GetDeltaTime());
	m_SampleSize++;
	m_RefreshTime += float(dae::Timer::GetInstance().GetDeltaTime());

	if (m_RefreshTime >= m_RefreshRate)
	{
		std::string newText{ std::to_string(int(m_AverageFps / m_SampleSize)) + " FPS"};

		if (m_pTextComp != nullptr )	
			if(m_pTextComp->GetText() != newText)
				m_pTextComp->SetText(newText);

		m_AverageFps = 0;
		m_SampleSize = 0;
		m_RefreshTime = 0.f;
	}
}

void Comp::FpsCounterComp::GetNeededComponents()
{
	if (m_pGameObject.lock())
		m_pTextComp = m_pGameObject.lock()->GetComponent<Comp::TextComp>();
}

bool Comp::FpsCounterComp::HasAllComponents() const
{
	if (m_pTextComp == nullptr)
		return false;
	return true;
}
