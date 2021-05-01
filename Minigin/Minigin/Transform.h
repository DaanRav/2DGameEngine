#pragma once
#include <../glm/vec3.hpp>
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
		 void SetScale(const glm::vec3& scale);
		 glm::vec3 GetScale() const;

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Scale{1,1,1};
		//TODO: maybe implement rotation here as well

		void GetNeededComponents() override {};
		bool HasAllComponents() const override { return true; };
	};
}
