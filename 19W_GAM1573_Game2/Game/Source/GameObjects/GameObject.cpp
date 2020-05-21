#include "GamePCH.h"

#include "Mesh/Material.h"
#include "Mesh/Mesh.h"
#include "GameObjects/CameraObject.h"
#include "GameObjects/GameObject.h"
#include "Game/Scene.h"
#include "BulletManager/BulletManager.h"
#include "BulletManager/GameObjectMotionState.h"
#include "CollisionFilter/CollisionFilter.h"
#include "GameObject.h"
#include "GameObjects/LightObject.h"
#include "Game/TweenObject.h"
#include "Game/TweenFunction.h"
#include "Game/ResourceManager.h"

GameObject::GameObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale, Mesh* pMesh, Material* pMaterial)
: m_Name( name )
, m_pScene( pScene )
, m_pMesh( pMesh )
, m_pMaterial( pMaterial )
, m_InitialPosition( pos )
, m_InitialRotation( rot )
, m_InitialScale( scale )
, m_Position( pos )
, m_Rotation( rot )
, m_Scale( scale )
{
    m_UVScale.Set( 1.0f, 1.0f );
    m_UVOffset.Set( 0.0f, 0.0f );
    m_TweenScale = m_Scale * 5.0f;
    m_pRigidBody = nullptr;
    m_pMotionState = nullptr;
}

GameObject::~GameObject()
{
    delete m_pMotionState;
    delete m_pRigidBody;
}

void GameObject::Reset()
{
    m_Position = m_InitialPosition;
    m_Rotation = m_InitialRotation;
}

void GameObject::OnEvent(Event* pEvent)
{
}

void GameObject::Update(float deltaTime)
{
    if (m_pRigidBody)
    {
        btTransform world = m_pRigidBody->getWorldTransform();

        //m_Rotation *= 180.0f / PI;
        //world.getRotation().getEulerZYX(m_Rotation.z, m_Rotation.y, m_Rotation.x);

        m_Position.x = world.getOrigin().getX();
        m_Position.y = world.getOrigin().getY();
        m_Position.z = world.getOrigin().getZ();

        //mat4 WorldMat;
        //world.getOpenGLMatrix(&WorldMat.m11);

        //ImGui::Text("Value: %f", world.getOrigin().getY());
        //ImGuiTweensTab();

        m_pRigidBody->setActivationState(1);
    }
    for (unsigned int i = 0; i < Tweens.size(); i++)
    {
        Tweens[i]->Update(deltaTime);
        if (Tweens[i]->GetIsFinished() == true)
        {
                auto iteratorForObject = std::find(Tweens.begin(), Tweens.end(), Tweens[i]);

                if (iteratorForObject != Tweens.end())
                {
                    Tweens.erase(iteratorForObject);
                }
        }
    }

}

void GameObject::AddTweenScale(vec3 startScale, vec3 endScale, float time, TweenFunction tweenFunction)
{
    for (int i = 0; i < 3; i++)
    {
        if (m_Scale[i] != endScale[i])
        {
            TweenObject* temp = new TweenObject();
            Tweens.push_back(temp);
            m_Scale[i] = startScale[i];
            temp->SetUp(tweenFunction, &m_Scale[i], startScale[i], endScale[i], time, true);
        }
    }
}

void GameObject::Draw(CameraObject* pCamera, LightObject* pLights[])
{
    if( m_pMesh != nullptr )
    {
        m_pMesh->SetupAttributes( m_pMaterial );

        // Create world matrix.
        MyMatrix worldMat;
        worldMat.CreateSRT( m_Scale, m_Rotation, m_Position );

        //Create Normal Matrix
        MyMatrix RotationMat;
        RotationMat.CreateRotation(m_Rotation);

        static vec3 materialColor = vec3(1, 1, 1);
        static vec3 lightColor = vec3(1, 1, 1);
        static vec3 LightPos = vec3(0,5,0);

        //ImGuiTweensTab();

        if (pLights != nullptr)
            m_pMesh->SetupUniforms( m_pMaterial, &worldMat, &RotationMat, pCamera, m_UVScale, m_UVOffset, pLights);
        else
            m_pMesh->SetupUniforms(m_pMaterial, &worldMat, &RotationMat, pCamera, m_UVScale, m_UVOffset);

        m_pMesh->Draw( m_pMaterial );
    }
}

void GameObject::ImGuiTweensTab()
{
    ImGui::Begin("Tweens");
    if (ImGui::CollapsingHeader("Tweens"))
    {
        //Enabled
        ImGui::PushID(" Scale ");
        ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(3.0f / 7.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(3.0f / 7.0f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(3.0f / 7.0f, 0.5f, 0.5f));
        ImGui::Button(" Scale ");
        if (ImGui::IsItemClicked(0))
        {
            AddTweenScale(m_Scale, m_TweenScale, 5.0f, TweenFunction_BounceEaseInOut);
        }
        ImGui::PopStyleColor(3);
        ImGui::PopID();
    }
    ImGui::End();
}

void GameObject::SetPosition(vec3 pos)
{
    m_Position = pos;
}

void GameObject::SetRotation(vec3 rot)
{
    m_Rotation = rot;
}

void GameObject::SetUVScaleAndOffset(vec2 uvScale, vec2 uvOffset)
{
    m_UVScale = uvScale;
    m_UVOffset = uvOffset;
}

void GameObject::ReturnToPool()
{
}

void GameObject::RemoveFromScene()
{
    m_pScene->RemoveGameObject( this );
}

void GameObject::CreateRigidBody(bool bisDynamic, std::string CollisionShapeName, float fmass, bool sensor, bool gravity)
{
#undef new
    assert(m_pRigidBody == nullptr);
    btCollisionShape* groundShape = m_pScene->GetResourceManager()->GetCollisionShape(CollisionShapeName);

    //collisionShapes.push_back(groundShape);

    btTransform groundTransform;
    groundTransform.setIdentity();
    groundTransform.setOrigin(btVector3(m_Position.x, m_Position.y, m_Position.z));

    btScalar mass(fmass);

    bool isDynamic = bisDynamic;

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        groundShape->calculateLocalInertia(mass, localInertia);

    m_pMotionState = new GameObjectMotionState(this);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_pMotionState, groundShape, localInertia);
    m_pRigidBody = new btRigidBody(rbInfo);
    if (sensor == true)
    {
        m_pRigidBody->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
    }
    if (gravity == false)
    {
        m_pRigidBody->setGravity(btVector3(0.0f,0.0f,0.0f));
    }
    m_pRigidBody->setUserPointer(this);
    m_pScene->GetBulletManager()->GetDynamicWorld()->addRigidBody(m_pRigidBody);
}

void GameObject::OnBeginContact(GameObject * other)
{
    //if (m_Name == "Sphere")
    //{
    //    m_TweenScale = vec3(m_Scale.x, -m_Scale.y * 0.5f, m_Scale.z);
    //    AddTweenScale(m_Scale, m_TweenScale, 1.0f, TweenFunction_BounceEaseInOut);
    //    //AddTweenScale(m_Scale, m_InitialScale, 1.0f, TweenFunction_BounceEaseInOut);
    //}
}

void GameObject::EndContact()
{
    //if (m_Name == "Sphere")
    //{
    //    m_TweenScale = vec3(m_Scale.x, m_Scale.y * 0.5f, m_Scale.z);
    //    AddTweenScale(m_Scale, m_InitialScale, 1.0f, TweenFunction_BounceEaseInOut);
    //    //AddTweenScale(m_Scale, m_InitialScale, 1.0f, TweenFunction_BounceEaseInOut);
    //}
}
