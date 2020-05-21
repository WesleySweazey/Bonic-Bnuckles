#ifndef __EndScene_H__
#define __EndScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;
class BulletManager;
class ShuffleCue;
class WeightedCue;
class Cue;

class EndScene : public Scene
{
protected:

public:
    EndScene(Game* pGame, ResourceManager* pResources, std::string name);
    virtual ~EndScene();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__EndScene_H__
