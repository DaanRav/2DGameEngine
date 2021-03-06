#pragma once
#include <memory>

class GameObject;

namespace Comp
{
	class TransformComp;
}

class Component
{
public: 
	Component() = default;
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) = delete;

	virtual void Initialize() = 0;
	virtual void FixedUpdate();
	virtual void Update();

	void SetGameObject(const std::weak_ptr<GameObject>& pGameObject);

protected:
	virtual void GetNeededComponents();
	virtual bool HasAllComponents() const = 0;
	bool IsAttachedToGameObject() const;

	std::shared_ptr<Comp::TransformComp> m_pTransformComp;

	//the gameobject this  component is part of
	std::weak_ptr<GameObject> m_pGameObject{};
};

