#ifndef __Coin_H__
#define __Coin_H__

#include "GameObjects/GameObject.h"

class Mesh;

class Coin : public GameObject
{
protected:
    float m_CollisionRadius;
    bool m_PickedUp;
public:
    Coin(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~Coin();

    virtual void Update(float deltaTime) override;

    virtual void OnBeginContact(GameObject* other) override;
    virtual void EndContact() override;
};

#endif //__Coin_H__
