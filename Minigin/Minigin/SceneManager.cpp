#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Initialize()
{
	for (auto& pScene : m_Scenes)
	{
		pScene->Initialize();
	}
}

void dae::SceneManager::FixedUpdate()
{
	for(auto& pScene : m_Scenes)
	{
		pScene->FixedUpdate();
	}
}

void dae::SceneManager::Update()
{
	for (auto& pScene : m_Scenes)
	{
		pScene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& pScene : m_Scenes)
	{
		pScene->Render();
	}
}

bool dae::SceneManager::HasScene() const
{
	if (m_Scenes.empty())
		return false;
	return true;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto pScene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(pScene);
	return *pScene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(const std::string& name) const
{
	auto it = std::find_if(m_Scenes.begin(), m_Scenes.end(), [name](std::shared_ptr<Scene> scene)
		{
			if (name == scene->GetName())
				return true;
			return false;
		});

	return *it;
}
