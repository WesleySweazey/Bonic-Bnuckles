#ifndef __LightObject_H__
#define __LightObject_H__

class GameObject;
class Mesh;
class Scene;
class Material;

class LightObject : public GameObject
{
protected:
    bool bIsEnabled;
    float m_Range;
    float m_Intensity;
    vec3 m_Color;
    vec3 m_DisabledColor;
    vec3 m_EnabledColor;
public:
    LightObject(std::string name, vec3 position, vec3 rotation, vec3 scale, Mesh* pMesh, Material * pMaterial, float Range, float Intensity, bool IsEnabled, vec3 pColor, Scene* pScene);
    virtual ~LightObject();

    virtual void Update(float deltatime) override;

    void ImGuiLightTab();

    float GetRange() { return m_Range; }
    float GetIntensity() { return m_Intensity; }
    vec3 GetColor() { return m_Color; }
    void SetRange(float Range) { m_Range = Range; }
    void SetIntensity(float Intensity) { m_Intensity = Intensity; }
};

#endif //__Player_H__
