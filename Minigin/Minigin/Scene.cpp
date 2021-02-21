#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void Scene::FixedUpdate()
{
	for(auto& object : m_Objects)
	{
		if(object->GetFlag() == GameObject::Flag::active)
			object->FixedUpdate();
	}

	//removing the destroyed objects
	auto it = std::remove_if(m_Objects.begin(), m_Objects.end(), [](const std::shared_ptr<GameObject>& pObject)
		{
			if (pObject->GetFlag() == GameObject::Flag::destroyed)
				return true;
			return false;
		});

	m_Objects.erase(it, m_Objects.end());
}

void dae::Scene::Update()
{
	for (auto& object : m_Objects)
	{
		if (object->GetFlag() == GameObject::Flag::active)
			object->Update();
	}

	//removing the destroyed objects
	auto it = std::remove_if(m_Objects.begin(), m_Objects.end(), [](const std::shared_ptr<GameObject>& pObject)
		{
			if (pObject->GetFlag() == GameObject::Flag::destroyed)
				return true;
			return false;
		});

	m_Objects.erase(it, m_Objects.end());
}

void Scene::Render() const
{
	//look for the render component of the object and update that one

	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

