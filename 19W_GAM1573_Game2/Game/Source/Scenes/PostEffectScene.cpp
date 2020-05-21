#include "GamePCH.h"

#include "PostEffectScene.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/OrthoCameraObject.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "BulletManager/BulletManager.h"
#include "CollisionFilter/CollisionFilter.h"
#include "Audio/Cue.h"
#include "Audio/ShuffleCue.h"
#include "Audio/WeightedCue.h"
#include "Audio/SoundPlayer.h"

PostEffectScene::PostEffectScene(Game* pGame, ResourceManager* pResources, std::string name, Player* pPlayer)
    : Scene(pGame, pResources, name)
{
    HorizontalActive = false;
    VerticalActive = false;
    BlackandWhiteActive = false;
    m_pPlayer = pPlayer;
}

PostEffectScene::~PostEffectScene()
{
    Cleanup();
}

void PostEffectScene::LoadContent()
{
    Scene::LoadContent();
    // Create our GameObjects.
    {
        // Camera.
        float width = (float)m_pGame->GetFramework()->GetWindowWidth();
        float height = (float)m_pGame->GetFramework()->GetWindowHeight();

        float aspect = width / height;

        CameraObject* pCamera = new OrthoCameraObject(this, "OrthoCamera", vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
        pCamera->GetViewMatrix()->SetIdentity();
        pCamera->GetProjMatrix()->CreateOrtho(0, 16, 0, 9, 0, 5);
        AddGameObject(pCamera);

        GameObject* pBlurScreen = new GameObject(this, "pVerticalBlurScreen", vec3(13, 6.5, 0), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("PostScreen"),
            m_pResources->GetMaterial("VerticalBlur"));
        AddGameObject(pBlurScreen);

        GameObject* pBlurScreen2 = new GameObject(this, "pHorizontalBlurScreen", vec3(13, 6.5, 0), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("PostScreen"),
            m_pResources->GetMaterial("HorizontalBlur"));
        AddGameObject(pBlurScreen2);

        GameObject* pBlackandWhite = new GameObject(this, "BlackandWhite", vec3(13, 6.5, 0), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("PostScreen"),
            m_pResources->GetMaterial("BlackandWhite"));
        AddGameObject(pBlackandWhite);

        GameObject* pRender = new GameObject(this, "Render", vec3(13, 6.5, 0), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("PostScreen"),
            m_pResources->GetMaterial("Render"));
        AddGameObject(pRender);

        //pCamera->SetObjectToFollow(pRender, 10.0f);
    }
}

void PostEffectScene::OnEvent(Event* pEvent)
{
    Scene::OnEvent(pEvent);
}

void PostEffectScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    //ImGui::Begin("Blur");

    //ImGui::Checkbox("HorizontalActive", &HorizontalActive);
    //ImGui::Checkbox("VerticalActive", &VerticalActive);

    //ImGui::End();

    //ImGui::Begin("BlackandWhite");
    //ImGui::Checkbox("BlackandWhite", &BlackandWhiteActive);
    //ImGui::End();
}

void PostEffectScene::Draw()
{
    //Scene::Draw();
    if (HorizontalActive == true)
        GetGameObjectByName("pHorizontalBlurScreen")->Draw((CameraObject*)GetGameObjectByName("OrthoCamera"), nullptr);

    else if (VerticalActive == true)
        GetGameObjectByName("pVerticalBlurScreen")->Draw((CameraObject*)GetGameObjectByName("OrthoCamera"), nullptr);

    else if (BlackandWhiteActive == true || m_pPlayer->GetHealth() == 0)
        GetGameObjectByName("BlackandWhite")->Draw((CameraObject*)GetGameObjectByName("OrthoCamera"), nullptr);

    else
        GetGameObjectByName("Render")->Draw((CameraObject*)GetGameObjectByName("OrthoCamera"), nullptr);
}
