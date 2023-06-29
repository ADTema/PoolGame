#ifndef PONG_SCENE_H
#define PONG_SCENE_H

#pragma once

#include <list>
#include <mutex>

#include "Window.h"

class Context;
class Camera;
class GameObject;

class Scene {
    friend void Window::on_update();
   public:
    Scene(float width, float height, Context *context);

    void addObject(GameObject *gameObject);

    void on_update();

    Context *getContext();

    void endGame();

    void destroyGameObject(GameObject *gameObject);
   private:

    void screensaver();

    void restartTable();

    void destroyGameObjects();

    void file(std::string name);

    void save(std::string name);

    void toJson(std::ofstream &ofstream);
    void outJson(std::ifstream &infile);

    std::mutex m_gameObjects_mutex;
    std::list<GameObject *> m_gameObjects;
    std::queue<GameObject *> m_toDestroyObjects;
    Camera *m_pCamera;

    std::string m_playerName;

    Context *m_pGameContext;
};

#endif  // PONG_SCENE_H
