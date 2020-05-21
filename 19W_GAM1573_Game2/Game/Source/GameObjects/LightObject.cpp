#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/LightObject.h"
#include "Game/Scene.h"
#include "Mesh/Material.h"
#include "LightObject.h"

struct RayCastResultCallback : public b2RayCastCallback
{
    bool m_Hit;
    b2Body* m_pBody;
    RayCastResultCallback() { m_Hit = false; m_pBody = 0; }

    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
    {
        m_Hit = true;
        m_pBody = fixture->GetBody();
        return fraction;
    }
};

LightObject::LightObject(std::string name, vec3 position, vec3 rotation, vec3 scale, Mesh* pMesh, Material * pMaterial, float Range, float Intensity, bool IsEnabled, vec3 pColor, Scene* pScene)
    : GameObject(pScene,name,position,rotation,scale, pMesh, pMaterial)
{
    bIsEnabled = IsEnabled;
    m_Range = Range;
    m_Intensity = Intensity;
    m_EnabledColor = pColor;
    m_DisabledColor.x = 0.0f;
    m_DisabledColor.y = 0.0f;
    m_DisabledColor.z = 0.0f;
    if (bIsEnabled)
    {
        m_Color = m_EnabledColor;
    }
    else
    {
        m_Color = m_DisabledColor;
    }
}

LightObject::~LightObject()
{
}

void LightObject::Update(float deltatime)
{
    GameObject::Update( deltatime );
    //ImGuiLightTab();
}

void LightObject::ImGuiLightTab()
{
    ImGui::Begin("Light");
    if (ImGui::CollapsingHeader(((std::string)m_Name).c_str()))
    {
        ImGui::PushID(this);

        //Enabled
        ImGui::Checkbox("Enable", &bIsEnabled);
        if (bIsEnabled)
        {
            m_Color = m_EnabledColor;
        }
        else
        {
            m_Color = m_DisabledColor;
        }

        ////Position
        ImGui::SliderFloat("X Position", &m_Position.x, -100.0f, 200.0f);
        ImGui::SliderFloat("Y Position", &m_Position.y, -100.0f, 200.0f);
        ImGui::SliderFloat("Z Position", &m_Position.z, -100.0f, 200.0f);

        ////Color
        ImGui::ColorEdit3("Color", &m_EnabledColor.x);

        ////Range
        ImGui::SliderFloat("Range", &m_Range, 0.0f, 10000.0f);

        ////Intensity
        ImGui::SliderFloat("Intensity", &m_Intensity, 0.0f, 1.0f);

        ImGui::PopID();
    }
    ImGui::End();
}
