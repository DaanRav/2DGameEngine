#include "MiniginPCH.h"
#include "Text.h"
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Render.h"

Comp::TextComp::TextComp()
	:Component{}
	, m_Font{nullptr}
{
	//if the text component has no data dont update it
	//and then it doesnt have a spot on the render component ether 
	m_NeedsUpdate = false;
}

Comp::TextComp::TextComp(const std::string& text, const std::string& fontFile, int fontSize)
	:Component{}
	,m_Text{text}
{
	m_Font = dae::ResourceManager::GetInstance().LoadFont(fontFile, fontSize);
	//update it at least once to create a texture on the render component
	m_NeedsUpdate = true;
}

void Comp::TextComp::Initialize()
{
	if (!IsAttachedToGameObject())
		return;

	GetNeededComponents();


}

void Comp::TextComp::Update()
{
	if (!HasAllComponents())
		return;

	if (m_NeedsUpdate)
	{
		//remove the old texture form the render component and add the new one
		if (m_pTexture)
			m_pRenderComp->RemoveTexture(m_pTexture);
		//create the new texture that needs to be rendered
		CreateTexture();
		//add the new texture to the render component so its rendered
		m_pRenderComp->AddTexture(m_pTexture);
	}
}

void Comp::TextComp::SetText(const std::string& newText)
{
	m_Text = newText;
	m_NeedsUpdate = true;
}

std::string Comp::TextComp::GetText() const
{
	return m_Text;
}

void Comp::TextComp::SetFont(const std::string& fontFile, int fontSize)
{
	m_Font = m_Font = dae::ResourceManager::GetInstance().LoadFont(fontFile, fontSize);
	m_NeedsUpdate = true;
}

void Comp::TextComp::SetColor(const glm::vec3& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}

void Comp::TextComp::GetNeededComponents()
{
	if (m_pGameObject.lock())
		m_pRenderComp = m_pGameObject.lock()->GetComponent<Comp::RenderComp>();
}

bool Comp::TextComp::HasAllComponents() const
{
	if (m_pRenderComp == nullptr)
		return false;
	return true;
}

void Comp::TextComp::CreateTexture()
{
	const SDL_Color SdlColor = { Uint8(m_Color.r * 255),Uint8(m_Color.g * 255),Uint8(m_Color.b * 255) };
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), SdlColor);
	if (surf == nullptr)
	{
		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	}
	auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	}
	SDL_FreeSurface(surf);

	m_pTexture = std::make_shared<dae::Texture2D>(texture);
}
