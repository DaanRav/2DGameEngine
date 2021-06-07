#include "HexGrid.h"
#include "GameObject.h"
#include "Transform.h"

//static vars
glm::ivec3 Comp::HexGrid::m_CubeDirections[int(Comp::HexGrid::Directions::NR_OF_DIRECTONS)] =
{ glm::vec3{-1,1,0},glm::vec3{1,-1,0},glm::vec3{0,1,-1},glm::vec3{1,0,-1},glm::vec3{-1,0,1},glm::vec3{0,-1,1} };

glm::ivec2 Comp::HexGrid::m_AxialDirections[int(Comp::HexGrid::Directions::NR_OF_DIRECTONS)] =
{ glm::vec2{-1,0},glm::vec2{1,0},glm::vec2{0,-1},glm::vec2{1,-1},glm::vec2{-1,1},glm::vec2{0,1} };

Comp::HexGrid::HexGrid()
{
	//as default hex grid type we will just create a diamond shaped one
	CreateDiamondGrid2x3();
}

Comp::HexGrid::HexGrid(Grids gridType, int gridWidth, int gridHeight, float TileWidth, float TileHeight)
	:m_HexTileSize{ TileWidth,TileHeight }
{
	//creating the grid
	switch (gridType)
	{
	case Comp::HexGrid::Grids::upTriangle:
		CreateUpTriangleHexGrid(gridWidth, gridHeight);
		break;
	case Comp::HexGrid::Grids::diamond:
		CreateDiamondGrid2x3();
		break;
	default:
		CreateDiamondGrid2x3();
		break;
	}
}

void Comp::HexGrid::Initialize()
{
	if (!IsAttachedToGameObject())
		return;

	GetNeededComponents();

	m_AxialToPxl = { m_HexTileSize.x * m_pTransformComp->GetScale().x , 0,							//first colom
			(m_HexTileSize.x / 2)* m_pTransformComp->GetScale().x, ((3.f / 4.f) * m_HexTileSize.y)* m_pTransformComp->GetScale().y };	//second colom
}

void Comp::HexGrid::Update()
{
	if (!HasAllComponents())
		return;

}

void Comp::HexGrid::GetNeededComponents()
{
	Component::GetNeededComponents();
}

bool Comp::HexGrid::HasAllComponents() const
{
	return true;
}

glm::ivec2 Comp::HexGrid::CubeToAxial(const glm::ivec3& cubeCoords)
{
	glm::ivec2 newCoords{ cubeCoords.x,cubeCoords.z };
	return newCoords;
}

std::vector<std::vector<bool>> Comp::HexGrid::GetGrid() const
{
	return m_HexArray;
}

glm::ivec3 Comp::HexGrid::Neighbor(const glm::ivec3& cubeCoords, Directions dir)
{
	glm::ivec3 neighbor{};
	neighbor.x = cubeCoords.x + m_CubeDirections[(int)dir].x;
	neighbor.y = cubeCoords.y + m_CubeDirections[(int)dir].y;
	neighbor.z = cubeCoords.z + m_CubeDirections[(int)dir].z;

	//if its not a valid coord return the current coord
	glm::ivec2 axialCoords{ CubeToAxial(cubeCoords) };
	if (m_HexArray.at(axialCoords.x).at(axialCoords.y))
		return cubeCoords;

	return neighbor;
}

glm::ivec3 Comp::HexGrid::AxialToCube(const glm::ivec2& axialCoords)
{
	glm::ivec3 newCoords{ axialCoords.x,-axialCoords.x - axialCoords.y,axialCoords.y };
	return newCoords;
}

void Comp::HexGrid::FillGridArray(int width, int height, bool villValue)
{
	//setting the sizes of the vectors
	m_HexArray.reserve(width);
	for (int i{}; i < width; ++i)
	{
		std::vector<bool> emptyArray{};
		emptyArray.reserve(height);

		for (int j{}; j < height; ++j)
		{
			emptyArray.push_back(villValue);
		}
		m_HexArray.push_back(emptyArray);
	}
}

void Comp::HexGrid::CreateUpTriangleHexGrid(int width, int height)
{
	FillGridArray(width, height, false);

	//setting the usable tiles to true
	//in a piramid form
	for (int i{}; i < height; ++i)
	{
		for (int j{}; j < i+1; ++j)
		{
			m_HexArray.at(i).at(width -1 - j ) = true;
		}
	}

}

void Comp::HexGrid::CreateDiamondGrid2x3()
{
	FillGridArray(2, 3, false);

	//setting the usable tiles to true
	//in a diamond formation	
	m_HexArray.at(1).at(0) = true;
	m_HexArray.at(0).at(1) = true;
	m_HexArray.at(1).at(1) = true;
	m_HexArray.at(0).at(2) = true;
}

glm::ivec2 Comp::HexGrid::Neighbor(const glm::ivec2& axialCoords, Directions dir)
{
	glm::ivec2 neighbor{};
	neighbor.x = axialCoords.x + m_AxialDirections[(int)dir].x;
	neighbor.y = axialCoords.y + m_AxialDirections[(int)dir].y;

	//if its not a valid coord return the current coord
	if (m_HexArray.at(axialCoords.x).at(axialCoords.y))
		return axialCoords;

	return neighbor;
}

glm::ivec2 Comp::HexGrid::AxialToPxl(const glm::ivec2& axialCoords)
{
	//the coords will be around the center of the grid
	glm::ivec2 gridCenter{GetGridDimentions()/2};
	gridCenter = m_AxialToPxl * gridCenter;

	glm::ivec2 pxlPos{};
	//no need to add the size in here since we already put it in our matrix
	pxlPos = m_AxialToPxl * axialCoords;

	return pxlPos - gridCenter + glm::ivec2(m_pTransformComp->GetPosition());
}

glm::ivec2 Comp::HexGrid::CubeToPxl(const glm::ivec3& cubeCoords)
{
	return AxialToPxl(CubeToAxial(cubeCoords));
}

glm::ivec2 Comp::HexGrid::GetGridDimentions() const
{
	glm::ivec2 gridDimentions{ m_HexArray.size(),m_HexArray.at(0).size() };
	return gridDimentions;
}

glm::vec2 Comp::HexGrid::GetTileSize() const
{
	return m_HexTileSize;
}
