#include "MiniginPCH.h"
#include "Render.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include <SDL.h>
#include <SDL_ttf.h>

Comp::RenderComp::RenderComp()
	:Component{}
{
}

void Comp::RenderComp::Initialize()
{
	if (!IsAttachedToGameObject())
		return;

	GetNeededComponents();
}

void Comp::RenderComp::Update()
{
	if (!HasAllComponents())
		return;

	if (!m_Enable)
		return;

	//loop through all the textures we need to render and render them
	std::for_each(m_TexturesToRender.begin(), m_TexturesToRender.end(), 
		[this]
		(const std::shared_ptr<dae::Texture2D>& pTexture)
		{
			if (pTexture == nullptr)
				return;

			dae::Renderer::GetInstance().RenderTexture(*pTexture, pTexture->GetSrcRect()
				, pTexture->GetDestRect().x
				, pTexture->GetDestRect().y
				, pTexture->GetDestRect().z
				, pTexture->GetDestRect().w);
		
		});
}

void Comp::RenderComp::AddTexture(const std::shared_ptr<dae::Texture2D>& pTexture)
{
	m_TexturesToRender.push_back(pTexture);
}

void Comp::RenderComp::RemoveTextures(const std::shared_ptr<dae::Texture2D>& pTexture)
{
	auto it = std::remove(m_TexturesToRender.begin(), m_TexturesToRender.end(), pTexture);
	m_TexturesToRender.erase(it);
}

void Comp::RenderComp::GetNeededComponents()
{
}

bool Comp::RenderComp::HasAllComponents() const
{
	return true;
}
