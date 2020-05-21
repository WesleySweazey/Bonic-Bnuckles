#include "GamePCH.h"

#include "OrthoCameraObject.h"
#include "CameraObject.h"
#include "Game/Game.h"
#include "Game/Scene.h"

OrthoCameraObject::OrthoCameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
: CameraObject( pScene, name, pos, rot, scale)
{
    //m_LookAtPosition.Set( 0, 0, 0 );
    //m_ObjectFollowing = nullptr;
}

OrthoCameraObject::~OrthoCameraObject()
{
}

void OrthoCameraObject::OnEvent(Event * pEvent)
{
}

void OrthoCameraObject::Update(float deltaTime)
{
    return;
    //// Setup camera/view matrix.
    //m_ViewMatrix.CreateLookAtView( m_Position, vec3(0,1,0), m_LookAtPosition );

    //float windowWidth = (float)m_pScene->GetGame()->GetFramework()->GetWindowWidth();
    //float windowHeight = (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight();
    //m_ProjMatrix.CreatePerspectiveVFoV( 45, windowWidth/windowHeight, 0.01f, 1000.0f );

    //if (m_ObjectFollowing != nullptr)
    //{
    //    static vec2 Dir = 0;
    //    float speed = 20;

    //    if (m_pScene->GetGame()->GetFramework()->IsKeyDown('I'))
    //    {
    //        Dir.x -= 1;
    //    }
    //    if (m_pScene->GetGame()->GetFramework()->IsKeyDown('J'))
    //    {
    //        Dir.y -= 1;
    //    }
    //    if (m_pScene->GetGame()->GetFramework()->IsKeyDown('K'))
    //    {
    //        Dir.x += 1;
    //    }
    //    if (m_pScene->GetGame()->GetFramework()->IsKeyDown('L'))
    //    {
    //        Dir.y += 1;
    //    }

    //    Dir.x *= speed * deltaTime;
    //    Dir.y *= speed * deltaTime;

    //    m_Rotation.x += Dir.x;
    //    m_Rotation.y += Dir.y;

    //    if (m_pScene->GetGame()->GetFramework()->IsKeyDown('U'))
    //        m_Distance -= 10 * deltaTime;
    //    if (m_pScene->GetGame()->GetFramework()->IsKeyDown('O'))
    //        m_Distance += 10 * deltaTime;

    //    MyClamp(m_Distance, 0.1f, 20.0f);
    //    MyClamp(m_Rotation.x, -89.9f, 89.9f);

    //    vec3 followedObjectPosition = m_ObjectFollowing->GetPosition() + vec3(0, 1, 0);

    //    float sx = sin(m_Rotation.x / 180 * PI);
    //    float sy = sin(m_Rotation.y / 180 * PI);
    //    float cx = cos(m_Rotation.x / 180 * PI);
    //    float cy = cos(m_Rotation.y / 180 * PI);

    //    m_Position = followedObjectPosition + vec3(cx * sy * m_Distance, -sx * m_Distance, -1 * cx * cy * m_Distance);

    //    m_ViewMatrix.CreateLookAtView(m_Position, vec3(0, 1, 0), followedObjectPosition);
    //}
}
