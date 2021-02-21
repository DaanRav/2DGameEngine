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

Comp::TransformComp::TransformComp(const TransformComp& other)
	: Component{}
	, m_Position{ other.m_Position }
{
}

Comp::TransformComp::TransformComp(TransformComp&& other)
	: Component{}
	, m_Position{ other.m_Position }
{
}

Comp::TransformComp& Comp::TransformComp::operator=(const TransformComp& other)
{
	m_Position = other.m_Position;
	return *this;
}

Comp::TransformComp& Comp::TransformComp::operator=(TransformComp&& other)
{
	m_Position = other.m_Position;
	return *this;
}

void Comp::TransformComp::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

glm::vec3 Comp::TransformComp::GetPosition() const
{
	return m_Position;
}
