#include "MiniginPCH.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Render.h"

Comp::TextureComp::TextureComp()
	:Component{}
{
	GetNeededComponents();
}

Comp::TextureComp::TextureComp(const std::string& fileName)
	: Component{}
	, m_FileName{ fileName }
{
	GetNeededComponents();

	CreateTexture();
	m_SrcRect = m_pTexture->GetSrcRect();
	m_DestRect = m_pTexture->GetDestRect();
}

void Comp::TextureComp::Initialize()
{
	if (!IsAttachedToGameObject())
		return;

	GetNeededComponents();

	if (!HasAllComponents())
		return;

	if (!m_FileName.empty())
	{
		CreateTexture();
		//add the new texture to the render component so its rendered
		m_pRenderComp->AddTexture(m_pTexture);
	}
}

void Comp::TextureComp::Update()
{
	if (!HasAllComponents())
		return;

	if (m_NeedsUpdate)
	{
		//remove the old texture form the render component and add the new one
		if (m_pTexture)
			m_pRenderComp->RemoveTextures(m_pTexture);
		//create the new texture that needs to be rendered
		CreateTexture();
		m_pTexture->SetSrcRect(m_SrcRect);

		glm::vec4 destRect{};
		destRect.x = m_DestRect.x + m_pTransformComp->GetPosition().x;
		destRect.y = m_DestRect.y + m_pTransformComp->GetPosition().y;
		destRect.z = m_DestRect.z * m_pTransformComp->GetScale().x;
		destRect.w = m_DestRect.w * m_pTransformComp->GetScale().y;

		m_pTexture->SetDestRect(destRect);
		//add the new texture to the render component so its rendered
		m_pRenderComp->AddTexture(m_pTexture);
	}
}

void Comp::TextureComp::SetTexture(const std::string& fileName)
{
	m_FileName = fileName;
	m_NeedsUpdate = true;
}

void Comp::TextureComp::SetSrcRect(const glm::vec4& srcRect)
{
	m_SrcRect = srcRect;
	m_NeedsUpdate = true;
}

void Comp::TextureComp::SetDestRect(const glm::vec4& destRect)
{
	m_DestRect = destRect;
	m_NeedsUpdate = true;
}

glm::vec2 Comp::TextureComp::GetTexSize() const
{
	if(m_pTexture)
		return m_pTexture->GetDestRect();

	return glm::vec2{};
}

void Comp::TextureComp::GetNeededComponents()
{
	Component::GetNeededComponents();

	if(m_pGameObject.lock())
		m_pRenderComp = m_pGameObject.lock()->GetComponent<Comp::RenderComp>();
}

bool Comp::TextureComp::HasAllComponents() const
{
	if (m_pRenderComp == nullptr)
		return false;
	return true;
}

void Comp::TextureComp::CreateTexture()
{
	m_pTexture = dae::ResourceManager::GetInstance().LoadTexture(m_FileName);
	m_NeedsUpdate = true;
}
