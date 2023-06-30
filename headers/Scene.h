#ifndef PONG_SCENE_H
#define PONG_SCENE_H

#pragma once

#include <list>
#include <mutex>


#include "Window.h"

class Score;
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

    void openFile(std::string name);

    void file(std::string name);

    void save(std::string name);

    void toJson(std::ofstream &ofstream);

    void outJson(std::ifstream &infile);

    void saveScores(std::string name, Score *m_score);

    std::mutex m_gameObjects_mutex;
    std::list<GameObject *> m_gameObjects;
    std::queue<GameObject *> m_toDestroyObjects;
    Camera *m_pCamera;

    Score *m_score;

    std::list<std::pair<std::string, int>> scores;

    std::string m_playerName;

    Context *m_pGameContext;
};

#endif  // PONG_SCENE_H
