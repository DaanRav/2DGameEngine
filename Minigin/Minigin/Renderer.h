#pragma once
#include "Singleton.h"

//there was a bug in the SDL_syswm.h that gave a weird warning to fix this i followed what they suggested here
//https://github.com/libsdl-org/SDL/issues/2891
//so it might be that this warning will reappear on a differnt device then mine

//imgui includes
#include "imgui.h"
#include "backends\imgui_impl_sdl.h"
#include "backends\imgui_impl_opengl2.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};

		//needed for imgui
		int GetOpenGlDriverIndex();

		SDL_Window* m_Window{};
		bool m_ShowDemo{ true };
	};
}

