#include "MiniginPCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);
}

void dae::Texture2D::SetSrcRect(const glm::vec4& srcRect)
{
	m_SrcRect = srcRect;
}

glm::vec4 dae::Texture2D::GetSrcRect() const
{
	return m_SrcRect;
}

void dae::Texture2D::SetDestSize(const glm::vec2& destSize)
{
	m_DestSize = destSize;
}

glm::vec2 dae::Texture2D::GetDestSize() const
{
	return m_DestSize;
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;

	int textureWidth{};
	int textureHeight{};

	SDL_QueryTexture(m_Texture, nullptr, nullptr, &textureWidth, &textureHeight);

	//as a default set the dest rect and the src rect to the size of the texture
	m_DestSize.x = (float)textureWidth;
	m_DestSize.y = (float)textureHeight;

	m_SrcRect.x = 0;
	m_SrcRect.y = 0;
	m_SrcRect.z = (float)textureWidth;
	m_SrcRect.w = (float)textureHeight;
}
