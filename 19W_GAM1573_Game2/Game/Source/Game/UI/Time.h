#ifndef Time_H
#define Time_H

class GameObject;
class Mesh;
class PlayerController;
class Scene;
class ResourceManager;
class CameraObject;

class Time
{
protected:
    Scene * m_pScene;
    int currentScore;
    ResourceManager* m_pResources;
    std::vector<GameObject*> m_pTimeGameObjects;
    vec3 m_Position;
    double m_TimeElapsed;
    bool m_Start;

public:
    Time(std::string name, vec3 position, vec3 rotation, vec3 scale, ResourceManager* pResources, Scene* pScene);
    ~Time();

    unsigned int GetTimeSize() { return m_pTimeGameObjects.size(); }
    GameObject* GetObjectByIndex(int index) { return m_pTimeGameObjects[index]; }
    vec3 GetPosition() { return m_Position; }
    void SetPosition(vec3 v) { m_Position = v; }
    void Update(float deltatime);
    void SetValue(float value);
    double GetTimeElapsed() { return m_TimeElapsed; }
    void Draw(CameraObject* c);
    void Start();
    void Stop();
};
#endif