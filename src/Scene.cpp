#include "../headers/Scene.h"

#include <algorithm>

#include "../game/ExitGameScript.h"
#include "../game/PlayerScript.h"
#include "../headers/Camera.h"
#include "../headers/Context.h"
#include "../headers/GameObject.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

std::list<GameObject *>::iterator Scene::getGameObjectBeginIterator() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    return m_gameObjects.begin();
}
std::list<GameObject *>::iterator Scene::getGameObjectEndIterator() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    return m_gameObjects.end();
}
void Scene::addObject(GameObject *gameObject) {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    m_gameObjects.push_back(gameObject);
    gameObject->m_pScene = this;
    gameObject->start();
}

Scene::Scene(float width, float height, Context *context)
    : m_gameContext(context) {
    m_pCamera = new Camera(width, height);
    m_pCamera->addComponent(new ExitGameScript());
    addObject(m_pCamera);

    auto gm = new GameObject();
    gm->addComponent(new PlayerScript());
    addObject(gm);
}
Camera *Scene::getCamera() {
    return m_pCamera;
}
void Scene::on_update() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(), [](GameObject *gameObject){
        gameObject->fixedUpdate();
    });
}
void Scene::destroyGameObject(GameObject *gameObject) {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    auto searched = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
    if(*searched){
        m_gameObjects.erase(searched);
    }
    delete gameObject;
}
Context *Scene::getContext() { return m_gameContext; }
