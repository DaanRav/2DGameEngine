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
#include "HexGrid.h"
#include "TileTexture.h"

void QbertGame::LoadLevelScene()
{
    auto& LevelScene = dae::SceneManager::GetInstance().CreateScene("LevelScreen");

    //displaying a temp fps counter to keep track of performance
    auto go = std::make_shared<GameObject>(L"fpsCounter", glm::vec3{ 5,5,0 });
    go->AddComponent(std::make_shared<Comp::TextComp>("00 FPS", "q-bert-revised/q-bert-revised.ttf", 10));
    go->GetComponent<Comp::TextComp>()->SetColor(glm::vec3{ 0.0f,1.0f,0.0f });
    go->AddComponent(std::make_shared<Comp::FpsCounterComp>());
    go->AddComponent(std::make_shared<Comp::RenderComp>());
    LevelScene.Add(go);

    //displaying the level text on the screen
    go = std::make_shared<GameObject>(L"LevelTexture", glm::vec3{ (m_WindowSize.x - (192 * 2)) / 2, m_WindowSize.y - 220, 0 });
    go->GetTransform()->SetScale(glm::vec3{ 2,2,2 });
    go->AddComponent(std::make_shared<Comp::TextureComp>("Level.png"));
    go->AddComponent(std::make_shared<Comp::RenderComp>());
    LevelScene.Add(go);

    //the circle under the level text
    go = std::make_shared<GameObject>(L"nrCircle", glm::vec3{ (m_WindowSize.x - (32 * 2)) / 2, m_WindowSize.y - 100, 0 });
    go->GetTransform()->SetScale(glm::vec3{ 2,2,2 });
    go->AddComponent(std::make_shared<Comp::TextureComp>("Circle.png"));
    go->AddComponent(std::make_shared<Comp::RenderComp>());
    LevelScene.Add(go);

    //Level Number
    go = std::make_shared<GameObject>(L"levelNr", glm::vec3{ m_WindowSize.x / 2.f - 13,m_WindowSize.y - 85,0 });
    go->AddComponent(std::make_shared<Comp::TextComp>("1", "q-bert-revised/q-bert-revised.ttf", 30));
    go->GetComponent<Comp::TextComp>()->SetColor(glm::vec3{ 1.0f,1.0f,0.0f });
    go->AddComponent(std::make_shared<Comp::RenderComp>());
    go->AddComponent(std::make_shared<Comp::FlickerComp>(0.6f));
    LevelScene.Add(go);

    //level grid
    go = std::make_shared<GameObject>(L"levelGrid", glm::vec3{ m_WindowSize.x / 2,(m_WindowSize.y / 2) - 170,0 });
    go->GetTransform()->SetScale(glm::vec3{2,2,2});
    go->AddComponent(std::make_shared<Comp::RenderComp>());
    go->AddComponent(std::make_shared<Comp::HexGrid>(Comp::HexGrid::Grids::diamond, 2, 3, 32, 32));
    std::shared_ptr<Comp::TileTexture> hexTileTexture = std::make_shared<Comp::TileTexture>("Arcade - QBert - General Sprites.png");

    //setting some fixed vars based on the sprite layout
    hexTileTexture->SetSrcRect(glm::vec4{0,224,32,32});

    go->AddComponent(hexTileTexture);
    
    LevelScene.Add(go);



    //createGrid
    //LoadTiles2x2("LevelScreen", glm::vec2{ m_WindowSize.x / 2,(m_WindowSize.y / 2)-170 }, glm::vec2{ 2,2 });
}

glm::vec2 QbertGame::GetWindowDimentions() const
{
    return m_WindowSize;
}

void QbertGame::LoadTiles2x2(const std::string& sceneName, const glm::vec2& pos, const glm::vec2& scale)
{
    const int tileNrs{ 4 };

    //some fixed vars based on the sprites
    glm::vec2 tileTexSize{ 32,32 };
    glm::vec2 tileTexPos{ 0, 224 };

    std::shared_ptr<dae::Scene> scene = dae::SceneManager::GetInstance().GetScene(sceneName);
    std::shared_ptr<GameObject> gridObj = scene->GetGameObject(L"levelGrid");
    std::vector<std::vector<bool>> grid = gridObj->GetComponent<Comp::HexGrid>()->GetGrid();

    glm::vec3 tilePosArray[tileNrs]
    {
        glm::vec3{pos.x - 16 * scale.x, pos.y - 8 * scale.y, 0},
        glm::vec3{pos.x - 32 * scale.x,pos.y + 16 * scale.y,0},
        glm::vec3{pos.x,pos.y + 16 * scale.y,0},
        glm::vec3{pos.x - 16 * scale.x,pos.y + 40 * scale.y,0}
    };

    int gridWidth = (int)grid.size();
    int gridHeight = (int)grid.at(0).size();

    for (int i{}; i < gridWidth; ++i)
    {
        for (int j{}; j < gridHeight; ++j)
        {
            if (grid.at(i).at(j))
            {
                auto go = std::make_shared<GameObject>(L"TileNr_" + std::to_wstring(i) + L"_" + std::to_wstring(j)
                    , glm::vec3{ gridObj->GetComponent<Comp::HexGrid>()->AxialToPxl({ i,j }), 0 });
                go->GetComponent<Comp::TransformComp>()->SetScale(glm::vec3{ scale.x,scale.y,0 });
                go->AddComponent(std::make_shared<Comp::TextureComp>("Arcade - QBert - General Sprites.png"));
                go->GetComponent<Comp::TextureComp>()->SetSrcRect(glm::vec4{ tileTexPos.x, tileTexPos.y, tileTexSize.x, tileTexSize.y });
                go->GetComponent<Comp::TextureComp>()->SetDestRect(glm::vec4{ 0,0,tileTexSize.x,tileTexSize.y });
                go->AddComponent(std::make_shared<Comp::RenderComp>());
                scene->Add(go);
            }
        }
    }



}
