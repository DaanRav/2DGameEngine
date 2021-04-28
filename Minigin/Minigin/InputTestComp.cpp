#include "InputTestComp.h"
#include "Text.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "SoundSystem.h"

Comp::InputTestComp::InputTestComp()
{
}

void Comp::InputTestComp::Initialize()
{
	if (!IsAttachedToGameObject())
		return;

	GetNeededComponents();

	//load the needed sounds here
	ServiceLocator::GetInstance().GetSoundSystem().LoadSound("door", "../Data/sounds/door1.wav", false);
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

	ServiceLocator::GetInstance().GetSoundSystem().PlayASound("door", SDL_MIX_MAXVOLUME);
	pTextComp->SetText("KeyboardPressed");
}

void ControllerPress::Execute()
{
	std::shared_ptr<Comp::TextComp> pTextComp = GetGameObject().lock()->GetComponent<Comp::TextComp>();
	if (pTextComp == nullptr)
		return;

	ServiceLocator::GetInstance().GetSoundSystem().PlayASound("door", SDL_MIX_MAXVOLUME);
	pTextComp->SetText("ControllerPressed");
}
