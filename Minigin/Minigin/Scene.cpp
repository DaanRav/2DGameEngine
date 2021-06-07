#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

std::shared_ptr<GameObject> dae::Scene::GetGameObject(const std::wstring& name)
{
	auto it = std::find_if(m_Objects.begin(), m_Objects.end(), [name](const std::shared_ptr<GameObject>& object)
		{
			if (object->GetName() == name)
				return true;
			return false;
		});

	return *it;
}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::Initialize()
{
	for (auto& pObject : m_Objects)
	{
		pObject->Initialize();
	}
}

void Scene::FixedUpdate()
{
	for(auto& pObject : m_Objects)
	{
		if(pObject->GetFlag() == GameObject::Flag::active)
			pObject->FixedUpdate();
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
	for (auto& pObject : m_Objects)
	{
		if (pObject->GetFlag() == GameObject::Flag::active)
			pObject->Update();
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

	for (const auto& pObject : m_Objects)
	{
		pObject->Render();
	}
}

