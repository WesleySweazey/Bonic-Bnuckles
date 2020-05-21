#ifndef __StartObject_H__
#define __StartObject_H__

#include "GameObjects/GameObject.h"

class Mesh;

class StartObject : public GameObject
{
public:
    StartObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~StartObject();

    virtual void Update(float deltaTime) override;

    virtual void OnBeginContact(GameObject* other) override;
    virtual void EndContact() override;
};

#endif //__Coin_H__
