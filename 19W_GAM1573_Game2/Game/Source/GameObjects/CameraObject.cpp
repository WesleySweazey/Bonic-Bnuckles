#include "GamePCH.h"

#include "CameraObject.h"
#include "Game/Game.h"
#include "Game/Scene.h"

CameraObject::CameraObject(Scene* pScene, std::string name, vec3 pos, vec3 rot, vec3 scale)
: GameObject( pScene, name, pos, rot, scale, 0, 0 )
{
    m_LookAtPosition.Set( 0, 0, 0 );
    m_ObjectFollowing = nullptr;
    m_MouseChangeSinceLastFrame.Set(0, 0);
}

CameraObject::~CameraObject()
{
}

void CameraObject::OnEvent(Event * pEvent)
{
    if (pEvent->GetEventType() == EventType_Input)
    {
#if WIN32
        InputEvent* pInput = static_cast<InputEvent*>(pEvent);

        if (pInput->GetInputDeviceType() == InputDeviceType_Keyboard)
        {
            int keyID = pInput->GetID();

            if (pInput->GetInputState() == InputState_Pressed)
            {
                if (keyID == 'C')
                {
                    vec2 middleScreenCoords = vec2((float)m_pScene->GetGame()->GetFramework()->GetWindowWidth() / 2, (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight() / 2);
                    if (m_MouseLocked)
                    {
                        m_MouseLocked = false;
                        //m_MouseChangeSinceLastFrame.Set(0, 0);
                        //m_LastMousePosition.Set(middleScreenCoords.x,middleScreenCoords.y);
                    }
                    else
                    {
                        m_MouseLocked = true;
                        //m_LastMousePosition.Set(middleScreenCoords.x, middleScreenCoords.y);
                        //SetCursorPos((int)m_LastMousePosition.x, (int)m_LastMousePosition.y);
                    }
                }
            }
        }

        if (pInput->GetInputDeviceType() == InputDeviceType_Mouse)
        {
            vec2 middleScreenCoords = vec2((float)m_pScene->GetGame()->GetFramework()->GetWindowWidth() / 2, (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight() / 2);
            if (m_MouseLocked)
            {
                m_MouseLocked = true;
                m_MouseChangeSinceLastFrame = pInput->GetPosition() - middleScreenCoords;//m_LastMousePosition -

                //m_LastMousePosition.Set(middleScreenCoords.x, middleScreenCoords.y);
                //m_pScene->GetGame()->GetFramework()->SetMousePosition(ivec2((int)m_LastMousePosition.x, (int)m_LastMousePosition.y));
            }
        }
#endif
    }
}

void CameraObject::Update(float deltaTime)
{
    // Setup camera/view matrix.
    m_ViewMatrix.CreateLookAtView( m_Position, vec3(0,1,0), m_LookAtPosition );

    float windowWidth = (float)m_pScene->GetGame()->GetFramework()->GetWindowWidth();
    float windowHeight = (float)m_pScene->GetGame()->GetFramework()->GetWindowHeight();
    m_ProjMatrix.CreatePerspectiveVFoV( 45, windowWidth/windowHeight, 0.01f, 1000.0f );

    glEnable(GL_CULL_FACE);
    if (m_ObjectFollowing != nullptr)
    {
        static vec2 Dir = 0;
        float speed = 50;

        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('I'))
        {
            Dir.x -= 1;
        }
        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('J'))
        {
            Dir.y -= 1;
        }
        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('K'))
        {
            Dir.x += 1;
        }
        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('L'))
        {
            Dir.y += 1;
        }

        if (m_MouseLocked == true)
        {
            m_Rotation.x += m_MouseChangeSinceLastFrame.y *0.1f * deltaTime;
            m_Rotation.y += -m_MouseChangeSinceLastFrame.x *0.1f * deltaTime;
        }

        Dir.x *= speed * deltaTime;
        Dir.y *= speed * deltaTime;

        m_Rotation.x += Dir.x;
        m_Rotation.y += Dir.y;

        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('U'))
            m_Distance -= 10 * deltaTime;
        if (m_pScene->GetGame()->GetFramework()->IsKeyDown('O'))
            m_Distance += 10 * deltaTime;

        MyClamp(m_Distance, 0.1f, 20.0f);
        MyClamp(m_Rotation.x, -89.9f, 89.9f);

        vec3 followedObjectPosition = m_ObjectFollowing->GetPosition() + vec3(0, 1, 0);

        float sx = sin(m_Rotation.x / 180 * PI);
        float sy = sin(m_Rotation.y / 180 * PI);
        float cx = cos(m_Rotation.x / 180 * PI);
        float cy = cos(m_Rotation.y / 180 * PI);

        m_Position = followedObjectPosition + vec3(cx * sy * m_Distance, -sx * m_Distance, -1 * cx * cy * m_Distance);

        m_ViewMatrix.CreateLookAtView(m_Position, vec3(0, 1, 0), followedObjectPosition);
    }
}
