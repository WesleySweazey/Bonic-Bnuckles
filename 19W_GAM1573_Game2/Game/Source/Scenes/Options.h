#ifndef __OptionsScene_H__
#define __OptionsScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class Player;
class ResourceManager;
class BulletManager;
class ShuffleCue;
class WeightedCue;
class Cue;

class OptionsScene : public Scene
{
protected:
    Player* m_pPlayer;
public:
    OptionsScene(Game* pGame, ResourceManager* pResources, std::string name, Player* pPlayer);
    virtual ~OptionsScene();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__OptionsScene_H__
