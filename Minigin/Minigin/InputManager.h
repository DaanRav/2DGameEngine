#pragma once
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")
#include "Command.h"
#include <vector>
#include "Singleton.h"


enum class ControllerButton
{
	ButtonCross,
	ButtonCircle,
	ButtonSquare,
	ButtonTriangle,
	DpadUp,
	DpadDown,
	DpadLeft,
	DpadRight,
	ButtonStart,
	ButtonBack,
	LeftBumper,
	LeftThumb,
	RightBumper,
	RightThumb,
	NR_OF_BUTTONS
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
	void HandleInput();
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
	std::vector<Input> m_Commands{};
	bool m_StopGame{};
};
