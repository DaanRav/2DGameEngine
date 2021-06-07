#pragma once
#include <vec3.hpp>
#include <memory>
#include <map>
#include "Font.h"
#include "Transform.h"

namespace dae
{
	class Texture2D;
}

namespace Comp
{
	class RenderComp final : public Component
	{
	public:
		RenderComp();
		~RenderComp() = default;


		void Initialize() override;
		void Update() override;

		void AddTexture(const std::shared_ptr<dae::Texture2D>& pTexture);
		void RemoveTextures(const std::shared_ptr<dae::Texture2D>& pTexture);

		bool IsEnabled() const { return m_Enable; };
		void SetEnable(bool enable) { m_Enable = enable; };
	
	private:
		void GetNeededComponents() override;
		bool HasAllComponents() const override;

		std::vector<std::shared_ptr<dae::Texture2D>> m_TexturesToRender{};

		bool m_Enable{ true };
	};
}

