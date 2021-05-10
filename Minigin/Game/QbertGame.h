#pragma once
#include <vec2.hpp>
#include <string>

class QbertGame
{
public:
	QbertGame() = default;
	~QbertGame() = default;

	void LoadLevelScene();
	glm::vec2 GetWindowDimentions() const;

private:
	glm::vec2 m_WindowSize{ 640, 480 };

	void LoadTiles2x2(const std::string& sceneName, const glm::vec2& pos, const glm::vec2& scale);
};

