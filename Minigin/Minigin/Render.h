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
		void RemoveTexture(const std::shared_ptr<dae::Texture2D>& pTexture);
	
	private:
		void GetNeededComponents() override;
		bool HasAllComponents() const override;

		std::vector<std::shared_ptr<dae::Texture2D>> m_TexturesToRender{};

		//all needed components for this one to work
		std::shared_ptr<TransformComp> m_pTransformComp{nullptr};
	};
}

