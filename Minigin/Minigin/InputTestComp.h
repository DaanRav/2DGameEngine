#pragma once
#include "Component.h"
#include <memory>
#include "Command.h"

//input commands
class KeyboardPress : public Command
{
public:
	KeyboardPress(std::weak_ptr<GameObject> pGameObject) :Command{ pGameObject } {};
	void Execute() override;
};

class ControllerPress : public Command
{
public:
	ControllerPress(std::weak_ptr<GameObject> pGameObject) :Command{ pGameObject } {};
	void Execute() override;
};

namespace Comp
{
	class TextComp;

	//simple component that prints out the input
	class InputTestComp final : public Component
	{
	public:
		InputTestComp();
		~InputTestComp() = default;
		InputTestComp(const InputTestComp& other);
		InputTestComp(InputTestComp&& other);
		InputTestComp& operator=(const InputTestComp& other);
		InputTestComp& operator=(InputTestComp&& other);

		void Initialize() override;
		void Update() override;
		CompType GetType() const override { return CompType::inputTest; };

	private:

		void GetNeededComponents() override;
		bool HasAllComponents() const override;

		//commands, in this case we will see them as the needed components
		KeyboardPress* m_pKeyboardPress{ nullptr };
		ControllerPress* m_pControllerPress{ nullptr };
	};
}