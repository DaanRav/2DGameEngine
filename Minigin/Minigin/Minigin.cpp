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
#include "InputTestComp.h"
#include "Benchmarking.h"

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

	//background
	auto go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<Comp::TransformComp>(glm::vec3{ 0,0,0 }));
	go->AddComponent(std::make_shared<Comp::TextureComp>("background.jpg"));
	go->AddComponent(std::make_shared<Comp::RenderComp>());
	scene.Add(go);

	//dae logo
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<Comp::TransformComp>(glm::vec3{216,180,0}));
	go->AddComponent(std::make_shared<Comp::TextureComp>("logo.png"));
	go->AddComponent(std::make_shared<Comp::RenderComp>());
	scene.Add(go);
	
	//assignment text
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<Comp::TransformComp>(glm::vec3{80,20,0}));
	go->AddComponent(std::make_shared<Comp::TextComp>("Programming 4 Assignment","Lingua.otf",36));
	go->AddComponent(std::make_shared<Comp::RenderComp>());
	scene.Add(go);
	
	//fps game object
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<Comp::TransformComp>(glm::vec3{0,0,0}));
	go->AddComponent(std::make_shared<Comp::TextComp>("00 FPS","Lingua.otf",20));
	go->GetComponent<Comp::TextComp>()->SetColor(glm::vec3{ 0.0f,1.0f,0.0f });
	go->AddComponent(std::make_shared<Comp::FpsCounterComp>());
	go->AddComponent(std::make_shared<Comp::RenderComp>());
	scene.Add(go);
	
	//creating text to check the input manager
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<Comp::TransformComp>(glm::vec3{20,400,0}));
	go->AddComponent(std::make_shared<Comp::TextComp>("No Input Given","Lingua.otf",20));
	go->AddComponent(std::make_shared<Comp::RenderComp>());
	go->AddComponent(std::make_shared<Comp::InputTestComp>());
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
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		//initializing everything in the game
		sceneManager.Initialize();

		bool doContinue = true;
		double lag = 0.0f;
		Timer::GetInstance().Start();
		while (doContinue)
		{
			Timer::GetInstance().Update();
			lag += Timer::GetInstance().GetDeltaTime();
			
			doContinue = input.ProcessInput();

			while (lag >= Timer::GetInstance().GetFixedDeltaTime())
			{
				sceneManager.FixedUpdate();
				lag -= Timer::GetInstance().GetFixedDeltaTime();
			}

			sceneManager.Update();

			renderer.Render();
			
		}
	}

	Cleanup();
}
