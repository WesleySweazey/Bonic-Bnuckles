#ifndef __TitleScene_H__
#define __TitleScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;
class BulletManager;
class ShuffleCue;
class WeightedCue;
class Cue;

class TitleScene : public Scene
{
protected:

public:
    TitleScene(Game* pGame, ResourceManager* pResources, std::string name);
    virtual ~TitleScene();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__TitleScene_H__
