#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Texture.h"
#include "Transform.h"
#include "Text.h"
#include "Timer.h"
#include "FpsCounter.h"
#include "Render.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{	
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	
	auto go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<Comp::TransformComp>(Comp::TransformComp{ glm::vec3{0,0,0} }));
	go->AddComponent(std::make_shared<Comp::TextureComp>(Comp::TextureComp{ "background.jpg" }));
	go->AddComponent(std::make_shared<Comp::RenderComp>(Comp::RenderComp{}));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<Comp::TransformComp>(Comp::TransformComp{ glm::vec3{216,180,0} }));
	go->AddComponent(std::make_shared<Comp::TextureComp>(Comp::TextureComp{ "logo.png" }));
	go->AddComponent(std::make_shared<Comp::RenderComp>(Comp::RenderComp{}));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<Comp::TransformComp>(Comp::TransformComp{glm::vec3{80,20,0} }));
	go->AddComponent(std::make_shared<Comp::TextComp>(Comp::TextComp{"Programming 4 Assignment","Lingua.otf",36 }));
	go->AddComponent(std::make_shared<Comp::RenderComp>(Comp::RenderComp{}));
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<Comp::TransformComp>(Comp::TransformComp{glm::vec3{0,0,0} }));
	go->AddComponent(std::make_shared<Comp::TextComp>(Comp::TextComp{ "00 FPS","Lingua.otf",20 }));
	std::dynamic_pointer_cast<Comp::TextComp>(go->GetComponent(Component::CompType::text))->SetColor(glm::vec3{ 0.0f,1.0f,0.0f });
	go->AddComponent(std::make_shared<Comp::FpsCounterComp>(Comp::FpsCounterComp{}));
	go->AddComponent(std::make_shared<Comp::RenderComp>(Comp::RenderComp{}));
	scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		//creating timer
		float fixedDeltaTime{ 0.02f };
		pTimer = new Timer{ fixedDeltaTime };

		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		double lag = 0.0f;
		pTimer->Start();
		while (doContinue)
		{
			pTimer->Update();
			lag += pTimer->GetDeltaTime();
			
			doContinue = input.ProcessInput();
			input.HandleInput();

			while (lag >= pTimer->GetFixedDeltaTime())
			{
				sceneManager.FixedUpdate();
				lag -= pTimer->GetFixedDeltaTime();
			}

			sceneManager.Update();

			renderer.Render();
			
		}
	}
	delete pTimer;
	pTimer = nullptr;

	Cleanup();
}
