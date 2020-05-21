#include "GamePCH.h"

#include "Game/UI/Health.h"
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/Player.h"
#include "Game/Scene.h"
#include "Game/ResourceManager.h"
#include "GameObjects/GameObject.h"
#include <string>

Health::Health(std::string name, vec3 position, vec3 rotation, vec3 scale, ResourceManager* pResources, Scene* pScene, int InitalHealth, int MaxHealth)
{
    m_pScene = pScene;
    m_pResources = pResources;
    m_Position = position;
    m_CurrentHealth = InitalHealth;
    m_MaxHealth = MaxHealth;
    m_win = false;
    m_lose = false;
    // Set the Player's initial position.
    //m_Position=(position);
    //m_IsTouching = false;
    for (int i = 0; i < m_MaxHealth; i++)
    {
        std::string HealthBoxname = "HealthBox" + std::to_string(i);
        m_pHealthGameObjects.push_back(new GameObject(m_pScene, HealthBoxname, vec3(1.0f + i, 2.0f, 0.0f), vec3(0.0f, 0.0f, 0.0), vec3(1.0f, 1.0f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("HealthMaterial")));
    }
    //m_pScreen = new GameObject(m_pScene,"Screen", vec3(5.0f, 5.0f, 1.0f), vec3(0.0f, 1.0f, 0.0), vec3(0.0f, 0.0f, 0.0), m_pResources->GetMesh("ScreenMesh"), m_pResources->GetMaterial("WinMaterial"));
}

Health::~Health()
{
    for (auto object : m_pHealthGameObjects)
    {
        if (object)
        {
            object = NULL;
            delete object;
        }
    }
}

void Health::Update(float deltatime)
{
}
void Health::Draw(CameraObject* pCamera)
 {
    
    /*if (m_CurrentHealth == 0)
    {
        m_lose = true;
        m_pScreen->SetMaterial(m_pResources->GetMaterial("LoseMaterial"));
        m_pScreen->Draw(pCamera, nullptr);
    }
    if (m_win == true)
    {
        m_pScreen->SetMaterial(m_pResources->GetMaterial("WinMaterial"));
        m_pScreen->Draw(pCamera, nullptr);
    }
    else
    {*/
        for (int i = 0; i < m_CurrentHealth; i++)
        {
            m_pHealthGameObjects[i]->Draw(pCamera,nullptr);
        }
    //}
}