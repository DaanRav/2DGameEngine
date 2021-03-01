#include "MiniginPCH.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Render.h"

Comp::TextureComp::TextureComp()
	:Component{}
{
	GetNeededComponents();
	//if it doesnt have anything dont update it
	m_NeedsUpdate = false;
}

Comp::TextureComp::TextureComp(const std::string& fileName)
	: Component{}
	, m_FileName{ fileName }
{
	GetNeededComponents();
	//update it to create the texture in the render component
	m_NeedsUpdate = true;
}

Comp::TextureComp::TextureComp(const TextureComp& other)
	:Component{}
	, m_FileName{other.m_FileName}
	, m_NeedsUpdate{true}
{
}

Comp::TextureComp::TextureComp(TextureComp&& other)
	: Component{}
	, m_FileName{other.m_FileName}
	, m_NeedsUpdate{ true }
{
}

Comp::TextureComp& Comp::TextureComp::operator=(const TextureComp& other)
{
	m_FileName = other.m_FileName;
	m_NeedsUpdate = true;

	return *this;
}

Comp::TextureComp& Comp::TextureComp::operator=(TextureComp&& other)
{
	m_FileName = other.m_FileName;
	m_NeedsUpdate = true;

	return *this;
}

void Comp::TextureComp::Update()
{
	//check if the component can update, if he has all he needs and is attached to a gameObject
	if (!IsAttachedToGameObject())
		return;
	//getting the components if needed
	if (!HasAllComponents())
		GetNeededComponents();
	//checking again if you got all components this time
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
