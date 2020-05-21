#include "GamePCH.h"

#include "ResourceManager.h"
#include "Audio/SoundObject.h"
#include "Audio/SoundCueObject.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    for( auto object: m_pMeshes )
        delete object.second;

    for( auto object: m_pMaterials )
        delete object.second;

    for( auto object: m_pShaders )
        delete object.second;

    for( auto object: m_pTextures )
        delete object.second;

    for (auto object : m_pScenes)
    {
        delete object.second;
    }

    for (auto object : m_pCollisionShapes)
    {
        delete object.second;
    }

    for (auto object : m_pSoundCueObjects)
    {
        delete object.second;
    }
}

void ResourceManager::AddSoundCueObject(std::string value, SoundCueObject* pSoundObject)
{
    assert(m_pSoundCueObjects.find(value) == m_pSoundCueObjects.end());

    m_pSoundCueObjects[value] = pSoundObject;
}

SoundCueObject* ResourceManager::GetSoundCueObject(std::string value)
{
    if (m_pSoundCueObjects.find(value) == m_pSoundCueObjects.end())
    {
        assert(false);
        return nullptr;
    }
    else
    {
        return m_pSoundCueObjects[value];
    }
}

void ResourceManager::AddCollisionShape(std::string value, btCollisionShape* pCollisionShape)
{
    assert(m_pCollisionShapes.find(value) == m_pCollisionShapes.end());

    m_pCollisionShapes[value] = pCollisionShape;
}

void ResourceManager::AddScene(std::string name, Scene * pScene)
{
    assert(m_pScenes.find(name) == m_pScenes.end());

    m_pScenes[name] = pScene;
}

btCollisionShape* ResourceManager::GetCollisionShape(std::string value)
{
    if (m_pCollisionShapes.find(value) == m_pCollisionShapes.end())
    {
        assert(false);
        return nullptr;
    }
    else
    {
        return m_pCollisionShapes[value];
    }
}

Scene * ResourceManager::GetScene(std::string name)
{
    auto it = m_pScenes.find(name);
    if (it == m_pScenes.end())
        return nullptr;

    return it->second;
}

Mesh* ResourceManager::AddMesh(std::string name, Mesh* pMesh)
{
    assert( m_pMeshes.find( name ) == m_pMeshes.end() );

    m_pMeshes[name] = pMesh;

    return pMesh;
}

void ResourceManager::AddShader(std::string name, ShaderProgram* pShader)
{
    assert( m_pShaders.find( name ) == m_pShaders.end() );

    m_pShaders[name] = pShader;
}

void ResourceManager::AddTexture(std::string name, Texture* pTexture)
{
    assert( m_pTextures.find( name ) == m_pTextures.end() );

    m_pTextures[name] = pTexture;
}

void ResourceManager::AddMaterial(std::string name, Material* pMaterial)
{
    assert( m_pMaterials.find( name ) == m_pMaterials.end() );

    m_pMaterials[name] = pMaterial;
}

Mesh* ResourceManager::GetMesh(std::string name)
{
    auto it = m_pMeshes.find( name );
    if( it == m_pMeshes.end() )
        return nullptr;

    return it->second;
}

ShaderProgram* ResourceManager::GetShader(std::string name)
{
    auto it = m_pShaders.find( name );
    if( it == m_pShaders.end() )
        return nullptr;

    return it->second;
}

Texture* ResourceManager::GetTexture(std::string name)
{
    auto it = m_pTextures.find( name );
    if( it == m_pTextures.end() )
        return nullptr;

    return it->second;
}

Material* ResourceManager::GetMaterial(std::string name)
{
    auto it = m_pMaterials.find( name );
    if( it == m_pMaterials.end() )
        return nullptr;

    return it->second;
}
