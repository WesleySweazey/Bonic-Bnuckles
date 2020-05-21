#include "GamePCH.h"

#include "PauseScene.h"
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

PauseScene::PauseScene(Game* pGame, ResourceManager* pResources, std::string name)
    : Scene(pGame, pResources, name)
{
    m_Opaque = true;
}

PauseScene::~PauseScene()
{
    Cleanup();
}

void PauseScene::LoadContent()
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

        GameObject* pPauseScreen = new GameObject(this, "PauseScreen", vec3(0,0,-12)/*vec3(12, 6.5, 5)*/, vec3(0, 0, 0), vec3(1, 1, 1),
            m_pResources->GetMesh("Box"),
            m_pResources->GetMaterial("Pause"));
        AddGameObject(pPauseScreen);
    }
}
void PauseScene::OnEvent(Event* pEvent)
{
    Scene::OnEvent(pEvent);
}

void PauseScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

  /*  GameObject* pScreen = GetGameObjectByName("PauseScreen");
   static float x = 0;
   static float y = 0;
   x++;
   y++;
   pScreen->SetRotation(vec3(x, y, 0));*/
}

void PauseScene::Draw()
{
    Scene::Draw();
}
