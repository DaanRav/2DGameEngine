#pragma once
#include "Component.h"

namespace Comp
{
	class TextComp;

	class FpsCounterComp : public Component
	{
	public:
		FpsCounterComp();
		~FpsCounterComp() = default;
		FpsCounterComp(const FpsCounterComp& other);
		FpsCounterComp(FpsCounterComp&& other);
		FpsCounterComp& operator=(const FpsCounterComp& other);
		FpsCounterComp& operator=(FpsCounterComp&& other);

		void Update() override;
		CompType GetType() const override { return CompType::fpsCounter; };

	private:
		float m_RefreshRate{1.f};	//refresh the fps only every 1s
		float m_RefreshTime{m_RefreshRate+1.f};	//setting it bigger then the refreshRate so that we update on construction
		float m_AverageFps{60};
		int m_SampleSize{1};

		//all needed components for this one to work
		std::shared_ptr<TextComp> m_pTextComp;

		void GetNeededComponents() override;
		bool HasAllComponents() const override;

	};
}

