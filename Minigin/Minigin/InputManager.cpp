#include "InputManager.h"
#include <iostream>

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

	//keyboard / mouse input
	while (SDL_PollEvent(&m_SDLEvent))
	{
		if (m_SDLEvent.type == SDL_QUIT) 
		{
			//quiting the game when clicked on the cross of the window
			return false;
		}
		if (m_SDLEvent.type == SDL_KEYDOWN || m_SDLEvent.type == SDL_KEYUP) 
		{
			//only handel keyboard input if a key is pressed
			HandleKeyboardInput();
		}
		if (m_SDLEvent.type == SDL_MOUSEBUTTONDOWN) 
		{
			//mouse input should come here
		}
	}

	return true;
}

bool InputManager::IsPressed(const ControllerButton& button) const
{
	if ((WORD)button == m_Keystrokes.VirtualKey)
		return true;
	return false;
}

bool InputManager::IsPressed(const KeyboardButton& button) const
{
	if ((SDL_Scancode)button == m_SDLEvent.key.keysym.scancode)
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

void InputManager::SetCommand(const KeyboardButton& button, ButtonState buttonState, Command* pCommand)
{
	if (buttonState == ButtonState::Down)
	{
		//removing the old command
		delete m_KeyboardCommands.at(button).downCommand;
		//setting the new command
		m_KeyboardCommands.at(button).downCommand = pCommand;
	}
	if (buttonState == ButtonState::Up)
	{
		//removing the old command
		delete m_KeyboardCommands.at(button).upCommand;
		//setting the new command
		m_KeyboardCommands.at(button).upCommand = pCommand;
	}
	if (buttonState == ButtonState::Pressed)
	{
		//removing the old command
		delete m_KeyboardCommands.at(button).pressedCommand;
		//setting the new command
		m_KeyboardCommands.at(button).pressedCommand = pCommand;
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

void InputManager::HandleKeyboardInput()
{
	//for keyboard input we only need to check the current button that is pressed and not loop over all of them
	//we do the looping in the proces input fucntion
	auto it = m_KeyboardCommands.find((KeyboardButton)m_SDLEvent.key.keysym.scancode);
	//check if the key is in the map
	if (it == m_KeyboardCommands.end())
		return;

	//TODO: make the down command work as well withs some kind of flag or look a bit more into sdl
	if (m_SDLEvent.type == SDL_KEYDOWN)
	{
		if(it->second.pressedCommand != nullptr)
			it->second.pressedCommand->Execute();
	}
	if (m_SDLEvent.type == SDL_KEYUP)
	{
		if (it->second.upCommand != nullptr)
			it->second.upCommand->Execute();
	}
}
