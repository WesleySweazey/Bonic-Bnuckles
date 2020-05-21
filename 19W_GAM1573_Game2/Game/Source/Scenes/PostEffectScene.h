#ifndef __PostEffectScene_H__
#define __PostEffectScene_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;
class BulletManager;
class ShuffleCue;
class WeightedCue;
class Player;
class Cue;

class PostEffectScene : public Scene
{
protected:
    bool HorizontalActive;
    bool VerticalActive;
    bool BlackandWhiteActive;
    Player* m_pPlayer;
public:
    PostEffectScene(Game* pGame, ResourceManager* pResources, std::string name, Player* pPlayer);
    virtual ~PostEffectScene();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
};

#endif //__PostEffectScene_H__
