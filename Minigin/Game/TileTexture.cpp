#include "TileTexture.h"
#include <ResourceManager.h>
#include "HexGrid.h"
#include <Render.h>
#include <Transform.h>
#include <GameObject.h>
#include <Texture2D.h>

Comp::TileTexture::TileTexture(const std::string& filePath)
	:m_FileName{filePath}
{
	GetNeededComponents();
	m_NeedsUpdate = true;
}

void Comp::TileTexture::Initialize()
{
	if(!HasAllComponents())
		GetNeededComponents();
}

void Comp::TileTexture::Update()
{
	if (!HasAllComponents())
		return;
	if (!m_NeedsUpdate)
		return;

	std::vector<std::vector<bool>> grid = m_pHexGridComp->GetGrid();

	//remove the old textures form the render component and add the new ones
	if (m_pTileTexture)
		m_pRenderComp->RemoveTextures(m_pTileTexture);

	for (int i{}; i< m_pHexGridComp->GetGridDimentions().x;++i)
	{
		for (int j{}; j<m_pHexGridComp->GetGridDimentions().y; j++)
		{
			//check if the current tile is a valid tile
			if (grid.at(i).at(j))
			{
				glm::vec4 destRect{ m_pHexGridComp->AxialToPxl(glm::vec2{i,j})
					,m_pHexGridComp->GetTileSize().x * m_pTransformComp->GetScale().x
				,m_pHexGridComp->GetTileSize().y * m_pTransformComp->GetScale().y };

				//create the new texture that needs to be rendered
				CreateTexture();
				m_pTileTexture->SetSrcRect(m_SrcRect);
				m_pTileTexture->SetDestRect(destRect);
				//add the new texture to the render component so its rendered
				m_pRenderComp->AddTexture(m_pTileTexture);
			}
		}
	}

	m_NeedsUpdate = false;
}

void Comp::TileTexture::SetSrcRect(const glm::vec4& srcRect)
{
	m_SrcRect = srcRect;
	m_NeedsUpdate = true;
}

void Comp::TileTexture::GetNeededComponents()
{
	Component::GetNeededComponents();

	if (m_pGameObject.lock())
	{
		m_pRenderComp = m_pGameObject.lock()->GetComponent<Comp::RenderComp>();
		m_pHexGridComp = m_pGameObject.lock()->GetComponent<Comp::HexGrid>();
	}
}

bool Comp::TileTexture::HasAllComponents() const
{
	if (!m_pHexGridComp)
		return false;
	if (!m_pRenderComp)
		return false;
	return true;
}

void Comp::TileTexture::CreateTexture()
{
	m_pTileTexture = dae::ResourceManager::GetInstance().LoadTexture(m_FileName);

	m_NeedsUpdate = true;
}