#include "../headers/Scene.h"

#include <algorithm>

#include "../game/CameraScript.h"
#include "../game/ExitGameScript.h"
#include "../game/PlayerScript.h"
#include "../game/prefabs/Rectangle.h"
#include "../headers/Camera.h"
#include "../headers/Context.h"
#include "../headers/Log.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

bool sortGM(GameObject *f, GameObject *s) {
    return f->getPosition().z < s->getPosition().z;
}

void Scene::addObject(GameObject *gameObject) {
    {
        std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
        m_gameObjects.push_back(gameObject);
        m_gameObjects.sort(sortGM);
    }
    gameObject->m_pScene = this;
    gameObject->start();
}
GameObject::~GameObject() { delete m_texture; }

Scene::Scene(float width, float height, Context *context)
    : m_pGameContext(context) {
    m_pCamera = new Camera(width, height);
    context->setCamera(m_pCamera);
    m_pCamera->addComponent(new ExitGameScript());
    m_pCamera->addComponent(new CameraScript());
    addObject(m_pCamera);

    auto gm = new GameObject();
    gm->addComponent(new PlayerScript());
    addObject(gm);

    auto obj1 = new Rectangle(glm::vec3(10, 10, 1), glm::vec2(128, 128),
                              sf::Color::Green);
    addObject(obj1);

    auto obj2 = new Rectangle(glm::vec3(400, 400, 1), glm::vec2(50, 50),
                              sf::Color::Blue);
    addObject(obj2);

    auto obj3 = new Rectangle(glm::vec3(10, 400, 0), glm::vec2(10, 10),
                              sf::Color::White);
    addObject(obj3);
    auto obj4 = new GameObject();
    obj4->setTexture(
        "/home/adtema/CLionProjects/Pong/"
        "1674270773_catherineasquithgallery-com-p-serii-fon-tekstura-bumagi-"
        "foto-104.jpg");
    obj4->setPosition({0, 0, -50});
    addObject(obj4);
}
void Scene::on_update() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(),
                  [](GameObject *gameObject) { gameObject->fixedUpdate(); });
}
void Scene::destroyGameObject(GameObject *gameObject) {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    auto searched =
        std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
    if (*searched) {
        m_gameObjects.erase(searched);
    }
    delete gameObject;
}
Context *Scene::getContext() { return m_pGameContext; }
