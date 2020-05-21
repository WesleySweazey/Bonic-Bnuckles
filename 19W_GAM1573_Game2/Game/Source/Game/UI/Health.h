#ifndef Health_H
#define Health_H

class GameObject;
class Mesh;
class PlayerController;
class Scene;
class ResourceManager;
class CameraObject;

class Health
{
protected:
    Scene * m_pScene;
    int m_CurrentHealth;
    int m_MaxHealth;
    bool m_win;
    bool m_lose;
    ResourceManager* m_pResources;
    std::vector<GameObject*> m_pHealthGameObjects;
    GameObject* m_pScreen;
    vec3 m_Position;
    //float m_TurningSpeed;

public:
    Health(std::string name, vec3 position, vec3 rotation, vec3 scale, ResourceManager* pResources, Scene* pScene, int InitalHealth, int MaxHealth);
    ~Health();

    unsigned int GetHealthSize() { return m_pHealthGameObjects.size(); }
    GameObject* GetObjectByIndex(int index) { return m_pHealthGameObjects[index]; }
    vec3 GetPosition() { return m_Position; }
    void SetPosition(vec3 v) { m_Position = v; }
    void SetHealth(int v) { m_CurrentHealth = v; }
    void SetWin(bool b) { m_win = b; }
    bool GetWin() { return m_win; }
    int GetHealth() { return m_CurrentHealth; }
    void Update(float deltatime);
    void Draw(CameraObject* c);
    // void SetPlayerController(PlayerController controller) { m_pPlayerController = controller; }
    //void SetSpeed(float speed) { m_Speed = speed; }
    //void SetTurningSpeed(float speed) { m_TurningSpeed = speed; }*/
};
#endif