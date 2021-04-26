#pragma once
#include "Component.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Render.h"
#include <memory>

namespace Comp
{
	class TextureComp final : public Component
	{
	public:
		TextureComp();
		TextureComp(const std::string& fileName);
		~TextureComp() = default;

		void Initialize() override;
		void Update() override;

		void SetTexture(const std::string& fileName);

	private:
		std::string m_FileName{};
		bool m_NeedsUpdate{ false };
		std::shared_ptr<dae::Texture2D> m_pTexture{ nullptr };

		//all needed components for this one to work
		std::shared_ptr<RenderComp> m_pRenderComp{ nullptr };

		void GetNeededComponents() override;
		bool HasAllComponents() const override;

		void CreateTexture();
	};
}

