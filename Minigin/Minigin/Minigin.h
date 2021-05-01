#pragma once

class SoundSystem;

struct SDL_Window;
namespace dae
{
	class Minigin
	{
	public:
		void Initialize(const char* windowName, int windowWidth = 640, int windowHeight = 480);
		void LoadDemoScene() const;
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};
		SoundSystem* m_pSoundSystem{ nullptr };
	};
}