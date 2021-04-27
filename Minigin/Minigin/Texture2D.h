#pragma once
#include <vec4.hpp>
#include <vec2.hpp>

struct SDL_Texture;

namespace dae
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		void SetSrcRect(const glm::vec4& srcRect);
		glm::vec4 GetSrcRect() const;
		void SetDestSize(const glm::vec2& destSize);
		glm::vec2 GetDestSize() const;

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
	private:
		SDL_Texture* m_Texture;
		glm::vec4 m_SrcRect;
		glm::vec2 m_DestSize{};
	};
}
