#include "GamePCH.h"

#include "GameScene.h"
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
#include "GameObjects/Coin.h"
#include "GameObjects/StartObject.h"
#include "GameObjects/CheckPointObject.h"
#include "GameObjects/LightObject.h"
#include <time.h>

GameScene::GameScene(Game* pGame, ResourceManager* pResources, std::string name)
    : Scene(pGame, pResources, name)
{
    srand(time(NULL));
    m_CoinCue = nullptr;
    m_BoosterCue = nullptr;
}

GameScene::~GameScene()
{
    delete m_CoinCue;
    delete m_BoosterCue;
    Cleanup();
}

void GameScene::LoadContent()
{
    Scene::LoadContent();
    CreateSoundPlayer();
    CreateSoundCues();
    //CreateLights();

    LightObject* light0 = new LightObject("Light0", vec3(0.0f, 45.0f, 0.0f), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 200.0f, 0.25f, true, vec3(1.0f, 1.0f, 1.0f), this);
    AddGameObject(light0);
    LightObject* light1 = new LightObject("Light1", vec3(0.0f, 45.0f, 30.0f), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 100.0f, 0.25f, true, vec3(1.0f, 1.0f, 1.0f), this);
    AddGameObject(light1);
    LightObject* light2 = new LightObject("Light2", vec3(0.0f, 45.0f, -30.0f), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 20.0f, 0.25f, false, vec3(0.0f, 1.0f, 0.0f), this);
    AddGameObject(light2);
    LightObject* light3 = new LightObject("Light3", vec3(30.0f, 45.0f, 0.0), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 20.0f, 0.25f, false, vec3(1.0f, 1.0f, 0.0f), this);
    AddGameObject(light3);
    LightObject* light4 = new LightObject("Light4", vec3(0.0f, 2.0f, -6.0), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 20.0f, 0.25f, true, vec3(1.0f, 1.0f, 1.0f), this);
    AddGameObject(light4);

    //Create sound cue
    m_CoinCue = new Cue(m_pSoundPlayer);
    m_CoinCue->AddSound(m_pResources->GetSoundCueObject("SonicRingSoundEffect"));
    //Create sound cue
    m_BoosterCue = new Cue(m_pSoundPlayer);
    m_BoosterCue->AddSound(m_pResources->GetSoundCueObject("Powerup"));

    // Create our GameObjects.
    {
        // Camera.
        float width = (float)m_pGame->GetFramework()->GetWindowWidth();
        float height = (float)m_pGame->GetFramework()->GetWindowHeight();

        float aspect = width / height;

        //Camera
        CameraObject* pCamera = new CameraObject(this, "Camera", vec3(0, 0, -15), vec3(0, 0, 0), vec3(1, 1, 1));
        pCamera->GetViewMatrix()->SetIdentity();
        pCamera->GetProjMatrix()->CreateOrtho(0, 9 * aspect, 0, 9, 0, 5);
        AddGameObject(pCamera);

        GameObject* pSkyBox = new GameObject(this, "SkyBox", vec3(0, 0, 0.0), vec3(0, 0, 0), vec3(1, 1, 1), m_pResources->GetMesh("SkyBox"), m_pResources->GetMaterial("Sky"));
        AddGameObject(pSkyBox);

        //Coins
        Coin* pCoin = new Coin(this, "Coin", vec3(130.0f, 13.5f, 20.0f), vec3(0, 90.0f, 0), vec3(1, 1, 1), m_pResources->GetMesh("RingOBJ"), m_pResources->GetMaterial("CoinMaterial"));
        pCoin->CreateRigidBody(true, "Player", 0.0f, true, false);
        pCoin->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = COIN;
        pCoin->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = FLOOR | PLAYER | SPHERE | COIN;
        AddGameObject(pCoin);

        Coin* pCoin1 = new Coin(this, "Coin1", vec3(130.0f, 11.0f, 40.0f), vec3(0, 90.0f, 0), vec3(1, 1, 1), m_pResources->GetMesh("RingOBJ"), m_pResources->GetMaterial("CoinMaterial"));
        pCoin1->CreateRigidBody(true, "Player", 0.0f, true, false);
        pCoin1->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = COIN;
        pCoin1->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = FLOOR | PLAYER | SPHERE | COIN;
        AddGameObject(pCoin1);

        Coin* pCoin2 = new Coin(this, "Coin2", vec3(130.0f, 10.0f, 80.0f), vec3(0, 90.0f, 0), vec3(1, 1, 1), m_pResources->GetMesh("RingOBJ"), m_pResources->GetMaterial("CoinMaterial"));
        pCoin2->CreateRigidBody(true, "Player", 0.0f, true, false);
        pCoin2->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = COIN;
        pCoin2->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = FLOOR | PLAYER | SPHERE | COIN;
        AddGameObject(pCoin2);

        Coin* pCoin3 = new Coin(this, "Coin3", vec3(130.0f, 10.0f, 90.0f), vec3(0, 90.0f, 0), vec3(1, 1, 1), m_pResources->GetMesh("RingOBJ"), m_pResources->GetMaterial("CoinMaterial"));
        pCoin3->CreateRigidBody(true, "Player", 0.0f, true, false);
        pCoin3->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = COIN;
        pCoin3->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = FLOOR | PLAYER | SPHERE | COIN;
        AddGameObject(pCoin3);

        for (int i = 4; i < 20; i++)
        {
            Coin* pCoin = new Coin(this, "Coin"+i, vec3((rand()% 230) - 140, (rand() % 20) + 10, (rand() % 230) - 140), vec3(0, (rand() % 360), 0), vec3(1, 1, 1), m_pResources->GetMesh("RingOBJ"), m_pResources->GetMaterial("CoinMaterial"));
            pCoin->CreateRigidBody(true, "Player", 0.0f, true, false);
            pCoin->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = COIN;
            pCoin->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = FLOOR | PLAYER | SPHERE | COIN;
            AddGameObject(pCoin);
        }

        //Player
        Player* pPlayer = new Player(this, "Player", vec3(130.0f, 30.0f, -30.0f), vec3(0, 0, 0), vec3(1, 1, 1), m_pResources->GetMesh("Bonic"), m_pResources->GetMaterial("Sonic"));
        pPlayer->CreateRigidBody(true, "Player", 10.0f, false, true);
        pPlayer->GetRigidBody()->setFriction(1.0f);
        pPlayer->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = PLAYER;
        pPlayer->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = FLOOR | PLAYER | SPHERE | CHECKPOINT | START | BOX;
        // Assign our controllers.
        pPlayer->SetPlayerController(m_pGame->GetController(0));
        AddGameObject(pPlayer);

        //Terrain
        GameObject* pPlatform = new GameObject(this, "Floor", vec3(0, 0, 0.0), vec3(0, 0, 0), vec3(1, 1, 1), m_pResources->GetMesh("TerrainOBJ"), m_pResources->GetMaterial("FloorColor"));
        pPlatform->CreateRigidBody(false, "Ground", 0.0f, false, false);
        pPlatform->GetRigidBody()->setFriction(1.0f);
        pPlatform->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = FLOOR;
        pPlatform->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = PLAYER | FLOOR | BOX | SPHERE;
        AddGameObject(pPlatform);

        //StartObject
        StartObject* pStartObject = new StartObject(this, "StartObject", vec3(130.0f, 21.0f, -20.0f), vec3(0, 90, 0), vec3(10, 10, 10), m_pResources->GetMesh("RingOBJ"), m_pResources->GetMaterial("CheckeredMaterial"));
        pStartObject->CreateRigidBody(false, "CheckPointCollision", 0.0f, true, false);
        pStartObject->GetRigidBody()->setFriction(1.0f);
        pStartObject->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = START;
        pStartObject->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = PLAYER | START | FLOOR;
        AddGameObject(pStartObject);

        //CheckPointObject
        CheckPointObject* pCheckPointObject = new CheckPointObject(this, "CheckPointObject", vec3(-110.0f, 21.0f, -30.0f), vec3(0, 90, 0), vec3(10, 10, 10), m_pResources->GetMesh("RingOBJ"), m_pResources->GetMaterial("CheckeredMaterial"), 1);
        pCheckPointObject->CreateRigidBody(false, "CheckPointCollision", 0.0f, true, false);
        pCheckPointObject->GetRigidBody()->setFriction(1.0f);
        pCheckPointObject->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = CHECKPOINT;
        pCheckPointObject->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = PLAYER | CHECKPOINT | FLOOR;
        AddGameObject(pCheckPointObject);

        GameObject* pWreakingBall = new GameObject(this, "WreakingBall", vec3(75.0f, 16.0f, 122.0f), vec3(0, 90, 0), vec3(5, 5, 5), m_pResources->GetMesh("Sphere"), m_pResources->GetMaterial("Black"));
        pWreakingBall->CreateRigidBody(true, "WreakingBall", 1.0f, false, false);
        pWreakingBall->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = BOX;
        pWreakingBall->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = BOX | PLAYER;
        AddGameObject(pWreakingBall);

        const btVector3 btPivotA(00.0f, 10.0f, 0.0f);
        btVector3 btAxisA(0.0f, 0.0f, 1.0f);
#undef new
        btHingeConstraint * pHinge = new btHingeConstraint(*pWreakingBall->GetRigidBody(), btPivotA, btAxisA);
#define new new(__FILE__, __LINE__)
        pHinge->enableAngularMotor(true, 50.0f, 10.0f);
        m_pBulletManager->GetDynamicWorld()->addConstraint(pHinge);
        pHinge->setDbgDrawSize(btScalar(1000.f));

        GameObject* pWreakingBall2 = new GameObject(this, "WreakingBall2", vec3(-70.0f, 13.0f, -100.0f), vec3(0, 0, 0), vec3(5, 5, 5), m_pResources->GetMesh("Sphere"), m_pResources->GetMaterial("Black"));
        pWreakingBall2->CreateRigidBody(true, "WreakingBall", 1.0f, false, false);
        pWreakingBall2->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = BOX;
        pWreakingBall2->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = FLOOR | BOX | PLAYER;
        AddGameObject(pWreakingBall2);

        const btVector3 btPivotA2(00.0f, 10.0f, 0.0f);
        btVector3 btAxisA2(0.0f, 0.0f, 1.0f);
#undef new
        btHingeConstraint * pHinge2 = new btHingeConstraint(*pWreakingBall2->GetRigidBody(), btPivotA2, btAxisA2);
#define new new(__FILE__, __LINE__)
        pHinge2->enableAngularMotor(true, 50.0f, 10.0f);
        m_pBulletManager->GetDynamicWorld()->addConstraint(pHinge2);
        pHinge2->setDbgDrawSize(btScalar(1000.f));

        GameObject* pDashPad = new GameObject(this, "1DashPad", vec3(130.0f, 18.0f, -8.0f), vec3(-90, 0, 0), vec3(5, 5, 5), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("DashPad"));
        pDashPad->CreateRigidBody(true, "Dash", 0.0f, true, false);
      
        AddGameObject(pDashPad);

        GameObject* pDashPad2 = new GameObject(this, "2DashPad", vec3(110.0f, 8.0f, 120.0f), vec3(-90, 90, 0), vec3(5, 5, 5), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("DashPad"));
        pDashPad2->CreateRigidBody(true, "Dash", 0.0f, true, false);

        AddGameObject(pDashPad2);

        GameObject* pDashPad3 = new GameObject(this, "3DashPad", vec3(-90.0f, 10.0f, 130.0f), vec3(-90, 180, 0), vec3(5, 5, 5), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("DashPad"));
        pDashPad3->CreateRigidBody(true, "Dash", 0.0f, true, false);

        AddGameObject(pDashPad3);

        GameObject* pDashPad4 = new GameObject(this, "4DashPad", vec3(-55.0f, 9.0f, -130.0f), vec3(-90, 270, 0), vec3(5, 5, 5), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("DashPad"));
        pDashPad4->CreateRigidBody(true, "Dash", 0.0f, true, false);

        AddGameObject(pDashPad4);

        pCamera->SetObjectToFollow(pPlayer, 10);
    }
}

void GameScene::OnEvent(Event* pEvent)
{
    Scene::OnEvent(pEvent);
}

void GameScene::Update(float deltaTime)
{
    Scene::Update(deltaTime);

    //ImGuiSoundTab();
}

void GameScene::Draw()
{
    Scene::Draw();
}

void GameScene::Reset()
{
    GameObject* pPlayer = GetGameObjectByName("Player");
    pPlayer->SetPosition(vec3(130.0f, 30.0f, -30.0f));
    btRigidBody* rb = pPlayer->GetRigidBody();
    //RemoveGameObject(player);

    //delete player;
    m_pBulletManager->GetDynamicWorld()->removeRigidBody(rb);
    pPlayer->SetRigidBody(nullptr);
    //Player* pPlayer = new Player(this, "Player", vec3(130.0f, 30.0f, -30.0f), vec3(0, 0, 0), vec3(1, 1, 1), m_pResources->GetMesh("Bonic"), m_pResources->GetMaterial("Sonic"));
    pPlayer->CreateRigidBody(true, "Player", 10.0f, false, true);
    pPlayer->GetRigidBody()->setFriction(1.0f);
    pPlayer->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterGroup = PLAYER;
    pPlayer->GetRigidBody()->getBroadphaseProxy()->m_collisionFilterMask = FLOOR | PLAYER | SPHERE | CHECKPOINT | START | BOX;
    // Assign our controllers.

    CameraObject* pCamera = (CameraObject*)GetGameObjectByName("Camera");
    pCamera->SetObjectToFollow(pPlayer, 10);

   /* GameObject* player = GetGameObjectByName("Player");
    if (player)
    {
        player->SetPosition(vec3(130.0f, 30.0f, -30.0f));

    }*/
}