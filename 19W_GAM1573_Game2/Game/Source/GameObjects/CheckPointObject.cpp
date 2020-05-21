#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/CheckPointObject.h"
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

CheckPointObject::CheckPointObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial, int CheckPointNumber)
: GameObject( pScene, name, pos, rot, scale, pMesh, pMaterial )
{
    m_CheckPointNumber = CheckPointNumber;
}
    
CheckPointObject::~CheckPointObject()
{
}

void CheckPointObject::Update(float deltaTime)
{
    GameObject::Update( deltaTime );
}

void CheckPointObject::OnBeginContact(GameObject * other)
{
    std::string nameOther = other->GetName();

    if (nameOther[0] == 'P')
    {
        Player* player = (Player*)(other);
        if(player)
        {
            player->SetCurrentCheckPoint(m_CheckPointNumber);
        }
    }
}

void CheckPointObject::EndContact()
{
}
