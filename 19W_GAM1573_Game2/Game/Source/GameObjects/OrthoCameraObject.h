#ifndef __OrthoCameraObject_H__
#define __OrthoCameraObject_H__

#include "CameraObject.h"
class Scene;

class OrthoCameraObject : public CameraObject
{
protected:
    //mat4 m_ViewMatrix;
    //mat4 m_ProjMatrix;
    //vec3 m_LookAtPosition;

public:
    OrthoCameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale);
    virtual ~OrthoCameraObject();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltaTime) override;

    //mat4* GetViewMatrix() { return &m_ViewMatrix; }
    //mat4* GetProjMatrix() { return &m_ProjMatrix; }
    //void SetLookAtPosition(vec3 pos) { m_LookAtPosition = pos; }
    //void SetObjectToFollow(GameObject* pObject, float dist) { m_ObjectFollowing = pObject; m_Distance = dist; }
};

#endif //__OrthoCameraObject_H__
