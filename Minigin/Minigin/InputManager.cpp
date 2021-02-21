#include "InputManager.h"
#include <iostream>

dae::InputManager::InputManager()
{
	//setting the input vector to the correct size
	for (int i{}; i < int(ControllerButton::NR_OF_BUTTONS); i++)
	{
		m_Commands.push_back(Input{});
	}
}

dae::InputManager::~InputManager()
{
	for (Input input : m_Commands)
	{
		delete input.downCommand;
		input.downCommand = nullptr;

		delete input.upCommand;
		input.upCommand = nullptr;

		delete input.pressedCommand;
		input.pressedCommand = nullptr;
	}
}

bool dae::InputManager::ProcessInput()
{
	DWORD result = XInputGetKeystroke(0, 0, &m_Keystrokes);

	if (result == ERROR_DEVICE_NOT_CONNECTED)
	{
		std::cout << "ERROR: No device connected\n";
		return false;
	}
	if (result == ERROR_EMPTY)
	{
		return false;
	}

	return true;
}

void dae::InputManager::HandleInput()
{
	//going through all the buttons and checking wich ones are pressed
	for (int i{}; i < int(ControllerButton::NR_OF_BUTTONS); i++)
	{
		//if the button is pressed execute the commands associated with it
		if (m_Keystrokes.Flags & XINPUT_KEYSTROKE_REPEAT)
		{
			if (IsPressed(ControllerButton(i)))
			{
				if (m_Commands.at(i).pressedCommand != nullptr)
					m_Commands.at(i).pressedCommand->Execute();
			}
		}
		//if the button is released execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYUP)
		{
			if (IsPressed(ControllerButton(i)))
			{
				if (m_Commands.at(i).upCommand != nullptr)
					m_Commands.at(i).upCommand->Execute();
			}
		}
		//if the button is pressed down execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			if (IsPressed(ControllerButton(i)))
			{
				if (m_Commands.at(i).downCommand != nullptr)
					m_Commands.at(i).downCommand->Execute();
			}
		}
	}
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case dae::ControllerButton::ButtonCross:
		if (m_Keystrokes.VirtualKey == VK_PAD_A)
			return true;
		break;
	case dae::ControllerButton::ButtonCircle:
		if (m_Keystrokes.VirtualKey == VK_PAD_B)
			return true;
		break;
	case dae::ControllerButton::ButtonSquare:
		if (m_Keystrokes.VirtualKey == VK_PAD_X)
			return true;
		break;
	case dae::ControllerButton::ButtonTriangle:
		if (m_Keystrokes.VirtualKey == VK_PAD_Y)
			return true;
		break;
	case dae::ControllerButton::DpadUp:
		if (m_Keystrokes.VirtualKey == VK_PAD_DPAD_UP)
			return true;
		break;
	case dae::ControllerButton::DpadDown:
		if (m_Keystrokes.VirtualKey == VK_PAD_DPAD_DOWN)
			return true;
		break;
	case dae::ControllerButton::DpadLeft:
		if (m_Keystrokes.VirtualKey == VK_PAD_DPAD_LEFT)
			return true;
		break;
	case dae::ControllerButton::DpadRight:
		if (m_Keystrokes.VirtualKey == VK_PAD_DPAD_RIGHT)
			return true;
		break;
	case dae::ControllerButton::ButtonStart:
		if (m_Keystrokes.VirtualKey == VK_PAD_START)
			return true;
		break;
	case dae::ControllerButton::ButtonBack:
		if (m_Keystrokes.VirtualKey == VK_PAD_BACK)
			return true;
		break;
	case dae::ControllerButton::LeftBumper:
		if (m_Keystrokes.VirtualKey == VK_PAD_LSHOULDER)
			return true;
		break;
	case dae::ControllerButton::LeftThumb:
		if (m_Keystrokes.VirtualKey == VK_PAD_LTHUMB_PRESS)
			return true;
		break;
	case dae::ControllerButton::RightBumper:
		if (m_Keystrokes.VirtualKey == VK_PAD_RSHOULDER)
			return true;
		break;
	case dae::ControllerButton::RightThumb:
		if (m_Keystrokes.VirtualKey == VK_PAD_RTHUMB_PRESS)
			return true;
		break;
	default:
		break;
	}

	return false;
}

void dae::InputManager::SetCommand(const ControllerButton& button, ButtonState buttonState, Command* pCommand)
{
	if (buttonState == ButtonState::Down)
	{
		//removing the old command
		delete m_Commands.at(int(button)).downCommand;
		//setting the new command
		m_Commands.at(int(button)).downCommand = pCommand;
	}
	if (buttonState == ButtonState::Up)
	{
		//removing the old command
		delete m_Commands.at(int(button)).upCommand;
		//setting the new command
		m_Commands.at(int(button)).upCommand = pCommand;
	}
	if (buttonState == ButtonState::Pressed)
	{
		//removing the old command
		delete m_Commands.at(int(button)).pressedCommand;
		//setting the new command
		m_Commands.at(int(button)).pressedCommand = pCommand;
	}
}
