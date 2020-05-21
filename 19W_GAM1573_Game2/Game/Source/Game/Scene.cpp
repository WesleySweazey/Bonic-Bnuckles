#include "GamePCH.h"

#include "Game.h"
#include "Game/ResourceManager.h"
#include "Game/ObjectPool.h"
#include "Scene.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/Player.h"
#include "BulletManager/BulletManager.h"
#include "GameObjects/LightObject.h"
#include "Audio/Cue.h"
#include "Audio/ShuffleCue.h"
#include "Audio/WeightedCue.h"
#include "Audio/SoundPlayer.h"
#include "Audio/SoundCueObject.h"

Scene::Scene(Game* pGame, ResourceManager* pResources, std::string name)
{
    m_pGame = pGame;
    m_pResources = pResources;
    m_Name = name;
    m_pSoundPlayer = nullptr;
    m_pBulletManager = nullptr;
    m_IsActive = false;
    m_Opaque = false;

    m_pShuffleCue = nullptr;
    m_pWeightedCue = nullptr;
}

Scene::~Scene()
{
    Cleanup();
}

void Scene::Cleanup()
{
    if (m_pBulletManager)
    {
        m_pBulletManager = NULL;
        delete m_pBulletManager;
    }
    int gameobjectindex = 0;
    for( auto pObject: m_pGameObjects )
    {
        gameobjectindex++;
        //pObject = NULL;
        //RemoveGameObject(pObject);
        delete pObject;
    }
    m_pGameObjects.clear();
    if (m_pSoundPlayer)
    {
        m_pSoundPlayer = NULL;
        delete m_pSoundPlayer;
    }
    if (m_pShuffleCue)
    {
        m_pShuffleCue = NULL;
        delete m_pShuffleCue;
    }
    if (m_pWeightedCue)
    {
        m_pWeightedCue = NULL;
        delete m_pWeightedCue;
    }
}

void Scene::LoadContent()
{
    m_pBulletManager = new BulletManager();
}

void Scene::CreateLights()
{
    /*LightObject* light0 = new LightObject("Light0", vec3(0.0f, 45.0f, 0.0f), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 200.0f, 0.25f, true, vec3(1.0f, 1.0f, 1.0f), this);
    m_pGameObjects.push_back(light0);
    LightObject* light1 = new LightObject("Light1", vec3(0.0f, 45.0f, 30.0f), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 100.0f, 0.25f, true, vec3(1.0f, 1.0f, 1.0f), this);
    m_pGameObjects.push_back(light1);
    LightObject* light2 = new LightObject("Light2", vec3(0.0f, 45.0f, -30.0f), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 20.0f, 0.25f, false, vec3(0.0f, 1.0f, 0.0f), this);
    m_pGameObjects.push_back(light2);
    LightObject* light3 = new LightObject("Light3", vec3(30.0f, 45.0f, 0.0), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 20.0f, 0.25f, false, vec3(1.0f, 1.0f, 0.0f), this);
    m_pGameObjects.push_back(light3);*/
}

void Scene::CreateSoundCues()
{
    m_pWeightedCue = new WeightedCue(m_pSoundPlayer);
    m_pWeightedCue->AddSound(m_pResources->GetSoundCueObject("Powerup"));
    m_pWeightedCue->AddSound(m_pResources->GetSoundCueObject("ErrorSound"));
    m_pWeightedCue->AddSound(m_pResources->GetSoundCueObject("LongWhistle"));
    m_pWeightedCue->AddSound(m_pResources->GetSoundCueObject("Wind"));
    m_pWeightedCue->AddSound(m_pResources->GetSoundCueObject("PickupCoin"));

    m_pShuffleCue = new ShuffleCue(m_pSoundPlayer);
    m_pShuffleCue->AddSound(m_pResources->GetSoundCueObject("Powerup"));
    m_pShuffleCue->AddSound(m_pResources->GetSoundCueObject("ErrorSound"));
    m_pShuffleCue->AddSound(m_pResources->GetSoundCueObject("LongWhistle"));
    m_pShuffleCue->AddSound(m_pResources->GetSoundCueObject("Wind"));
    m_pShuffleCue->AddSound(m_pResources->GetSoundCueObject("PickupCoin"));
}

void Scene::CreateSoundPlayer()
{
    m_pSoundPlayer = new SoundPlayer();
    SoundObject * LoadSoundObject;

    LoadSoundObject = m_pSoundPlayer->LoadSound("Data/Audio/Powerup.wav");
    SoundCueObject* newSoundCueObject1 = new SoundCueObject(1, 1, LoadSoundObject);
    m_pResources->AddSoundCueObject("Powerup", newSoundCueObject1);

    LoadSoundObject = m_pSoundPlayer->LoadSound("Data/Audio/ErrorSound.wav");
    SoundCueObject* newSoundCueObject2 = new SoundCueObject(1, 1, LoadSoundObject);
    m_pResources->AddSoundCueObject("ErrorSound", newSoundCueObject2);

    LoadSoundObject = m_pSoundPlayer->LoadSound("Data/Audio/LongWhistle.wav");
    SoundCueObject* newSoundCueObject3 = new SoundCueObject(1, 1, LoadSoundObject);
    m_pResources->AddSoundCueObject("LongWhistle", newSoundCueObject3);

    LoadSoundObject = m_pSoundPlayer->LoadSound("Data/Audio/Wind.wav");
    SoundCueObject* newSoundCueObject4 = new SoundCueObject(1, 1, LoadSoundObject);
    m_pResources->AddSoundCueObject("Wind", newSoundCueObject4);

    LoadSoundObject = m_pSoundPlayer->LoadSound("Data/Audio/PickupCoin.wav");
    SoundCueObject* newSoundCueObject5 = new SoundCueObject(1, 1, LoadSoundObject);
    m_pResources->AddSoundCueObject("PickupCoin", newSoundCueObject5);

    LoadSoundObject = m_pSoundPlayer->LoadSound("Data/Audio/SonicRingSoundEffect.wav");
    SoundCueObject* newSoundCueObject6 = new SoundCueObject(1, 1, LoadSoundObject);
    m_pResources->AddSoundCueObject("SonicRingSoundEffect", newSoundCueObject6);
}

void Scene::Reset()
{
    // Reset all of the Scene objects in the list.
    for( auto pObject: m_pGameObjects )
    {
        pObject->Reset();
    }
}

void Scene::OnEvent(Event* pEvent)
{
    // Send the event to Scene objects in the list.
    for( auto pObject: m_pGameObjects )
    {
        pObject->OnEvent( pEvent );
    }
}

void Scene::Update(float deltaTime)
{
    CheckForGLErrors();

    m_pBulletManager->update(deltaTime);
    int sizeOfGameObjList = m_pGameObjects.size();

    // Update all of the Scene objects in the list.
    for( unsigned int i=0; i<m_pGameObjects.size(); i++ )
    {
        m_pGameObjects[i]->Update( deltaTime );
    }

    CheckForGLErrors();
}

void Scene::Draw()
{
    CheckForGLErrors();

    CameraObject* pCamera = static_cast<CameraObject*>( GetGameObjectByName( "Camera" ) );
    assert( pCamera );
    LightObject* light = dynamic_cast<LightObject*>(GetGameObjectByName("Light0"));
    if (light)
    {
        LightObject* lights[5];
        for (int i = 0; i < 5; i++)
        {
            lights[i] = dynamic_cast<LightObject*>(GetGameObjectByName("Light" + std::to_string(i)));
        }
        // Render all of the Scene objects in the list.
        for (auto pObject : m_pGameObjects)
        {
            pObject->Draw(pCamera, lights);
        }
    }
    else
        for (auto pObject : m_pGameObjects)
        {
            pObject->Draw(pCamera, nullptr);
        }
    CheckForGLErrors();
}

void Scene::AddGameObject(GameObject* pObject)
{
    m_pGameObjects.push_back( pObject );
}

bool Scene::RemoveGameObject(GameObject* pObject)
{
    //auto iteratorForObject = std::find( m_pGameObjects.begin(), m_pGameObjects.end(), pObject );
    auto iteratorForObject = std::find(m_pGameObjects.begin(), m_pGameObjects.end(), pObject);
    //if (pObject->GetName() == "Player")
    //{
    //    m_pBulletManager->GetDynamicWorld()->removeRigidBody(pObject->GetRigidBody());
    //    //btRigidBody* rb = pObject->GetRigidBody();
    //    //rb->getWor
    //    //.removeCollisionObject();
    //}
    if( iteratorForObject != m_pGameObjects.end() )
    {
        m_pGameObjects.erase( iteratorForObject );
        return true;
    }

    return false;
}

bool Scene::IsGameObjectInScene(GameObject* pObject)
{
    auto iteratorForObject = std::find( m_pGameObjects.begin(), m_pGameObjects.end(), pObject );

    if( iteratorForObject != m_pGameObjects.end() )
    {
        return true;
    }

    return false;
}

GameObject* Scene::GetGameObjectByName(std::string name)
{
    for( auto pObject: m_pGameObjects )
    {
        if( pObject->GetName() == name )
        {
            return pObject;
        }
    }

    return nullptr;
}

void Scene::ImGuiSoundTab()
{
    ImGui::Begin("SoundsTab");
    if (ImGui::CollapsingHeader("SoundsTab"))
    {
        //Enabled
        ImGui::PushID(" Cue ");
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3.0f / 7.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3.0f / 7.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3.0f / 7.0f, 0.5f, 0.5f));
        ImGui::Button(" Cue ");
        if (ImGui::IsItemClicked(0))
        {
            //_pSoundPlayer->PlaySound(m_NormalCue);
            m_pSoundPlayer->PlaySound(m_pShuffleCue);
            m_pSoundPlayer->PlaySound(m_pWeightedCue);
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();

        ImGui::PushID(" ShuffleCue ");
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3.0f / 7.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3.0f / 7.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3.0f / 7.0f, 0.5f, 0.5f));
        ImGui::Button(" ShuffleCue ");
        if (ImGui::IsItemClicked(0))
        {
            m_pSoundPlayer->PlaySound(m_pShuffleCue);
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();

        ImGui::PushID(" WeightedCue ");
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3.0f / 7.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3.0f / 7.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3.0f / 7.0f, 0.5f, 0.5f));
        ImGui::Button(" WeightedCue ");
        if (ImGui::IsItemClicked(0))
        {
            m_pSoundPlayer->PlaySound(m_pWeightedCue);
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }
    ImGui::End();
}