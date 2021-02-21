#pragma once
#include <memory>

class GameObject;

class Component
{
public: 
	enum class CompType
	{
		baseComp, transform, texture, text, fpsCounter, renderComp
	};

	Component() = default;
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void FixedUpdate();
	virtual void Update();

	void SetGameObject(const std::weak_ptr<GameObject>& pGameObject);

	virtual CompType GetType() const { return CompType::baseComp; };
protected:
	virtual void GetNeededComponents() = 0;
	virtual bool HasAllComponents() const = 0;
	bool IsAttachedToGameObject() const;

	//all needed components for this one to work
	std::weak_ptr<GameObject> m_pGameObject{};
};

