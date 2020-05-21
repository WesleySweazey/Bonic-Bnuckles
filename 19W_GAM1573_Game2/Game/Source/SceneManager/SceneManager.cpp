#include "GamePCH.h"

#include "SceneManager.h"
#include "Game/Game.h"
#include "Game/Scene.h"
#include "Game/ResourceManager.h"

SceneManager::SceneManager(ResourceManager* pResources)
{
    m_pResources = pResources;
}

SceneManager::~SceneManager()
{
    for (auto pScene : m_pActiveScenes)
    {
        pScene = NULL;
        delete pScene;
    }
    m_pActiveScenes.clear();
}

void SceneManager::PushScene(std::string name)
{
    m_pActiveScenes.push_back(m_pResources->GetScene(name));
}

void SceneManager::PopScene()
{
    m_pActiveScenes.pop_back();
}

void SceneManager::PopAllScenes()
{
    for (unsigned int i = 0; i <= m_pActiveScenes.size(); i++)
        m_pActiveScenes.pop_back();
}

void SceneManager::Update(float deltaTime)
{
    for (unsigned int i = 0; i < m_pActiveScenes.size(); i++)
    {
        if (m_pActiveScenes[m_pActiveScenes.size() - 1]->GetIsOpaque() == true)
        {
            m_pActiveScenes[m_pActiveScenes.size() - 1]->Update(deltaTime);
        }
        else
        {
            m_pActiveScenes[i]->Update(deltaTime);
        }
        //ImGui::Begin("Scenes");
        //ImGui::Text("ActiveScene: %s", m_pActiveScenes[i]->GetName().c_str());
        //ImGui::End();
    }
}

void SceneManager::OnEvent(Event * pEvent)
{
    for (auto pScenes : m_pActiveScenes)
    {
            pScenes->OnEvent(pEvent);
    }
}

void SceneManager::Draw()
{
    for (unsigned int i = 0; i < m_pActiveScenes.size(); i++)
    {
        m_pActiveScenes[i]->Draw();
    }
}

Scene* SceneManager::GetSceneByName(std::string name)
{
    return m_pResources->GetScene(name);
}