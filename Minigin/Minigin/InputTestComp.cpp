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

void Comp::InputTestComp::Initialize()
{
	if (!IsAttachedToGameObject())
		return;

	GetNeededComponents();
}

void Comp::InputTestComp::Update()
{
	//checking if you got all components 
	if (!HasAllComponents())
		return;
}

void Comp::InputTestComp::GetNeededComponents()
{
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
	std::shared_ptr<Comp::TextComp> pTextComp = GetGameObject().lock()->GetComponent<Comp::TextComp>();
	if (pTextComp == nullptr)
		return;

	pTextComp->SetText("KeyboardPressed");
}

void ControllerPress::Execute()
{
	std::shared_ptr<Comp::TextComp> pTextComp = GetGameObject().lock()->GetComponent<Comp::TextComp>();
	if (pTextComp == nullptr)
		return;

	pTextComp->SetText("ControllerPressed");
}
