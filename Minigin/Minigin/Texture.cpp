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
			m_pRenderComp->RemoveTexture(m_pTexture);
		//create the new texture that needs to be rendered
		CreateTexture();
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
	m_pTexture->SetSrcRect( srcRect );
}

void Comp::TextureComp::SetSize(const glm::vec2& size)
{
	m_pTexture->SetDestSize(size);
}

void Comp::TextureComp::GetNeededComponents()
{
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
}
