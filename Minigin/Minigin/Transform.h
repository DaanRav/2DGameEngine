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
		TransformComp(const TransformComp& other);
		TransformComp(TransformComp&& other);
		TransformComp& operator=(const TransformComp& other);
		TransformComp& operator=(TransformComp&& other);

		void Initialize() override;
		CompType GetType() const override { return CompType::transform; };
		
		 void SetPosition(const glm::vec3& pos);
		 glm::vec3 GetPosition() const;

	private:
		glm::vec3 m_Position;
		//TODO: maybe implement rotation, and scale here

		void GetNeededComponents() override {};
		bool HasAllComponents() const override { return true; };
	};
}
