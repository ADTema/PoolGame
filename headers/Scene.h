#ifndef PONG_SCENE_H
#define PONG_SCENE_H

#pragma once

#include <list>
#include <mutex>

class Context;
class Camera;
class GameObject;

class Scene {
   public:
    Scene(float width, float height, Context *context);

    std::list<GameObject *>::iterator getGameObjectBeginIterator();
    std::list<GameObject *>::iterator getGameObjectEndIterator();

    void addObject(GameObject *gameObject);
    Camera *getCamera();

    void on_update();

    Context *getContext();

    void destroyGameObject(GameObject *gameObject);

   private:
    std::mutex m_gameObjects_mutex;
    std::list<GameObject *> m_gameObjects;
    Camera *m_pCamera;

    Context *m_gameContext;
};

#endif  // PONG_SCENE_H
