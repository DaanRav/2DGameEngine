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

void GameObject::Initialize()
{
	for (std::shared_ptr<Component> pComponent : m_Components)
	{
		pComponent->SetGameObject(weak_from_this());
		pComponent->Initialize();
	}
}

void GameObject::FixedUpdate()
{
	for (std::shared_ptr<Component> pComponent : m_Components)
	{
		//dont update the render component here, we do it in the render function of the game object
		if (std::dynamic_pointer_cast<Comp::RenderComp>(pComponent))
			continue;

		pComponent->FixedUpdate();
	}
}

void GameObject::Update()
{
	for (std::shared_ptr<Component> pComponent : m_Components)
	{
		//dont update the render component here, we do it in the render function of the game object
		if (std::dynamic_pointer_cast<Comp::RenderComp>(pComponent))
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

void GameObject::AddComponent(std::shared_ptr<Component> pComponent)
{
	m_Components.push_back(pComponent);
}

void GameObject::SetFlag(const Flag& flag)
{
	m_Flag = flag;
}

GameObject::Flag GameObject::GetFlag() const
{
	return m_Flag;
}
