#ifndef Score_H
#define Score_H

class GameObject;
class Mesh;
class PlayerController;
class Scene;
class ResourceManager;
class CameraObject;

class Score
{
protected:
    Scene * m_pScene;
    int currentScore;
    ResourceManager* m_pResources;
    std::vector<GameObject*> m_pScoreGameObjects;
    vec3 m_Position;
    //float m_TurningSpeed;

public:
    Score(std::string name, vec3 position, vec3 rotation, vec3 scale, ResourceManager* pResources, Scene* pScene);
    ~Score();

    unsigned int GetScoreSize() { return m_pScoreGameObjects.size(); }
    GameObject* GetObjectByIndex(int index) { return m_pScoreGameObjects[index]; }
    vec3 GetPosition() { return m_Position; }
    void SetPosition(vec3 v) { m_Position = v; }
    void Update(float deltatime);
    void SetValue(int value);
    void Draw(CameraObject* c);
    int GetCurrentScore() { return currentScore; }
    void SetCurrentScore(int newScore) { currentScore = newScore; }
    // void SetPlayerController(PlayerController controller) { m_pPlayerController = controller; }
    //void SetSpeed(float speed) { m_Speed = speed; }
    //void SetTurningSpeed(float speed) { m_TurningSpeed = speed; }*/
};
#endif