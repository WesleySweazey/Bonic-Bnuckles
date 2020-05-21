#include "GamePCH.h"

#include "Game/UI/Time.h"
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/Player.h"
#include "Game/Scene.h"
#include "Game/ResourceManager.h"
#include "GameObjects/GameObject.h"
#include <string>

Time::Time(std::string name, vec3 position, vec3 rotation, vec3 scale, ResourceManager* pResources, Scene* pScene)
{
    m_pScene = pScene;
    m_pResources = pResources;
    m_Position = position;
    
    for (int i = 0; i < 6; i++)
    {
        std::string TimeBoxname = "TimeBox" + std::to_string(i);
        m_pTimeGameObjects.push_back(new GameObject(m_pScene, TimeBoxname, vec3(8.0f + i*0.5f, 8.5f, 0.0f), vec3(0.0f, 0.0f, 0.0), vec3(1.0f, 1.0f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("TimeZeroMaterial")));
    }
    m_pTimeGameObjects[2]->SetMaterial(m_pResources->GetMaterial("TimeColonMaterial"));
    //m_pScreen = new GameObject(m_pScene,"Screen", vec3(5.0f, 5.0f, 1.0f), vec3(0.0f, 1.0f, 0.0), vec3(0.0f, 0.0f, 0.0), m_pResources->GetMesh("ScreenMesh"), m_pResources->GetMaterial("WinMaterial"));
    m_Start = false;
    m_TimeElapsed = 0.0;
}

Time::~Time()
{
    for (auto object : m_pTimeGameObjects)
    {
        if (object)
        {
            object = NULL;
            delete object;
        }
    }
}

void Time::Update(float deltatime)
{
    if (m_Start == true)
    {
        m_TimeElapsed += deltatime;
        int value = (int)m_TimeElapsed * 100;
        if (m_TimeElapsed < 999999)
        {
            for (int i = 5; i >= 0; i--)
            {
                if (i != 2)
                {
                    switch (value % 10)
                    {
                    case 0:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeZeroMaterial"));
                        break;
                    case 1:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeOneMaterial"));
                        break;
                    case 2:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeTwoMaterial"));
                        break;
                    case 3:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeThreeMaterial"));
                        break;
                    case 4:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeFourMaterial"));
                        break;
                    case 5:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeFiveMaterial"));
                        break;
                    case 6:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeSixMaterial"));
                        break;
                    case 7:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeSevenMaterial"));
                        break;
                    case 8:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeEightMaterial"));
                        break;
                    case 9:
                        m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeNineMaterial"));
                        break;
                    }
                    value /= 10;
                }
            }
        }
    }
}

void Time::Draw(CameraObject* pCamera)
{
    for (int i = 0; i < 6; i++)
    {
        m_pTimeGameObjects[i]->Draw(pCamera, nullptr);
    }
}

void Time::Start()
{
    m_Start = true;
}

void Time::Stop()
{
    m_Start = false;
}

void Time::SetValue(float value)
{
    m_TimeElapsed = value;
    int newValue = (int)m_TimeElapsed * 100;
    if (m_TimeElapsed < 999999)
    {
        for (int i = 5; i >= 0; i--)
        {
            if (i != 2)
            {
                switch (newValue % 10)
                {
                case 0:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeZeroMaterial"));
                    break;
                case 1:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeOneMaterial"));
                    break;
                case 2:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeTwoMaterial"));
                    break;
                case 3:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeThreeMaterial"));
                    break;
                case 4:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeFourMaterial"));
                    break;
                case 5:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeFiveMaterial"));
                    break;
                case 6:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeSixMaterial"));
                    break;
                case 7:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeSevenMaterial"));
                    break;
                case 8:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeEightMaterial"));
                    break;
                case 9:
                    m_pTimeGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TimeNineMaterial"));
                    break;
                }
                newValue /= 10;
            }
        }
    }

}