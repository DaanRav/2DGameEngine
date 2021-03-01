#include "MiniginPCH.h"
#include <memory>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"

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
	std::shared_ptr<Component> renderComp{ GetComponent(Component::CompType::renderComp) };

	if (renderComp == nullptr)
		return;

	renderComp->Update();
}

//TODO: make this a templated functions so i dont have to cast it each time i do it to get a component
void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	component->SetGameObject(weak_from_this());
	m_Components.push_back(component);
}

//TODO: this will probably give some errors when used, maybe fix those later
void GameObject::RemoveComponent(const Component::CompType& componentType)
{
	auto it = std::remove_if(m_Components.begin(), m_Components.end(), [componentType](const std::shared_ptr<Component>& pComp) 
		{
			if (componentType == pComp->GetType())
				return true;
			return false;
		});
	m_Components.erase(it, m_Components.end());
}

std::shared_ptr<Component> GameObject::GetComponent(const Component::CompType& componentType) const
{
	if (m_Components.size() == 0)
		return nullptr;

	for (std::shared_ptr<Component> comp : m_Components)
	{
		if (comp->GetType() == componentType)
			return comp;
	}

	return nullptr;
}

std::vector<std::shared_ptr<Component>> GameObject::GetComponents(const Component::CompType& componentType) const
{
	std::vector<std::shared_ptr<Component>> returnVector{};

	for (std::shared_ptr<Component> comp : m_Components)
	{
		if (comp->GetType() == componentType)
			returnVector.push_back(comp);
	}

	return returnVector;
}

void GameObject::SetFlag(const Flag& flag)
{
	m_Flag = flag;
}

GameObject::Flag GameObject::GetFlag() const
{
	return m_Flag;
}
