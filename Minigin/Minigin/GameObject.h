#pragma once
#include <algorithm>
#include <typeinfo>
#include "Component.h"
#include <vector>

class Component;

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
	
	//TODO: also implement a remove comp, but will probably have to have weak ptrs in the comp to other comp
	template<typename T>
	std::shared_ptr<T> GetComponent() const
	{
		auto it = std::find_if(m_Components.begin(), m_Components.end(), [](const std::shared_ptr<Component>& pComponent)
			{
				if (std::dynamic_pointer_cast<T>(pComponent))
					return true;
				return false;
			});

		if (it == m_Components.end())
			return std::shared_ptr<T>(nullptr);

		return std::dynamic_pointer_cast<T>(*it);
	};

	void SetFlag(const Flag& flag);
	Flag GetFlag() const;

private:
	std::vector<std::shared_ptr<Component>> m_Components{};
	Flag m_Flag{ Flag::active };
};

