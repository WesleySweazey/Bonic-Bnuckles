#include "GamePCH.h"

#include "VictoryScene.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "Game/UI/Time.h"
#include "BulletManager/BulletManager.h"
#include "CollisionFilter/CollisionFilter.h"
#include "Audio/Cue.h"
#include "Audio/ShuffleCue.h"
#include "Audio/WeightedCue.h"
#include "Audio/SoundPlayer.h"

VictoryScene::VictoryScene(Game* pGame, ResourceManager* pResources, std::string name, Player* pPlayer)
    : Scene(pGame, pResources, name)
{
    m_Opaque = true;
    m_pPlayer = pPlayer;
}

VictoryScene::~VictoryScene()
{
    Cleanup();
}

void VictoryScene::LoadContent()
{
    Scene::LoadContent(); 
    // Create our GameObjects.
    {
        // Camera.
        float width = (float)m_pGame->GetFramework()->GetWindowWidth();
        float height = (float)m_pGame->GetFramework()->GetWindowHeight();

        float aspect = width / height;

        CameraObject* pCamera = new CameraObject(this, "Camera", vec3(0, 0, -15), vec3(0, 0, 0), vec3(1, 1, 1));
        pCamera->GetViewMatrix()->SetIdentity();
        pCamera->GetProjMatrix()->CreateOrtho(0, 9 * aspect, 0, 9, 0, 5);
        AddGameObject(pCamera);

        GameObject* pVictoryScreen = new GameObject(this, "VictoryScreen", vec3(0, 0, -13)/*vec3(12, 6.5, 5)*/, vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Box"),
            m_pResources->GetMaterial("SRank"));
        AddGameObject(pVictoryScreen);
    }
}
void VictoryScene::OnEvent(Event* pEvent)
{
    Scene::OnEvent(pEvent);
}

void VictoryScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

 if (m_pPlayer->GetVictory() == true)
    {
        if (m_pPlayer->GetTime()->GetTimeElapsed() <= 120.0)
        {
            GetGameObjectByName("VictoryScreen")->SetMaterial(m_pResources->GetMaterial("SRank"));
        }
        else if (m_pPlayer->GetTime()->GetTimeElapsed() <= 160.0)
        {
            GetGameObjectByName("VictoryScreen")->SetMaterial(m_pResources->GetMaterial("ARank"));
        }
        else if (m_pPlayer->GetTime()->GetTimeElapsed() <= 200.0)
        {
            GetGameObjectByName("VictoryScreen")->SetMaterial(m_pResources->GetMaterial("BRank"));
        }
        else if (m_pPlayer->GetTime()->GetTimeElapsed() <= 240.0)
        {
            GetGameObjectByName("VictoryScreen")->SetMaterial(m_pResources->GetMaterial("CRank"));
        }
        else
        {
            GetGameObjectByName("VictoryScreen")->SetMaterial(m_pResources->GetMaterial("DRank"));
        }
    }
}

void VictoryScene::Draw()
{
    Scene::Draw();
}
