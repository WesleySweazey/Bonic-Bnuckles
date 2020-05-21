#ifndef __ResourceManager_H__
#define __ResourceManager_H__

class ResourceManager;
class SoundObject;
class btCollisionShape;
class SoundCueObject;
class Scene;

#include "Mesh/Material.h"
#include "Mesh/Mesh.h"
#include "Mesh/Texture.h"
#include "Game/Scene.h"

class Game;
class ShaderProgram;

class ResourceManager
{
protected:
    std::map<std::string, Mesh*> m_pMeshes;
    std::map<std::string, Material*> m_pMaterials;
    std::map<std::string, Texture*> m_pTextures;
    std::map<std::string, ShaderProgram*> m_pShaders;
    std::map<std::string, SoundCueObject*> m_pSoundCueObjects;
    std::map<std::string, btCollisionShape*> m_pCollisionShapes;
    std::map<std::string, Scene*> m_pScenes;

public:
    Mesh* AddMesh(std::string, Mesh* mesh);
    void AddMaterial(std::string, Material* material);
    void AddShader(std::string name, ShaderProgram* pShader);
    void AddTexture(std::string name, Texture* pTexture);
    void AddSoundCueObject(std::string name, SoundCueObject* pSoundObject);
    void AddCollisionShape(std::string name, btCollisionShape* pCollisionShape);
    void AddScene(std::string name, Scene* pScene);

    Mesh* GetMesh(std::string);
    Material* GetMaterial(std::string);
    ShaderProgram* GetShader(std::string name);
    Texture* GetTexture(std::string name);
    SoundCueObject* GetSoundCueObject(std::string name);
    btCollisionShape* GetCollisionShape(std::string name);
    Scene* GetScene(std::string name);

    ResourceManager();
    virtual ~ResourceManager();
};

#endif //__ResourceManager_H__
