#ifndef __SceneManager_H__
#define __SceneManager_H__

#include "Game/Scene.h"

class Scene;
class ResourceManager;

class SceneManager
{
protected:
    std::vector<Scene*> m_pActiveScenes;
    ResourceManager* m_pResources;
public:
    SceneManager(ResourceManager* pResources);
    virtual ~SceneManager();

    void PushScene(std::string name);
    void PopScene();
    void PopAllScenes();
    Scene* GetSceneByName(std::string name);

    virtual void Update(float deltaTime);
    virtual void OnEvent(Event* pEvent);
    virtual void Draw();
};

#endif //__SceneManager_H__
