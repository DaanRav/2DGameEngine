#pragma once
#include <algorithm>
#include <typeinfo>
#include "Component.h"

class Component;
enum class Component::CompType;

class GameObject final : public std::enable_shared_from_this<GameObject>
{
public:
	enum class Flag
	{
		active, destroyed
	};

	GameObject() = default;
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void FixedUpdate();
	void Update();
	void Render();

	void AddComponent(std::shared_ptr<Component> component);
	void RemoveComponent(const Component::CompType& componentType);

	std::shared_ptr<Component> GetComponent(const Component::CompType& componentType) const;
	std::vector<std::shared_ptr<Component>> GetComponents(const Component::CompType& componentType) const;

	void SetFlag(const Flag& flag);
	Flag GetFlag() const;

private:
	std::vector<std::shared_ptr<Component>> m_Components{};
	Flag m_Flag{ Flag::active };
};

