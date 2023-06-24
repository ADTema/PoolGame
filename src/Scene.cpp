#include "../headers/Scene.h"

#include <algorithm>

#include "../game/CameraScript.h"
#include "../game/ExitGameScript.h"
#include "../game/PlayerScript.h"
#include "../game/prefabs/Ball.h"
#include "../game/prefabs/Collision.h"
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

    auto collision = new Collision();

    auto mainBall = new Ball(1,  glm::vec3(1,1,1));
    mainBall->addComponent(new PlayerScript());
    addObject(mainBall);
    collision->addBall(mainBall);

    auto ball1 = new Ball(1,  glm::vec3(100,100,1));
    addObject(ball1);
    collision->addBall(ball1);

    auto ball2 = new Ball(1,  glm::vec3(150,150,1));
    addObject(ball2);
    collision->addBall(ball2);

    auto wallTop = new Rectangle(glm::vec3(0, 250, 1), glm::vec2(1000, 20),
                              sf::Color::Green);
    addObject(wallTop);
    collision->addWall(wallTop);

    auto wallDown = new Rectangle(glm::vec3(0, -250, 1), glm::vec2(1000, 20),
                              sf::Color::Green);
    addObject(wallDown);
    collision->addWall(wallDown);

    auto wallRight = new Rectangle(glm::vec3(500, 0, 1), glm::vec2(20, 500),
                              sf::Color::Green);
    addObject(wallRight);
    collision->addWall(wallRight);

    auto wallLeft = new Rectangle(glm::vec3(-500, 0, 1), glm::vec2(20, 500),
                              sf::Color::Green);
    addObject(wallLeft);
    collision->addWall(wallLeft);

    auto obj4 = new GameObject();
    obj4->setTexture(
        "/home/adtema/CLionProjects/Pong/"
        "1674270773_catherineasquithgallery-com-p-serii-fon-tekstura-bumagi-"
        "foto-104.jpg");
    obj4->setPosition({0, 0, -50});
    addObject(obj4);

    addObject(collision);
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
