#ifndef __GameScene_H__
#define __GameScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;
class BulletManager;
class ShuffleCue;
class WeightedCue;
class Cue;

class GameScene : public Scene
{
protected:

public:
    Cue* m_CoinCue;
    Cue* m_BoosterCue;
    GameScene(Game* pGame, ResourceManager* pResources, std::string name);
    virtual ~GameScene();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void Reset() override;
};

#endif //__GameScene_H__
