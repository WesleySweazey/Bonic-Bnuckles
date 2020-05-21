#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Coin.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Game/UI/Score.h"
#include "Game/Scene.h"
#include "Scenes/GameScene.h"
#include "GameObjects/CameraObject.h"
#include "CollisionFilter/CollisionFilter.h"
#include "Player.h"
#include "LightObject.h"
#include "Game/ResourceManager.h"
#include "Audio/Cue.h"
#include "Audio/SoundPlayer.h"

Coin::Coin(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_CollisionRadius = 30.0f;
    m_PickedUp = false;
}
    
Coin::~Coin()
{
}

void Coin::Update(float deltaTime)
{
    GameObject::Update( deltaTime );
    m_pRigidBody->applyTorque(btVector3(0, deltaTime, 0));
}

void Coin::OnBeginContact(GameObject * other)
{
    std::string nameOther = other->GetName();

    if (nameOther[0] == 'P')
    {
        if (m_PickedUp == false)
        {
            Player* player = (Player*)(other);
            if (player->GetPreviousCoin() != this)
            {
                int score = player->GetScore()->GetCurrentScore();
                score++;
                player->GetScore()->SetValue(score);
                player->SetPreviousCoin(this);
                m_TweenScale = vec3(0.0f, 0.0f, 0.0f);
                this->AddTweenScale(m_Scale, m_TweenScale, 2.0f, TweenFunction_BounceEaseOut);
                GameScene* pGameScene = (GameScene*)m_pScene;
                m_pScene->GetSoundPlayer()->PlaySound(pGameScene->m_CoinCue);
                m_PickedUp = true;
            }
        }
    }
    //if (nameOther[0] == 'S')
    //{
    //    other->GetRigidBody()->applyCentralForce(btVector3(0.0f, 500.0f, 0.0f));
    //}
}

void Coin::EndContact()
{
}
