#include "GamePCH.h"

#include "Options.h"
#include "Game/Game.h"
#include "Game/ResourceManager.h"
#include "Game/Scene.h"
#include "Game/ObjectPool.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Player.h"
#include "BulletManager/BulletManager.h"
#include "CollisionFilter/CollisionFilter.h"
#include "Audio/Cue.h"
#include "Audio/ShuffleCue.h"
#include "Audio/WeightedCue.h"
#include "Audio/SoundPlayer.h"

OptionsScene::OptionsScene(Game* pGame, ResourceManager* pResources, std::string name, Player* pPlayer)
    : Scene(pGame, pResources, name)
{
    m_pPlayer = pPlayer;
}

OptionsScene::~OptionsScene()
{
}

void OptionsScene::LoadContent()
{
    m_pBulletManager = new BulletManager();
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

        GameObject* pOptionsScreen = new GameObject(this, "OptionsScreen", vec3(0,0,0), vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Screen"),
            m_pResources->GetMaterial("OptionsSonic"));
        AddGameObject(pOptionsScreen);

        //ImGuiSoundTab();

    }
}

void OptionsScene::OnEvent(Event* pEvent)
{
    GameObject* pOptions = GetGameObjectByName("OptionsScreen");
    Scene::OnEvent(pEvent);

    if (pEvent->GetEventType() == EventType_Input)
    {
        InputEvent* pInput = static_cast<InputEvent*>(pEvent);

        if (pInput->GetInputState() == InputState_Pressed)
        {
            if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_UP)
            {
                if (pOptions->GetMaterial() == m_pResources->GetMaterial("OptionsSonic"))
                    return;
                else if (pOptions->GetMaterial() == m_pResources->GetMaterial("OptionsKnuckles"))
                {
                    pOptions->SetMaterial(m_pResources->GetMaterial("OptionsSonic"));
                    m_pPlayer->SetMesh(m_pResources->GetMesh("Bonic"));
                    m_pPlayer->SetMaterial(m_pResources->GetMaterial("Sonic"));
                    return;
                }
                else if (pOptions->GetMaterial() == m_pResources->GetMaterial("OptionsSuper"))
                {
                    pOptions->SetMaterial(m_pResources->GetMaterial("OptionsKnuckles"));
                    m_pPlayer->SetMesh(m_pResources->GetMesh("Bnuckles"));
                    m_pPlayer->SetMaterial(m_pResources->GetMaterial("Knuckles"));
                    return;
                }
            }
            if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard && pInput->GetID() == VK_DOWN)
            {
                if (pOptions->GetMaterial() == m_pResources->GetMaterial("OptionsSuper"))
                    return;
                if (pOptions->GetMaterial() == m_pResources->GetMaterial("OptionsSonic"))
                {
                    pOptions->SetMaterial(m_pResources->GetMaterial("OptionsKnuckles"));
                    m_pPlayer->SetMesh(m_pResources->GetMesh("Bnuckles"));
                    m_pPlayer->SetMaterial(m_pResources->GetMaterial("Knuckles"));
                    return;
                }
                if (pOptions->GetMaterial() == m_pResources->GetMaterial("OptionsKnuckles"))
                {
                    pOptions->SetMaterial(m_pResources->GetMaterial("OptionsSuper"));
                    m_pPlayer->SetMesh(m_pResources->GetMesh("SuperBonic"));
                    m_pPlayer->SetMaterial(m_pResources->GetMaterial("Super"));
                    return;
                }
            }
        }
    }
}

void OptionsScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);
}

void OptionsScene::Draw()
{
    Scene::Draw();
}
