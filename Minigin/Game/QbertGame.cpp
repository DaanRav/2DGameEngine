#include "QbertGame.h"

#include <string>
#include <vector>
#include <memory> 
#include <SceneManager.h>
#include <Scene.h>

//game object includes
#include <GameObject.h>
#include <Transform.h>
#include <Texture.h>
#include <Text.h>
#include <FpsCounter.h>
#include "FlickerComp.h"

void QbertGame::LoadLevelScene()
{
    auto& LevelScene = dae::SceneManager::GetInstance().CreateScene("LevelScreen");

    //displaying a temp fps counter to keep track of performance
    auto go = std::make_shared<GameObject>();
    go->AddComponent(std::make_shared<Comp::TransformComp>(glm::vec3{ 5,5,0 }));
    go->AddComponent(std::make_shared<Comp::TextComp>("00 FPS", "q-bert-revised/q-bert-revised.ttf", 10));
    go->GetComponent<Comp::TextComp>()->SetColor(glm::vec3{ 0.0f,1.0f,0.0f });
    go->AddComponent(std::make_shared<Comp::FpsCounterComp>());
    go->AddComponent(std::make_shared<Comp::RenderComp>());
    LevelScene.Add(go);

    //displaying the level text on the screen
    go = std::make_shared<GameObject>();
    go->AddComponent(std::make_shared<Comp::TransformComp>(glm::vec3{ (m_WindowWidth.x - (192*2))/2, m_WindowWidth.y-220, 0 }));
    go->GetComponent<Comp::TransformComp>()->SetScale(glm::vec3{ 2,2,2 });
    go->AddComponent(std::make_shared<Comp::TextureComp>("Level.png"));
    go->AddComponent(std::make_shared<Comp::RenderComp>());
    LevelScene.Add(go);

    //the circle under the level text
    go = std::make_shared<GameObject>();
    go->AddComponent(std::make_shared<Comp::TransformComp>(glm::vec3{ (m_WindowWidth.x - (32 * 2)) / 2, m_WindowWidth.y - 100, 0 }));
    go->GetComponent<Comp::TransformComp>()->SetScale(glm::vec3{ 2,2,2 });
    go->AddComponent(std::make_shared<Comp::TextureComp>("Circle.png"));
    go->AddComponent(std::make_shared<Comp::RenderComp>());
    LevelScene.Add(go);

    //Level Number
    go = std::make_shared<GameObject>();
    go->AddComponent(std::make_shared<Comp::TransformComp>(glm::vec3{ m_WindowWidth.x / 2.f - 13,m_WindowWidth.y - 85,0 }));
    go->AddComponent(std::make_shared<Comp::TextComp>("1", "q-bert-revised/q-bert-revised.ttf", 30));
    go->GetComponent<Comp::TextComp>()->SetColor(glm::vec3{ 1.0f,1.0f,0.0f });
    go->AddComponent(std::make_shared<Comp::RenderComp>());
    go->AddComponent(std::make_shared<Comp::FlickerComp>(0.6f));
    LevelScene.Add(go);

}

glm::vec2 QbertGame::GetWindowDimentions() const
{
    return m_WindowWidth;
}
