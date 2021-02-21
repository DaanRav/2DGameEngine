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

bool Component::IsAttachedToGameObject() const
{
	if(m_pGameObject.lock() == nullptr)
		return false;
	return true;
}
