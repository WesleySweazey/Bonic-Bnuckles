#ifndef __PauseScene_H__
#define __PauseScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;
class BulletManager;
class ShuffleCue;
class WeightedCue;
class Cue;

class PauseScene : public Scene
{
protected:

public:
    PauseScene(Game* pGame, ResourceManager* pResources, std::string name);
    virtual ~PauseScene();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__PauseScene_H__
