#ifndef __VictoryScene_H__
#define __VictoryScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;
class BulletManager;
class ShuffleCue;
class WeightedCue;
class Player;
class Cue;

class VictoryScene : public Scene
{
protected:
    Player* m_pPlayer;
public:
    VictoryScene(Game* pGame, ResourceManager* pResources, std::string name, Player* pPlayer);
    virtual ~VictoryScene();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__VictoryScene_H__
