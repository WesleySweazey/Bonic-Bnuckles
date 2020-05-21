#include "GamePCH.h"

#include "TitleScene.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "BulletManager/BulletManager.h"
#include "CollisionFilter/CollisionFilter.h"
#include "Audio/Cue.h"
#include "Audio/ShuffleCue.h"
#include "Audio/WeightedCue.h"
#include "Audio/SoundPlayer.h"

TitleScene::TitleScene(Game* pGame, ResourceManager* pResources, std::string name)
    : Scene(pGame, pResources, name)
{
}

TitleScene::~TitleScene()
{
    Cleanup();
}

void TitleScene::LoadContent()
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

        GameObject* pTitleScreen = new GameObject(this, "TitleScreen", vec3(0,0,0), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Screen"),
            m_pResources->GetMaterial("Start"));
        AddGameObject(pTitleScreen);

        GameObject* pRedEmerald = new GameObject(this, "RedEmerald", vec3(0.25, 3.5, -5), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Emerald"),
            m_pResources->GetMaterial("RedEmerald"));
        AddGameObject(pRedEmerald);

        GameObject* pBlueEmerald = new GameObject(this, "BlueEmerald", vec3(2.5, 2.0, -5), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Emerald"),
            m_pResources->GetMaterial("BlueEmerald"));
        AddGameObject(pBlueEmerald);

        GameObject* pGreenEmerald = new GameObject(this, "GreenEmerald", vec3(3.0f, 0.0, -5), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Emerald"),
            m_pResources->GetMaterial("GreenEmerald"));
        AddGameObject(pGreenEmerald);

        GameObject* pTealEmerald = new GameObject(this, "TealEmerald", vec3(0.25, -2.5, -5), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Emerald"),
            m_pResources->GetMaterial("TealEmerald"));
        AddGameObject(pTealEmerald);

        GameObject* pPurpleEmerald = new GameObject(this, "PurpleEmerald", vec3(-2.0, 2.0, -5), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Emerald"),
            m_pResources->GetMaterial("PurpleEmerald"));
        AddGameObject(pPurpleEmerald);

        GameObject* pYellowEmerald = new GameObject(this, "YellowEmerald", vec3(-2.0, 0.0, -5), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Emerald"),
            m_pResources->GetMaterial("YellowEmerald"));
        AddGameObject(pYellowEmerald);

        GameObject* pWhiteEmerald = new GameObject(this, "WhiteEmerald", vec3(0.5, 0.5, -5), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Emerald"),
            m_pResources->GetMaterial("WhiteEmerald"));
        AddGameObject(pWhiteEmerald);
    }
}

void TitleScene::OnEvent(Event* pEvent)
{
    Scene::OnEvent(pEvent);
}

void TitleScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    //Emerald Spin
    {
        static float z = 0;
        z++;

        GameObject* pRed = GetGameObjectByName("RedEmerald");
        pRed->SetRotation(vec3(0, 0, z));
        GameObject* pBlue = GetGameObjectByName("BlueEmerald");
        pBlue->SetRotation(vec3(0, 0, z));
        GameObject* pGreen = GetGameObjectByName("GreenEmerald");
        pGreen->SetRotation(vec3(0, 0, z));
        GameObject* pTeal = GetGameObjectByName("TealEmerald");
        pTeal->SetRotation(vec3(0, 0, z));
        GameObject* pPurple = GetGameObjectByName("PurpleEmerald");
        pPurple->SetRotation(vec3(0, 0, z));
        GameObject* pYellow = GetGameObjectByName("YellowEmerald");
        pYellow->SetRotation(vec3(0, 0, z));
        GameObject* pWhite = GetGameObjectByName("WhiteEmerald");
        pWhite->SetRotation(vec3(0, 0, z));
    }
}

void TitleScene::Draw()
{
    Scene::Draw();
}
