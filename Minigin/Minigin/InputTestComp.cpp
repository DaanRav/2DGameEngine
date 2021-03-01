#include "InputTestComp.h"
#include "Text.h"
#include "InputManager.h"

Comp::InputTestComp::InputTestComp()
{
}

Comp::InputTestComp::InputTestComp(const InputTestComp& other)
{
	UNREFERENCED_PARAMETER(other);
}

Comp::InputTestComp::InputTestComp(InputTestComp&& other)
{
	UNREFERENCED_PARAMETER(other);
}

Comp::InputTestComp& Comp::InputTestComp::operator=(const InputTestComp& other)
{
	UNREFERENCED_PARAMETER(other);
	return *this;
}

Comp::InputTestComp& Comp::InputTestComp::operator=(InputTestComp&& other)
{
	UNREFERENCED_PARAMETER(other);
	return *this;
}

void Comp::InputTestComp::Update()
{
	//check if the component can update, if he has all he needs and is attached to a gameObject
	if (!IsAttachedToGameObject())
		return;
	//getting the components if needed
	if (!HasAllComponents())
		GetNeededComponents();
	//checking again if you got all components this time
	if (!HasAllComponents())
		return;


}

void Comp::InputTestComp::GetNeededComponents()
{
	//TODO: got to work this away in an initialize function
	//have to do it this way for now so the m_pGameObject is not a nullptr and not in the constructor

	//creating the commands for the input manager
	m_pKeyboardPress = new KeyboardPress{ m_pGameObject };
	m_pControllerPress = new ControllerPress{ m_pGameObject };

	InputManager::GetInstance().SetCommand(KeyboardButton::A, ButtonState::Up, m_pKeyboardPress);
	InputManager::GetInstance().SetCommand(ControllerButton::ButtonCross, ButtonState::Up, m_pControllerPress);
}

bool Comp::InputTestComp::HasAllComponents() const
{
	if (m_pControllerPress != nullptr && m_pKeyboardPress != nullptr)
		return true;
	return false;
}


//commands
void KeyboardPress::Execute()
{
	std::shared_ptr<Comp::TextComp> pTextComp = std::dynamic_pointer_cast<Comp::TextComp>(GetGameObject().lock()->GetComponent(Component::CompType::text));
	if (pTextComp == nullptr)
		return;

	pTextComp->SetText("KeyboardPressed");
}

void ControllerPress::Execute()
{
	std::shared_ptr<Comp::TextComp> pTextComp = std::dynamic_pointer_cast<Comp::TextComp>(GetGameObject().lock()->GetComponent(Component::CompType::text));
	if (pTextComp == nullptr)
		return;

	pTextComp->SetText("ControllerPressed");
}
