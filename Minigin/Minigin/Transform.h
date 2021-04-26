#pragma once
#include <vec3.hpp>
#include "Component.h"

namespace Comp
{
	class TransformComp final: public Component
	{
	public:
		TransformComp();
		TransformComp(const glm::vec3& pos);
		~TransformComp() = default;

		void Initialize() override;
		
		 void SetPosition(const glm::vec3& pos);
		 glm::vec3 GetPosition() const;

	private:
		glm::vec3 m_Position;
		//TODO: maybe implement rotation, and scale here

		void GetNeededComponents() override {};
		bool HasAllComponents() const override { return true; };
	};
}
