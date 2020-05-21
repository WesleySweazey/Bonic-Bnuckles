#ifndef Laps_H
#define Laps_H

class GameObject;
class Mesh;
class PlayerController;
class Scene;
class ResourceManager;
class CameraObject;

class Laps
{
protected:
    Scene * m_pScene;
    int m_currentLap;
    int m_totalLaps;
    ResourceManager* m_pResources;
    std::vector<GameObject*> m_pLapGameObjects;
    vec3 m_Position;
public:
    Laps(std::string name, vec3 position, vec3 rotation, vec3 scale, ResourceManager* pResources, Scene* pScene, int totalLaps);
    ~Laps();

    unsigned int GetLapSize() { return m_pLapGameObjects.size(); }
    GameObject* GetObjectByIndex(int index) { return m_pLapGameObjects[index]; }
    vec3 GetPosition() { return m_Position; }
    void SetPosition(vec3 v) { m_Position = v; }
    void Update(float deltatime);
    void SetCurrentLapValue();
    void SetTotalLapValue();
    void Draw(CameraObject* c);
    void SetCurrentLapNum(int lapNum) { m_currentLap = lapNum; }
};
#endif