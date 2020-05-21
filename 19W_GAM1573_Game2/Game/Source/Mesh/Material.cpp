#include "GamePCH.h"

#include "Material.h"
#include "Mesh/Texture.h"


Material::Material(ShaderProgram* pShader, Texture* pTexture, float Shine)
{
    m_pShader = pShader;
    m_pTexture = pTexture;
    m_Shine = Shine;
    m_pCubemap = nullptr;
}
Material::Material(ShaderProgram* pShader, Texture* pTexture, float Shine, Texture* pCubemap)
{
    m_pShader = pShader;
    m_pTexture = pTexture;
    m_Shine = Shine;
    m_pCubemap = pCubemap;
}

Material::~Material()
{
}
