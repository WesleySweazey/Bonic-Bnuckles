#pragma once

class GameObject;
class GameObjectMotionState : public btMotionState
{
protected:
    GameObject* m_pGameObject;
public:
    GameObjectMotionState(GameObject* pGameObject);
    ~GameObjectMotionState();

    virtual void getWorldTransform(btTransform& worldTrans) const override;
    virtual void setWorldTransform(const btTransform& worldTrans) override;
};