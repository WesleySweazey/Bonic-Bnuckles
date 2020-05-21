#ifndef __Scene_H__
#define __Scene_H__

class Game;
class GameObject;
class ResourceManager;
class BulletManager;
class SoundPlayer;
class ShuffleCue;
class WeightedCue;
class Cue;

class Scene
{
private:
    std::vector<GameObject*> m_pGameObjects;

protected:
    Game* m_pGame;
    ResourceManager* m_pResources;
    BulletManager* m_pBulletManager;
    std::string m_Name;

    bool m_IsActive;
    bool m_Opaque;

    SoundPlayer* m_pSoundPlayer;
    ShuffleCue* m_pShuffleCue;
    WeightedCue* m_pWeightedCue;

public:
    Scene(Game* pGame, ResourceManager* pResources, std::string name);
    virtual ~Scene();

    void Cleanup();

    virtual void LoadContent();

    void CreateLights();

    void CreateSoundCues();

    void CreateSoundPlayer();

    virtual void Reset();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltaTime);
    virtual void Draw();

    void AddGameObject(GameObject* pObject);
    bool RemoveGameObject(GameObject* pObject);
    bool IsGameObjectInScene(GameObject* pObject);
    GameObject* GetGameObjectByName(std::string name);

    Game* GetGame() { return m_pGame; }
    ResourceManager* GetResourceManager() { return m_pResources; }
    BulletManager* GetBulletManager() { return m_pBulletManager; }
    std::string GetName() { return m_Name; }
    bool GetIsActive() { return m_IsActive; }
    bool GetIsOpaque() { return m_Opaque; }
    SoundPlayer* GetSoundPlayer() { return m_pSoundPlayer; }

    void SetIsActive(bool IsActive) { m_IsActive = IsActive; }
    void SetIsOpaque(bool IsOpaque) { m_Opaque = IsOpaque; }

    void ImGuiSoundTab();
};

#endif //__Scene_H__
