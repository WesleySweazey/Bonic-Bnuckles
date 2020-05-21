#ifndef __Material_H__
#define __Material_H__

class ShaderProgram;
class Texture;

class Material
{
protected:
    ShaderProgram* m_pShader;
    Texture* m_pTexture;
    Texture* m_pCubemap;
    float m_Shine;

public:
    Material(ShaderProgram* pShader, Texture* pTexture, float Shine);
    Material(ShaderProgram* pShader, Texture* pTexture, float Shine, Texture* pCubemap);
    virtual ~Material();

    ShaderProgram* GetShader() { return m_pShader; }
    Texture* GetTexture() { return m_pTexture; }
    Texture* GetCubemap() { return m_pCubemap; }
    float GetShine() { return m_Shine; }

    void SetShader(ShaderProgram* pShader) { m_pShader = pShader; }
    void SetTexture(Texture* pTexture) { m_pTexture = pTexture; }
};

#endif //__Material_H__
