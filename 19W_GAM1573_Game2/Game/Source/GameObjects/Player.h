#ifndef __Player_H__
#define __Player_H__

#include "GameObjects/GameObject.h"

class Mesh;
class PlayerController;
class Score;
class Coin;
class Time;
class Laps;
class btCollisionObject;
class GameScene;

class Player : public GameObject
{
     float PLAYER_SPEED = 10.0f;   // Units per second

protected:
    LightObject* m_pPlayerLight;
    PlayerController* m_pPlayerController;
    Score* m_pScore;
    Time* m_pTime;
    Laps* m_pLaps;
    Coin* m_PreviousCoin;
    float m_Health;
    bool m_Victory;

    int m_NumOfLaps;
    float m_Speed;
    int m_NumOfJumps;
    float m_TurningSpeed;
    float m_RotationSpeedX;
    float m_RotationSpeedZ;
    int m_CurrentCheckPoint;

    vec3 m_LockCamera;
    btCollisionObject* m_Floor;

    int m_jumpTimer;
public:
    Player(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~Player();

    virtual void Update(float deltaTime) override;
    bool m_JumpAllowed;
    void SetPlayerController(PlayerController* controller) { m_pPlayerController = controller; }
    void SetSpeed(float speed) { m_Speed = speed; }
    void SetNumOfJumps(int numOfJumps) { m_NumOfJumps = numOfJumps; }
    //HUD Getters and Setters
    void SetScore(Score* pScore) { m_pScore = pScore; }
    Score* GetScore() { return m_pScore; }
    void SetTime(Time* pTime) { m_pTime = pTime; }
    Time* GetTime() { return m_pTime; }
    void SetLaps(Laps* pLaps) { m_pLaps = pLaps; }
    Laps* GetLaps() { return m_pLaps; }
    float GetHealth() { return m_Health; }
    bool GetVictory() { return m_Victory; }

    void SetPreviousCoin(Coin* pPreviousCoin) { m_PreviousCoin = pPreviousCoin; }
    Coin* GetPreviousCoin() { return m_PreviousCoin; }
    virtual void OnBeginContact(GameObject* other) override;
    virtual void EndContact() override;
    int GetNumOfLaps() { return m_NumOfLaps; }
    void AddLap() { m_NumOfLaps++; }
    int GetCurrentCheckPoint() { return m_CurrentCheckPoint; }
    void SetCurrentCheckPoint(int CurrentCheckPoint) { m_CurrentCheckPoint = CurrentCheckPoint; }
};

#endif //__Player_H__
