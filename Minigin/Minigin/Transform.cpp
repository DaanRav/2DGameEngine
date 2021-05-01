#include "MiniginPCH.h"
#include "Transform.h"
#include "GameObject.h"

Comp::TransformComp::TransformComp()
	:Component{}
{
}

Comp::TransformComp::TransformComp(const glm::vec3& pos)
	:Component{}
	, m_Position{pos}
{
}

void Comp::TransformComp::Initialize()
{
	if (!IsAttachedToGameObject())
		return;

	GetNeededComponents();
}

void Comp::TransformComp::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

glm::vec3 Comp::TransformComp::GetPosition() const
{
	return m_Position;
}

void Comp::TransformComp::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
}

glm::vec3 Comp::TransformComp::GetScale() const
{
	return m_Scale;
}
