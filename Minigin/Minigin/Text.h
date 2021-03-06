#pragma once
#include <vec3.hpp>
#include "Component.h"
#include "Render.h"

namespace dae
{
	class Font;
	class Texture2D;
}

namespace Comp
{
	class TextComp final : public Component
	{
	public:
		TextComp();
		TextComp(const std::string& text, const std::string& fontFile, int fontSize);
		~TextComp() = default;

		void Initialize() override;
		void Update() override;

		void SetText(const std::string& newText);
		std::string GetText() const;
		void SetFont(const std::string& fontFile, int fontSize = 25);
		void SetColor(const glm::vec3& color);
	private:
		bool m_NeedsUpdate{false};
		std::string m_Text;
		glm::vec3 m_Color{1,1,1};
		std::shared_ptr<dae::Font> m_Font;
		std::shared_ptr<dae::Texture2D> m_pTexture{ nullptr };

		//all needed components for this one to work
		std::shared_ptr<RenderComp> m_pRenderComp{nullptr};

		void GetNeededComponents() override;
		bool HasAllComponents() const override;

		void CreateTexture();
	};
}

