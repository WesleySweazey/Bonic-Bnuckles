#include "GamePCH.h"
#include "BulletManager.h"
#include "GameObjects/GameObject.h"

#undef new
bool MyContactAddedCallback(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj0Wrap, 
    int partId0, int index0, const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
{
    return false;
}

void MyContactStartedCallback(btPersistentManifold* const &manifold)
{
    GameObject* m_pObjA;
    GameObject* m_pObjB;
    m_pObjA = (GameObject*)manifold->getBody0()->getUserPointer();
    m_pObjB = (GameObject*)manifold->getBody1()->getUserPointer();

    m_pObjA->OnBeginContact(m_pObjB);
    m_pObjB->OnBeginContact(m_pObjA);

}
void MyContactEndedCallback(btPersistentManifold* const &manifold)
{
}

BulletManager::BulletManager()
{
    m_pCollisionConfiguration = new btDefaultCollisionConfiguration();

    m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);

    m_pOverlappingPairCache = new btDbvtBroadphase();
 
    m_pSolver = new btSequentialImpulseConstraintSolver;

    m_pDynamicsWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pOverlappingPairCache, m_pSolver, m_pCollisionConfiguration);

    m_pDynamicsWorld->setGravity(btVector3(0, -10, 0));

    gContactAddedCallback = MyContactAddedCallback;
    gContactStartedCallback = MyContactStartedCallback;
    gContactEndedCallback = MyContactEndedCallback;
}

BulletManager::~BulletManager()
{
    m_pDynamicsWorld = NULL;
    delete m_pDynamicsWorld;
    //
    m_pSolver = NULL;
    delete m_pSolver;
    //
    m_pOverlappingPairCache = NULL;
    delete m_pOverlappingPairCache;
    //
    m_pDispatcher = NULL;
    delete m_pDispatcher;
    //
    m_pCollisionConfiguration = NULL;
    delete m_pCollisionConfiguration;
}

void BulletManager::update(float deltatime)
{
    m_pDynamicsWorld->stepSimulation(deltatime);
}