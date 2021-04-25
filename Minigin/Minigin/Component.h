#pragma once
#include <memory>

class GameObject;

class Component
{
public: 
	//TODO: remove this struct and just work with the type of the components instead
	enum class CompType
	{
		baseComp, transform, texture, text, fpsCounter, renderComp, inputTest
	};

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

	virtual CompType GetType() const { return CompType::baseComp; };
protected:
	virtual void GetNeededComponents() = 0;
	virtual bool HasAllComponents() const = 0;
	bool IsAttachedToGameObject() const;

	//the gameobject this  component is part of
	std::weak_ptr<GameObject> m_pGameObject{};
};

