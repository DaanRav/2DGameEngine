#pragma once
#include <Component.h>
#include <memory>

namespace Comp
{
	class RenderComp;

	class FlickerComp : public Component
	{
	public:
		FlickerComp(float interval = 0.1f);
		~FlickerComp() = default;

		void Initialize() override;
		void Update() override;

	private:
		void GetNeededComponents() override;
		bool HasAllComponents() const override;

		std::shared_ptr<RenderComp> m_pRenderComp{ nullptr };
		float m_Interval{ 0.1f };
		float m_Counter{ 0.f };
	};
}

