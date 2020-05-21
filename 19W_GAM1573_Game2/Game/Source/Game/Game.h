#ifndef __Game_H__
#define __Game_H__

class ImGuiManager;
class ResourceManager;
class Texture;
class Scene;
class Mesh;
class GameObject;
class Player;
class PlayerController;
class FBODefinition;
class SceneManager;
class HUD;

class Game : public GameCore
{
protected:
    ImGuiManager* m_pImGuiManager;

    ResourceManager* m_pResources;

    SceneManager* m_pSceneManager;

    Scene*  m_pPostEffectScene;

    PlayerController* m_pControllers[4];

    FBODefinition* m_pFBO;

    Player* m_pPlayer;

    HUD* m_pHUD;

    bool HasStartedGame;
    bool InOptionsTab;
    bool IsGameOver;
    bool IsPaused;


public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height) override;
    virtual void LoadContent() override;

    virtual void OnEvent(Event* pEvent) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    virtual btTriangleMesh* LoadTriangleMesh(std::string objMeshName);
    PlayerController* GetController(int index) { return m_pControllers[index]; }
};

#endif //__Game_H__
