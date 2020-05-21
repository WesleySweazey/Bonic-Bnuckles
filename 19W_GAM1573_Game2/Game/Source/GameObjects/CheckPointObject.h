#ifndef __CheckPointObject_H__
#define __CheckPointObject_H__

#include "GameObjects/GameObject.h"

class Mesh;

class CheckPointObject : public GameObject
{
    int m_CheckPointNumber;
public:
    CheckPointObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial,int CheckPointNumber);
    virtual ~CheckPointObject();

    virtual void Update(float deltaTime) override;

    virtual void OnBeginContact(GameObject* other) override;
    virtual void EndContact() override;
};

#endif //__Coin_H__
