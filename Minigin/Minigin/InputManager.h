#pragma once
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")
#include "Command.h"
#include <map>
#include "Singleton.h"


enum class ControllerButton
{
	ButtonCross = VK_PAD_A,
	ButtonA = VK_PAD_A,
	ButtonCircle = VK_PAD_B,
	ButtonB = VK_PAD_B,
	ButtonSquare = VK_PAD_X,
	ButtonX = VK_PAD_X,
	ButtonTriangle = VK_PAD_Y,
	ButtonY = VK_PAD_Y,
	DpadUp = VK_PAD_DPAD_UP,
	DpadDown = VK_PAD_DPAD_DOWN,
	DpadLeft = VK_PAD_DPAD_LEFT,
	DpadRight = VK_PAD_DPAD_RIGHT,
	ButtonStart = VK_PAD_START,
	ButtonBack = VK_PAD_BACK,
	LeftBumper = VK_PAD_LSHOULDER,
	LeftThumb = VK_PAD_LTHUMB_PRESS,
	RightBumper = VK_PAD_RSHOULDER,
	RightThumb = VK_PAD_RTHUMB_PRESS,
	NR_OF_BUTTONS = 18
};

enum class KeyboardButton
{

};



enum class ButtonState
{
	Down, Up, Pressed
};

class InputManager final : public dae::Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();
	bool ProcessInput();

	bool IsPressed(ControllerButton button) const;
	void SetCommand(const ControllerButton& button, ButtonState buttonState, Command* pCommand);
private:
	//only supports one command per button
	struct Input
	{
		Command* upCommand{ nullptr };
		Command* pressedCommand{ nullptr };
		Command* downCommand{ nullptr };
	};

	XINPUT_KEYSTROKE m_Keystrokes{};
	std::map<ControllerButton,Input> m_ControllerCommands{};
	bool m_StopGame{};

	void HandleControllerInput();
};
