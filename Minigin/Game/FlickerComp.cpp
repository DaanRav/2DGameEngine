#include "FlickerComp.h"
#include "GameObject.h"
#include "Render.h"
#include "Timer.h"

Comp::FlickerComp::FlickerComp(float interval)
	:Component{}
	, m_Interval{interval}
{
}

void Comp::FlickerComp::Initialize()
{
	if (!IsAttachedToGameObject())
		return;

	GetNeededComponents();
}

void Comp::FlickerComp::Update()
{
	if (!HasAllComponents())
		return;

	m_Counter += (float)dae::Timer::GetInstance().GetDeltaTime();

	if (m_Counter >= m_Interval)
	{
		m_Counter = 0.f;
		m_pRenderComp->SetEnable(!m_pRenderComp->IsEnabled());
	}


}

void Comp::FlickerComp::GetNeededComponents()
{
	if (m_pGameObject.lock())
		m_pRenderComp = m_pGameObject.lock()->GetComponent<Comp::RenderComp>();
}

bool Comp::FlickerComp::HasAllComponents() const
{
	if (!m_pRenderComp)
		return false;

	return true;
}
