#include "GamePCH.h"

#include "HUD.h"
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
#include "Game/UI/Health.h"
#include "Game/UI/Score.h"
#include "Game/UI/Laps.h"
#include "Game/UI/Time.h"

HUD::HUD(Game* pGame, ResourceManager* pResources, std::string name, Player* pPlayer)
    : Scene(pGame, pResources, name)
{
    m_pPlayer = pPlayer;
}

HUD::~HUD()
{
    Cleanup();
    if (m_pTime)
    {
        m_pTime = nullptr;
        delete m_pTime;
    }
    if (m_pScore)
    {
        m_pScore = nullptr;
        delete m_pScore;
    }
    if (m_pLaps)
    {
        m_pLaps = nullptr;
        delete m_pLaps;
    }
}

void HUD::LoadContent()
{
    Scene::LoadContent();
    // Create our GameObjects.
    {
        // Camera.
        float width = (float)m_pGame->GetFramework()->GetWindowWidth();
        float height = (float)m_pGame->GetFramework()->GetWindowHeight();

        float aspect = width / height;

        OrthoCameraObject* pCamera = new OrthoCameraObject(this, "OrthoCamera", vec3(0, 0, -15), vec3(0, 0, 0), vec3(1, 1, 1));
        pCamera->GetViewMatrix()->SetIdentity();
        pCamera->GetProjMatrix()->CreateOrtho(0, 9 * aspect, 0, 9, 0, 5);
        AddGameObject(pCamera);
        //Health
        /*m_pHealth = new Health("Health", vec3(0, 0, 0), vec3(5, 5, 0), vec3(1, 1, 1), m_pResources, this, 2,2);
        for (unsigned int i = 0; i < m_pHealth->GetHealthSize(); i++)
        {
            AddGameObject(m_pHealth->GetObjectByIndex(i));
        }*/
        //Score
        m_pScore = new Score("Scores", vec3(0, 0, 0), vec3(5, 4, 0), vec3(1, 1, 1), m_pResources, this);
        m_pScore->SetValue(0);
        for (unsigned int i = 0; i < m_pScore->GetScoreSize(); i++)
        {
            AddGameObject(m_pScore->GetObjectByIndex(i));
        }
        m_pPlayer->SetScore(m_pScore);
        //Time 
        m_pTime = new Time("Time", vec3(0, 0, 0), vec3(5, 5, 0), vec3(1, 1, 1), m_pResources, this);
        for (unsigned int i = 0; i < m_pTime->GetTimeSize(); i++)
        {
            AddGameObject(m_pTime->GetObjectByIndex(i));
        }
        m_pPlayer->SetTime(m_pTime);
        //Number of laps
        m_pLaps = new Laps("Laps", vec3(0, 0, 0), vec3(5, 5, 0), vec3(1, 1, 1), m_pResources, this, 3);
        for (unsigned int i = 0; i < m_pLaps->GetLapSize(); i++)
        {
            AddGameObject(m_pLaps->GetObjectByIndex(i));
        }
        m_pPlayer->SetLaps(m_pLaps);
    }
}

void HUD::OnEvent(Event* pEvent)
{
    Scene::OnEvent(pEvent);
}

void HUD::Update(float deltaTime)
{
    Scene::Update(deltaTime);
    //m_pHealth->Update(deltaTime);
    m_pScore->Update(deltaTime);
    m_pLaps->Update(deltaTime);
    m_pTime->Update(deltaTime);
}

void HUD::Draw()
{
    //Scene::Draw();
    OrthoCameraObject* pCamera = (OrthoCameraObject*)GetGameObjectByName("OrthoCamera");
    //m_pHealth->Draw(pCamera);
    m_pScore->Draw(pCamera);
    m_pLaps->Draw(pCamera);
    m_pTime->Draw(pCamera);
}

void HUD::Reset()
{
    m_pScore->SetCurrentScore(0);
    m_pLaps->SetCurrentLapNum(0);
    m_pTime->SetValue(0.0f);
}
