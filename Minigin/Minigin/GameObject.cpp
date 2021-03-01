#include "MiniginPCH.h"
#include <memory>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"
#include "Render.h"

GameObject::~GameObject()
{
}

void GameObject::FixedUpdate()
{
	for (std::shared_ptr<Component> pComponent : m_Components)
	{
		//dont update the render component here, we do it in the render function of the game object
		if (pComponent->GetType() == Component::CompType::renderComp)
			continue;

		pComponent->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (std::shared_ptr<Component> pComponent : m_Components)
	{
		//dont update the render component here, we do it in the render function of the game object
		if (pComponent->GetType() == Component::CompType::renderComp)
			continue;

		pComponent->Update();
	}
}

void GameObject::Render()
{
	std::shared_ptr<Component> renderComp{ GetComponent<Comp::RenderComp>() };

	if (renderComp == nullptr)
		return;

	renderComp->Update();
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	component->SetGameObject(weak_from_this());
	m_Components.push_back(component);
}

void GameObject::SetFlag(const Flag& flag)
{
	m_Flag = flag;
}

GameObject::Flag GameObject::GetFlag() const
{
	return m_Flag;
}
