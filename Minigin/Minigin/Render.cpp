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

Comp::RenderComp::RenderComp(const RenderComp& other)
	: Component{}
{
	for (std::shared_ptr<dae::Texture2D> pTexture : other.m_TexturesToRender)
	{
		//TODO: clean this up, i would say to just create a new empty container instead of copying the pointers
		//create a copy of the texture in the new render component
		m_TexturesToRender.push_back(pTexture);
	}
}

Comp::RenderComp::RenderComp(RenderComp&& other)
	: Component{}
{
	//move the pointers of the textures in the newly constructed render component
	for (std::shared_ptr<dae::Texture2D> pTexture : other.m_TexturesToRender)
	{
		m_TexturesToRender.push_back(pTexture);
	}
}

Comp::RenderComp& Comp::RenderComp::operator=(const RenderComp& other)
{
	for (std::shared_ptr<dae::Texture2D> pTexture : other.m_TexturesToRender)
	{
		//TODO: clean this up, i would say to just create a new empty container instead of copying the pointers
		//create a copy of the texture in the current render component
		m_TexturesToRender.push_back(pTexture);
	}

	return *this;
}

Comp::RenderComp& Comp::RenderComp::operator=(RenderComp&& other)
{
	//move the pointers of the textures to this render component
	for (std::shared_ptr<dae::Texture2D> pTexture : other.m_TexturesToRender)
	{
		m_TexturesToRender.push_back(pTexture);
	}

	return *this;
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

	//loop through all the textures we need to render and render them

	std::for_each(m_TexturesToRender.begin(), m_TexturesToRender.end(), 
		[this]
		(const std::shared_ptr<dae::Texture2D>& pTexture)
		{
			if (pTexture == nullptr)
				return;
			if (m_pTransformComp == nullptr)
				return;

			glm::vec3 pos{ m_pTransformComp->GetPosition() };

			dae::Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y);
		});
}

void Comp::RenderComp::AddTexture(const std::shared_ptr<dae::Texture2D>& pTexture)
{
	m_TexturesToRender.push_back(pTexture);
}

void Comp::RenderComp::RemoveTexture(const std::shared_ptr<dae::Texture2D>& pTexture)
{
	auto it = std::remove(m_TexturesToRender.begin(), m_TexturesToRender.end(), pTexture);
	m_TexturesToRender.erase(it);
}

void Comp::RenderComp::GetNeededComponents()
{
	if (m_pGameObject.lock())
		m_pTransformComp = m_pGameObject.lock()->GetComponent<Comp::TransformComp>();
}

bool Comp::RenderComp::HasAllComponents() const
{
	if (m_pTransformComp == nullptr)
		return false;
	return true;
}
