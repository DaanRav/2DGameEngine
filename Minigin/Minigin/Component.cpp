#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

void Component::FixedUpdate()
{
}

void Component::Update()
{
}

void Component::SetGameObject(const std::weak_ptr<GameObject>& pGameObject)
{
	m_pGameObject = pGameObject;
}

void Component::GetNeededComponents()
{
	if (m_pGameObject.lock())
		m_pTransformComp = m_pGameObject.lock()->GetTransform();
}

bool Component::IsAttachedToGameObject() const
{
	if(m_pGameObject.lock() == nullptr)
		return false;
	return true;
}
