#pragma once
#include <memory>

class GameObject;

class Component
{
public: 
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

	//TODO: make an initialize function here as well, to avoid setting a lot of vars in the update function
	virtual void FixedUpdate();
	virtual void Update();

	void SetGameObject(const std::weak_ptr<GameObject>& pGameObject);

	virtual CompType GetType() const { return CompType::baseComp; };
protected:
	virtual void GetNeededComponents() = 0;
	virtual bool HasAllComponents() const = 0;
	bool IsAttachedToGameObject() const;

	//TODO: make a vector here so the get needed comp function can be implemented here instead of having to make it in each component

	//the gameobject this  component is part of
	std::weak_ptr<GameObject> m_pGameObject{};
};

