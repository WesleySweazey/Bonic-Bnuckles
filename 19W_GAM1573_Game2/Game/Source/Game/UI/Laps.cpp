#include "GamePCH.h"

#include "Game/UI/Laps.h"
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/Player.h"
#include "Game/Scene.h"
#include "Game/ResourceManager.h"
#include "GameObjects/GameObject.h"
#include <string>

Laps::Laps(std::string name, vec3 position, vec3 rotation, vec3 scale, ResourceManager* pResources, Scene* pScene, int totalLaps)
{
    m_pScene = pScene;
    m_pResources = pResources;
    m_Position = position;
    m_currentLap = 0;
    m_totalLaps = totalLaps;
    for (int i = 0; i < 3; i++)
    {
        std::string lapBoxname = "LapBox" + std::to_string(i);
        switch (i)
        {
        case 0:
            m_pLapGameObjects.push_back(new GameObject(m_pScene, lapBoxname, vec3(1.0f + i, 3.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("ZeroMaterial")));
            SetCurrentLapValue();
            break;
        case 1:
            m_pLapGameObjects.push_back(new GameObject(m_pScene, lapBoxname, vec3(1.0f + i, 3.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("SlashMaterial")));
            break;
        case 2:
            m_pLapGameObjects.push_back(new GameObject(m_pScene, lapBoxname, vec3(1.0f + i, 3.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("ThreeMaterial")));
            SetTotalLapValue();
            break;
        }
    }

}

Laps::~Laps()
{
    for (auto object : m_pLapGameObjects)
    {
        if (object)
        {
            object = NULL;
            delete object;
        }
    }
}

void Laps::Update(float deltatime)
{
    
}

void Laps::SetCurrentLapValue()
{
    switch (m_currentLap)
    {
    case 0:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("ZeroMaterial"));
        break;
    case 1:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("OneMaterial"));
        break;
    case 2:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("TwoMaterial"));
        break;
    case 3:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("ThreeMaterial"));
        break;
    case 4:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("FourMaterial"));
        break;
    case 5:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("FiveMaterial"));
        break;
    case 6:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("SixMaterial"));
        break;
    case 7:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("SevenMaterial"));
        break;
    case 8:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("EightMaterial"));
        break;
    case 9:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("NineMaterial"));
        break;
    default:
        m_pLapGameObjects[0]->SetMaterial(m_pResources->GetMaterial("ZeroMaterial"));
        break;
    }
}

void Laps::Draw(CameraObject* pCamera)
{
    for (int i = 0; i < 3; i++)
    {
        m_pLapGameObjects[i]->Draw(pCamera, nullptr);
    }
}

void Laps::SetTotalLapValue()
{
    switch (m_totalLaps)
    {
    case 0:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("ZeroMaterial"));
        break;
    case 1:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("OneMaterial"));
        break;
    case 2:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("TwoMaterial"));
        break;
    case 3:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("ThreeMaterial"));
        break;
    case 4:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("FourMaterial"));
        break;
    case 5:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("FiveMaterial"));
        break;
    case 6:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("SixMaterial"));
        break;
    case 7:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("SevenMaterial"));
        break;
    case 8:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("EightMaterial"));
        break;
    case 9:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("NineMaterial"));
        break;
    default:
        m_pLapGameObjects[2]->SetMaterial(m_pResources->GetMaterial("ZeroMaterial"));
        break;
    }
}