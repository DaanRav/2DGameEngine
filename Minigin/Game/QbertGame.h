#pragma once
#include <vec2.hpp>

class QbertGame
{
public:
	QbertGame() = default;
	~QbertGame() = default;

	void LoadLevelScene();
	glm::vec2 GetWindowDimentions() const;

private:
	glm::vec2 m_WindowWidth{ 640, 480 };

};

