#pragma once
#include <Component.h>
#include <../glm/mat2x2.hpp>
#include <memory>
#include <vector>

namespace Comp
{
	//inspiration
	//https://www.redblobgames.com/grids/hexagons/

	//this grid will be oriented with one of the points on top 
	//we will use a axial or cube coord system

	class TransformComp;

	class HexGrid : public Component
	{
	public:
		enum class Directions
		{
			left = 0, right = 1, topLeft = 2, topRight = 3, bottomLeft = 4, bottomRight = 5, NR_OF_DIRECTONS = 6
		};
		enum class Grids
		{
			upTriangle, diamond
		};

		HexGrid();
		HexGrid(Grids gridType, int gridWidth, int gridHeight, float TileWidth = 10, float TileHeight = 10);
		~HexGrid() = default;

		void Initialize() override;
		void Update() override;

		std::vector<std::vector<bool>> GetGrid() const;
		glm::ivec3 Neighbor(const glm::ivec3& cubeCoords, Directions dir);
		glm::ivec2 Neighbor(const glm::ivec2& axialCoords, Directions dir);
		glm::ivec2 AxialToPxl(const glm::ivec2& axialCoords);
		glm::ivec2 CubeToPxl(const glm::ivec3& cubeCoords);

		glm::ivec2 GetGridDimentions() const;
		glm::vec2 GetTileSize() const;

	private:
		//components stuff
		void GetNeededComponents() override;
		bool HasAllComponents() const override;

		//hex stuff
		static glm::ivec3 m_CubeDirections[];
		static glm::ivec2 m_AxialDirections[];
		glm::mat2 m_AxialToPxl;
		//this is the size of the cube a hex fits in
		glm::ivec2 m_HexTileSize{ 10,10 };
		std::vector<std::vector<bool>> m_HexArray;

		glm::ivec2 CubeToAxial(const glm::ivec3& cubeCoords);
		glm::ivec3 AxialToCube(const glm::ivec2& axialCoords);

		void FillGridArray(int width, int height, bool villValue = false);
		void CreateUpTriangleHexGrid(int width, int height);
		void CreateDiamondGrid2x3();
	};
}
