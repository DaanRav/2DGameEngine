#pragma once
#include <Component.h>
#include <string>
#include <vec4.hpp>
#include <vec2.hpp>

namespace dae
{
	class Texture2D;
}

namespace Comp
{
	class RenderComp;
	class HexGrid;
	class TransformComp;

	class TileTexture : public Component
	{
	public:
		TileTexture(const std::string& filePath);
		~TileTexture() = default;

		void Initialize() override;
		void Update() override;

		void SetSrcRect(const glm::vec4& srcRect);

	private:
		void GetNeededComponents() override;
		bool HasAllComponents() const override;

		void CreateTexture();

		std::string m_FileName{};
		glm::vec4 m_SrcRect{};
		bool m_NeedsUpdate{ false };
		std::shared_ptr<dae::Texture2D> m_pTileTexture{ nullptr };

		std::shared_ptr<RenderComp> m_pRenderComp{ nullptr };
		std::shared_ptr<HexGrid> m_pHexGridComp{ nullptr };
	};
}

