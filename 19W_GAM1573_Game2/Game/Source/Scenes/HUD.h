#ifndef __HUD_H__
#define __HUD_H__

#include "Game/Scene.h"

class Game;
class GameObject;
class ResourceManager;
class BulletManager;
class ShuffleCue;
class WeightedCue;
class Cue;
class Health;
class Score;
class Laps;
class Time;
class Player;

class HUD : public Scene
{
protected:

public:
    Health* m_pHealth;
    Score* m_pScore;
    Laps* m_pLaps;
    Time* m_pTime;
    Player* m_pPlayer;
    HUD(Game* pGame, ResourceManager* pResources, std::string name, Player* pPlayer);
    virtual ~HUD();

    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual void Reset() override;
};

#endif //__HUD_H__
