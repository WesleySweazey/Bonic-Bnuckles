#ifndef __GameObject_H__
#define __GameObject_H__

class Game;
class Material;
class Scene;
class Mesh;
class b2Body;
class CameraObject;
class GameObjectMotionState;
class LightObject;
class TweenObject;

#include "Game/TweenFunction.h"

class GameObject
{
    friend class GameObjectMotionState;

protected:
    std::string m_Name;

    Scene* m_pScene;

    Mesh* m_pMesh;
    Material* m_pMaterial;

    vec3 m_InitialPosition;
    vec3 m_InitialRotation;
    vec3 m_InitialScale;

    vec3 m_Position;
    vec3 m_Rotation;
    vec3 m_Scale;
    vec3 m_TweenScale;
    vec2 m_UVScale;
    vec2 m_UVOffset;

    btRigidBody* m_pRigidBody;
    GameObjectMotionState* m_pMotionState;

    std::vector<TweenObject*> Tweens;

public:
    GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial);
    virtual ~GameObject();

    virtual void Reset();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltaTime);
    virtual void Draw(CameraObject* pCamera, LightObject* pLights[]);

    void ImGuiTweensTab();

    void AddTweenScale(vec3 startScale, vec3 endScale, float time, TweenFunction tweenFunction);

    // Getters.
    std::string GetName() { return m_Name; }
    vec3 GetPosition() { return m_Position; }
    vec3 GetRotation() { return m_Rotation; }
    btRigidBody* GetRigidBody() { return m_pRigidBody; }

    // Setters.
    void SetPosition(vec3 pos);
    void SetRotation(vec3 rot);
    void SetUVScaleAndOffset(vec2 uvScale, vec2 uvOffset);
    void SetRigidBody(btRigidBody* RigidBody) { m_pRigidBody = RigidBody; }
    
    // Other helpers.
    virtual void ReturnToPool();
    virtual void RemoveFromScene();

    void CreateRigidBody(bool isDynamic, std::string CollisionShapeName, float mass, bool sensor, bool gravity);
    virtual void OnBeginContact(GameObject* other);
    virtual void EndContact();

    Material* GetMaterial() { return m_pMaterial; }
    void SetMaterial(Material * pMaterial) { m_pMaterial = pMaterial; }

    Mesh* GetMesh() { return m_pMesh; }
    void SetMesh(Mesh * pMesh) { m_pMesh = pMesh; }
};

#endif //__GameObject_H__
