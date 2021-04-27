#pragma once
#include "Singleton.h"
#include <vec4.hpp>

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
		void RenderTexture(const Texture2D& texture, const glm::vec4& srcRect, float x, float y) const;
		void RenderTexture(const Texture2D& texture, const glm::vec4& srcRect, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};

		//needed for imgui
		int GetOpenGlDriverIndex();

		SDL_Window* m_Window{};
		bool m_ShowDemo{ true };
	};
}

