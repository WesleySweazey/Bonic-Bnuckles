#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/PlayerController.h"
#include "Game/Scene.h"
#include "Scenes/GameScene.h"
#include "GameObjects/CameraObject.h"
#include "CollisionFilter/CollisionFilter.h"
#include "Player.h"
#include "LightObject.h"
#include "Game/UI/Health.h"
#include "Game/UI/Score.h"
#include "Game/UI/Laps.h"
#include "Game/UI/Time.h"
#include "Game/ResourceManager.h"
#include "Audio/Cue.h"
#include "Audio/SoundPlayer.h"

Player::Player(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
, m_pPlayerController( nullptr )
{
    m_NumOfLaps = 0;
    m_CurrentCheckPoint = 0;
    m_pScore = nullptr;
    m_Speed = 0.5;
    m_Health = 10;
    m_JumpAllowed = false;
    m_NumOfJumps = 1;
    /*LightObject* light4 = new LightObject("Light4", vec3(0.0f, 2.0f, -6.0), vec3(0.0f, 0.0f, 0.0), vec3(0.0f, 0.0f, 0.0), 0, 0, 20.0f, 0.25f, true, vec3(1.0f, 1.0f, 1.0f), pScene);
    pScene->AddGameObject(light4);*/
    m_RotationSpeedX = 0;
    m_RotationSpeedZ = 0;
    m_PreviousCoin = nullptr;
    m_Victory = false;
    m_jumpTimer = 0;
    m_LockCamera = vec3(0.0f, 0.0f, 0.0f);
    m_Floor = nullptr;
}
    
Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    GameObject::Update( deltaTime );

    vec3 targetVelocity(0, 0, 0);
    vec3 dir( 0, 0 );
    if( m_pPlayerController )
    {
           if( m_pPlayerController->IsHeld_Up() )
           {
               dir.z = 1;
               targetVelocity.z = m_Speed;
               
           }

           if( m_pPlayerController->IsHeld_Down() )
           {
               dir.z = -1;
               targetVelocity.z = m_Speed;
           }

           if( m_pPlayerController->IsHeld_Left() )
           {
               dir.x = -1;
               targetVelocity.x = m_Speed ;
           }

           if( m_pPlayerController->IsHeld_Right() )
           {
               dir.x = 1;
               targetVelocity.x = m_Speed;
           }
           if (m_pPlayerController->IsHeld_Jump())
           {
               if (m_Floor != nullptr)
               {
                   if (GetRigidBody()->checkCollideWith(m_Floor))
                   {
                       if (m_jumpTimer > 0.0f)
                       {
                           m_pRigidBody->applyCentralForce(btVector3(0.0f, 300.0f, 0.0f));
                           m_jumpTimer--;
                       }
                       //m_NumOfJumps--;
                   }
               }
           }
    }
  
    //return;
    
    if (m_pPlayerController->IsHeld_TopDownCamera())
    {
        CameraObject* pCamera = (CameraObject*)m_pScene->GetGameObjectByName("Camera");
        vec3 Rot = m_LockCamera;
        vec3 CameraPosition = m_pScene->GetGameObjectByName("Camera")->GetPosition();
        vec3 TopDownPosition = vec3(-50.0f,100.0f,-50.0f);
        m_pScene->GetGameObjectByName("Camera")->SetPosition(TopDownPosition);
        m_pScene->GetGameObjectByName("Camera")->SetRotation(Rot);
    }
    else
    {
        CameraObject* pCamera = (CameraObject*)m_pScene->GetGameObjectByName("Camera");
        vec3 Rot = pCamera->GetRotation();
        m_LockCamera = pCamera->GetRotation();
        float CAngle = atan2(dir.z, dir.x) * PI / 180;
        CAngle -= 90;
        float angle = Rot.y * PI / 180;
        float newX = dir.x * cos(angle) - dir.z * sin(angle);
        float newZ = dir.x * sin(angle) + dir.z * cos(angle);

        dir.x = newX;
        dir.z = newZ;
    }

    

    //m_pRigidBody->applyTorque(btVector3(dir.x, 0.0f, dir.y));
    //ImGui::Text("Direction x: %f z: %f cam: %f ", dir.x, dir.z, angle);

    
    
    //Light Movement
    GameObject* light = m_pScene->GetGameObjectByName("Light4");
    vec3 lightOffSet = vec3(0.0f, 6.0f, 0.0f) + m_Position;
    light->SetPosition(lightOffSet);

    float mass = 10.0f;
    float timeStep = 1 / 60.0f;
    float currentVelocityX = m_pRigidBody->getLinearVelocity().x();
    float currentVelocityZ = m_pRigidBody->getLinearVelocity().z();
    
    if (currentVelocityZ <= 0.05f && currentVelocityX <= 0.1f)
    {
        currentVelocityZ = 0.05f;
        currentVelocityX = 0.1f;
    }
        float diffVelocityX = (targetVelocity.x - currentVelocityX);
        float diffVelocityZ = (targetVelocity.z - currentVelocityZ);

        float MovementSpeedX = (mass * (targetVelocity.x)) / timeStep;
        float MovementSpeedZ = (mass * (targetVelocity.z)) / timeStep;

        MovementSpeedX *= dir.x;
        MovementSpeedZ *= dir.z;

        //ImGui::Text("MovementSpeed x: %f z: %f ", MovementSpeedX, MovementSpeedZ);
        m_pRigidBody->applyCentralImpulse(btVector3(MovementSpeedX*deltaTime, -9.8f, MovementSpeedZ*deltaTime));
        //m_pRigidBody->applyTorque(btVector3(MovementSpeedX*deltaTime, 0.0f, MovementSpeedZ*deltaTime));

        vec2 Direction = vec2(dir.x, dir.z);
        Direction.Normalize();
        vec3 CameraVector2 = m_pScene->GetGameObjectByName("Camera")->GetPosition();
        vec3 distance = CameraVector2 - this->GetPosition();
        float angle2 = atan2(distance.z, distance.x);
        float degreeAngle = angle2 * 180 / PI;

        //m_Rotation.y += degreeAngle + 90;
    

    if (m_NumOfJumps == 0)
        m_JumpAllowed = false;

    if (m_Position.y < 0)
        m_Health = 0;
}

void Player::OnBeginContact(GameObject * other)
{
    std::string nameOther = other->GetName();

    if (nameOther[0] == 'F')
    {
        m_Floor = other->GetRigidBody();
        m_JumpAllowed = true;
        m_NumOfJumps = 1;
        m_jumpTimer = 100;
    }
    if (nameOther[0] == 'S')
    {
        //other->GetRigidBody()->applyCentralForce(btVector3(0.0f, 500.0f, 0.0f));
        m_pTime->Start();
        m_pLaps->SetCurrentLapNum(m_NumOfLaps);
        m_pLaps->SetCurrentLapValue();
        if (m_NumOfLaps == 3)
            m_Victory = true;
    }

    if (nameOther[0] == '1')
    {
        m_pRigidBody->applyCentralImpulse(btVector3(0,0,200.0f));
        GameScene* pGameScene = (GameScene*)m_pScene;
        m_pScene->GetSoundPlayer()->PlaySound(pGameScene->m_BoosterCue);
    }

    if (nameOther[0] == '2')
    {
        m_pRigidBody->applyCentralImpulse(btVector3(-200.0f, 0, 0.0f));
        GameScene* pGameScene = (GameScene*)m_pScene;
        m_pScene->GetSoundPlayer()->PlaySound(pGameScene->m_BoosterCue);
    }
    if (nameOther[0] == '3')
    {
        m_pRigidBody->applyCentralImpulse(btVector3(0.0f, 0, -300.0f));
        GameScene* pGameScene = (GameScene*)m_pScene;
        m_pScene->GetSoundPlayer()->PlaySound(pGameScene->m_BoosterCue);
    }

    if (nameOther[0] == '4')
    {
        m_pRigidBody->applyCentralImpulse(btVector3(200.0f, 0, 0.0f));
        GameScene* pGameScene = (GameScene*)m_pScene;
        m_pScene->GetSoundPlayer()->PlaySound(pGameScene->m_BoosterCue);
    }

    if (nameOther[0] == 'W')
    {
        m_pRigidBody->applyCentralImpulse(btVector3(100.0f, 100.0f, 0.0f));
    }
}

void Player::EndContact()
{
}
