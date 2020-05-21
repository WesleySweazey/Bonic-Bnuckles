#include "GamePCH.h"

#include "Game/UI/Score.h"
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/Player.h"
#include "Game/Scene.h"
#include "Game/ResourceManager.h"
#include "GameObjects/GameObject.h"
#include <string>

Score::Score(std::string name, vec3 position, vec3 rotation, vec3 scale, ResourceManager* pResources, Scene* pScene)
{
    m_pScene = pScene;
    m_pResources = pResources;
    m_Position = position;

    for (int i = 0; i < 6; i++)
    {
        std::string scoreBoxname = "ScoreBox" + std::to_string(i);
        m_pScoreGameObjects.push_back(new GameObject(m_pScene, scoreBoxname, vec3(1.0f + i, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0), vec3(1.0f, 1.0f, 1.0f), m_pResources->GetMesh("Box"), m_pResources->GetMaterial("ZeroMaterial")));
    }
}

Score::~Score()
{
    for (auto object : m_pScoreGameObjects)
    {
        if (object)
        {
            object = NULL;
            delete object;
        }
    }
}

void Score::Update(float deltatime)
{

}

void Score::SetValue(int value)
{
    currentScore = value;
    int score = value;
    if (value < 999999)
    {
        for (int i = 5; i >= 0; i--)
        {
            switch (score % 10)
            {
            case 0:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("ZeroMaterial"));
                break;
            case 1:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("OneMaterial"));
                break;
            case 2:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("TwoMaterial"));
                break;
            case 3:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("ThreeMaterial"));
                break;
            case 4:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("FourMaterial"));
                break;
            case 5:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("FiveMaterial"));
                break;
            case 6:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("SixMaterial"));
                break;
            case 7:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("SevenMaterial"));
                break;
            case 8:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("EightMaterial"));
                break;
            case 9:
                m_pScoreGameObjects[i]->SetMaterial(m_pResources->GetMaterial("NineMaterial"));
                break;
            }
            score /= 10;
        }
    }
}

void Score::Draw(CameraObject* pCamera)
{
    for (int i = 0; i < 6; i++)
    {
        m_pScoreGameObjects[i]->Draw(pCamera, nullptr);
    }
}