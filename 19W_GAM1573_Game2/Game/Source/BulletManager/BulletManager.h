#pragma once

class BulletManager
{
protected:
    btDefaultCollisionConfiguration* m_pCollisionConfiguration;
    btCollisionDispatcher* m_pDispatcher;
    btBroadphaseInterface* m_pOverlappingPairCache;
    btSequentialImpulseConstraintSolver* m_pSolver;
    btDiscreteDynamicsWorld* m_pDynamicsWorld;

public:
    BulletManager();
    ~BulletManager();

    void update(float deltatime);

    btDiscreteDynamicsWorld* GetDynamicWorld() { return m_pDynamicsWorld; }
};