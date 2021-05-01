#if _DEBUG
#include <vld.h>
#endif

#include <Minigin.h>
#include "QbertGame.h"
#include <ResourceManager.h>

int main()
{
    QbertGame game{};
    dae::Minigin engine{};

    // tell the resource manager where he can find the game data
    dae::ResourceManager::GetInstance().Init("../Data/");

    engine.Initialize("Qbert", (int)game.GetWindowDimentions().x, (int)game.GetWindowDimentions().y);

    game.LoadLevelScene();

    engine.Run();
    return 0;
}