#include "InputManager.h"
#include <iostream>
#include <SDL.h>

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
	for (std::pair<ControllerButton, Input> input : m_ControllerCommands)
	{
		delete input.second.downCommand;
		input.second.downCommand = nullptr;

		delete input.second.upCommand;
		input.second.upCommand = nullptr;

		delete input.second.pressedCommand;
		input.second.pressedCommand = nullptr;
	}
}

bool InputManager::ProcessInput()
{
	//controller input
	XInputGetKeystroke(0, 0, &m_Keystrokes);
	HandleControllerInput();

	//keyboard input
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{

		}
	}

	return true;
}

bool InputManager::IsPressed(ControllerButton button) const
{
	if ((WORD)button == m_Keystrokes.VirtualKey)
		return true;
	return false;
}

void InputManager::SetCommand(const ControllerButton& button, ButtonState buttonState, Command* pCommand)
{
	if (buttonState == ButtonState::Down)
	{
		//removing the old command
		delete m_ControllerCommands.at(button).downCommand;
		//setting the new command
		m_ControllerCommands.at(button).downCommand = pCommand;
	}
	if (buttonState == ButtonState::Up)
	{
		//removing the old command
		delete m_ControllerCommands.at(button).upCommand;
		//setting the new command
		m_ControllerCommands.at(button).upCommand = pCommand;
	}
	if (buttonState == ButtonState::Pressed)
	{
		//removing the old command
		delete m_ControllerCommands.at(button).pressedCommand;
		//setting the new command
		m_ControllerCommands.at(button).pressedCommand = pCommand;
	}
}

void InputManager::HandleControllerInput()
{
	//going through all the buttons and checking wich ones are pressed
	for (const std::pair<ControllerButton, Input>& input : m_ControllerCommands)
	{
		//if the button is pressed execute the commands associated with it
		if (m_Keystrokes.Flags & XINPUT_KEYSTROKE_REPEAT)
		{
			if (IsPressed(input.first))
			{
				if (m_ControllerCommands.at(input.first).pressedCommand != nullptr)
					m_ControllerCommands.at(input.first).pressedCommand->Execute();
			}
		}
		//if the button is released execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYUP)
		{
			if (IsPressed(input.first))
			{
				if (m_ControllerCommands.at(input.first).upCommand != nullptr)
					m_ControllerCommands.at(input.first).upCommand->Execute();
			}
		}
		//if the button is pressed down execute the commands associated with it
		if (m_Keystrokes.Flags == XINPUT_KEYSTROKE_KEYDOWN)
		{
			if (IsPressed(input.first))
			{
				if (m_ControllerCommands.at(input.first).downCommand != nullptr)
					m_ControllerCommands.at(input.first).downCommand->Execute();
			}
		}
	}
}
