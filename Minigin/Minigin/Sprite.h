#pragma once
#include "Component.h"
#include <vec4.hpp>
#include <vec2.hpp>

namespace Comp
{
	class TextureComp;

	class Sprite final : public Component
	{
	public:
		//the sprite component is assuming that the frames are placed horizontally after each other in one line
		Sprite(int frames, int pxlWidth, int pxlHeight, const glm::vec2& startFramePos, float frameTime);
		~Sprite() = default;

		void Initialize() override;
		void Update() override;

		void SetSize(const glm::vec4& size);

	private:
		int m_Frames{1};
		int m_FramePxlWidth{ 0 };
		int m_FramePxlHeight{ 0 };
		glm::vec2 m_StartFramePos{ 0,0 };
		float m_FrameTime{0.1f};
		int m_CurrentFrame{ 0 };
		float m_ElapsedFrameTime{ 0 };

		std::shared_ptr<Comp::TextureComp> m_pTextureComp;

		void GetNeededComponents() override;
		bool HasAllComponents() const override;
	};
}

