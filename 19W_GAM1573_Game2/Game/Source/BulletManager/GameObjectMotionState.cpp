#include "GamePCH.h"

#include "GameObjectMotionState.h"
#include "GameObjects/GameObject.h"


GameObjectMotionState::GameObjectMotionState(GameObject* pGameObject)
{
    m_pGameObject = pGameObject;
}

GameObjectMotionState::~GameObjectMotionState()
{
}

void GameObjectMotionState::getWorldTransform(btTransform& worldTrans) const
{
    MyMatrix localmat;
    localmat.CreateSRT(vec3(1), m_pGameObject->m_Rotation, m_pGameObject->m_Position);
    worldTrans.setFromOpenGLMatrix(&localmat.m11);
}

void GameObjectMotionState::setWorldTransform(const btTransform& worldTrans)
{
    MyMatrix matBulletGL;
    worldTrans.getOpenGLMatrix(&matBulletGL.m11);
    m_pGameObject->m_Position = matBulletGL.GetTranslation();
    m_pGameObject->m_Rotation = matBulletGL.GetEulerAngles() * 180.0f / PI;
}