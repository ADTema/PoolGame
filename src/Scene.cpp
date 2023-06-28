#include "../headers/Scene.h"

#include <algorithm>

#include "../game/CameraScript.h"
#include "../game/ExitGameScript.h"
#include "../game/PlayerScript.h"
#include "../game/prefabs/Ball.h"
#include "../game/prefabs/Collision.h"
#include "../headers/Camera.h"
#include "../headers/Context.h"
#include "../headers/Log.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "../../headers/utils.h"

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
    addObject(m_pCamera);



    auto collision = new Collision();

    auto hole1 = new Hole(glm::vec3(0,250,2), 1);
    addObject(hole1);
    collision->addHole(hole1);
    auto hole2 = new Hole(glm::vec3(490,240,2), 2);
    addObject(hole2);
    collision->addHole(hole2);
    auto hole3 = new Hole(glm::vec3(490,-240,2), 3);
    addObject(hole3);
    collision->addHole(hole3);
    auto hole4 = new Hole(glm::vec3(0,-250,2), 4);
    addObject(hole4);
    collision->addHole(hole4);
    auto hole5 = new Hole(glm::vec3(-490,-240,2), 5);
    addObject(hole5);
    collision->addHole(hole5);
    auto hole6 = new Hole(glm::vec3(-490,240,2), 6);
    addObject(hole6);
    collision->addHole(hole6);

    auto mainBall = new Ball(0,  glm::vec3(1,1,5));
    mainBall->addComponent(new PlayerScript());
    addObject(mainBall);
    collision->addBall(mainBall);

    auto ball1 = new Ball(1,  glm::vec3(-250, 0,3));
    addObject(ball1);
    collision->addBall(ball1);

    auto ball2 = new Ball(2,  glm::vec3(-302, 0,3));
    addObject(ball2);
    collision->addBall(ball2);

    auto ball3 = new Ball(3,  glm::vec3(-354, 0,3));
    addObject(ball3);
    collision->addBall(ball3);

    auto ball4 = new Ball(4,  glm::vec3(-276, 15,3));
    addObject(ball4);
    collision->addBall(ball4);

    auto ball5 = new Ball(5,  glm::vec3(-276, -15,3));
    addObject(ball5);
    collision->addBall(ball5);

    auto ball6 = new Ball(6,  glm::vec3(-328, -15,3));
    addObject(ball6);
    collision->addBall(ball6);

    auto ball7 = new Ball(7,  glm::vec3 (-328, 15,3));
    addObject(ball7);
    collision->addBall(ball7);

    auto ball8 = new Ball(8,  glm::vec3(-302, 30,3));
    addObject(ball8);
    collision->addBall(ball8);

    auto ball9 = new Ball(9,  glm::vec3(-302, -30,3));
    addObject(ball9);
    collision->addBall(ball9);

    auto ball10 = new Ball(10,  glm::vec3(-354, 30,3));
    addObject(ball10);
    collision->addBall(ball10);

    auto ball11 = new Ball(11,  glm::vec3(-354, -30,3));
    addObject(ball11);
    collision->addBall(ball11);

    auto ball12 = new Ball(12,  glm::vec3(-328, -45,3));
    addObject(ball12);
    collision->addBall(ball12);

    auto ball13 = new Ball(13,  glm::vec3(-328, 45,3));
    addObject(ball13);
    collision->addBall(ball13);

    auto ball14 = new Ball(14,  glm::vec3(-354, 60,3));
    addObject(ball14);
    collision->addBall(ball14);


    auto ball15 = new Ball(15,  glm::vec3(-354, -60,3));
    addObject(ball15);
    collision->addBall(ball15);


    auto sqr = new Rectangle(glm::vec3(450, 252, 0), glm::vec2(32, 32),
                                     {2, 69, 4});

    sqr->setRotation({0,0,45});
    addObject(sqr);
    collision->addWall(sqr);
    auto sqr1 = new Rectangle(glm::vec3(502, 201, 0), glm::vec2(32, 32),
                                     {2, 69, 4});

    sqr1->setRotation({0,0,45});
    addObject(sqr1);
    collision->addWall(sqr1);

    auto sqr2 = new Rectangle(glm::vec3(450, -252, 0), glm::vec2(32, 32),
                                     {2, 69, 4});

    sqr2->setRotation({0,0,45});
    addObject(sqr2);
    collision->addWall(sqr2);
    auto sqr3 = new Rectangle(glm::vec3(502, -201, 0), glm::vec2(32, 32),
                                     {2, 69, 4});

    sqr3->setRotation({0,0,45});
    addObject(sqr3);
    collision->addWall(sqr3);

    auto sqr4 = new Rectangle(glm::vec3(-450, 252, 0), glm::vec2(32, 32),
                                     {2, 69, 4});

    sqr4->setRotation({0,0,45});
    addObject(sqr4);
    collision->addWall(sqr4);
    auto sqr5 = new Rectangle(glm::vec3(-502, 201, 0), glm::vec2(32, 32),
                                     {2, 69, 4});

    sqr5->setRotation({0,0,45});
    addObject(sqr5);
    collision->addWall(sqr5);

    auto sqr6 = new Rectangle(glm::vec3(-450, -252, 0), glm::vec2(32, 32),
                                     {2, 69, 4});

    sqr6->setRotation({0,0,45});
    addObject(sqr6);
    collision->addWall(sqr6);
    auto sqr7 = new Rectangle(glm::vec3(-502, -201, 0), glm::vec2(32, 32),
                                     {2, 69, 4});

    sqr7->setRotation({0,0,45});
    addObject(sqr7);
    collision->addWall(sqr7);

    auto sqr8 = new Rectangle(glm::vec3(40, 252, 0), glm::vec2(32, 32),
                             {2, 69, 4});

    sqr8->setRotation({0,0,45});
    addObject(sqr8);
    collision->addWall(sqr8);

    auto sqr9 = new Rectangle(glm::vec3(-40, 252, 0), glm::vec2(32, 32),
                              {2, 69, 4});

    sqr9->setRotation({0,0,45});
    addObject(sqr9);
    collision->addWall(sqr9);

    auto sqr10 = new Rectangle(glm::vec3(40, -252, 0), glm::vec2(32, 32),
                              {2, 69, 4});

    sqr10->setRotation({0,0,45});
    addObject(sqr10);
    collision->addWall(sqr10);

    auto sqr11 = new Rectangle(glm::vec3(-40, -252, 0), glm::vec2(32, 32),
                              {2, 69, 4});

    sqr11->setRotation({0,0,45});
    addObject(sqr11);
    collision->addWall(sqr11);

    auto wallTopLeft = new Rectangle(glm::vec3(-245, 240, 0), glm::vec2(410, 20),
                                     {2, 69, 4});

    addObject(wallTopLeft);
    collision->addWall(wallTopLeft);

    auto wallTopRight = new Rectangle(glm::vec3(245, 240, 0), glm::vec2(410, 20),
                                      {2, 69, 4});
    addObject(wallTopRight);
    collision->addWall(wallTopRight);

    auto wallDownRight = new Rectangle(glm::vec3(245, -240, 0), glm::vec2(410, 20), {2, 69, 4});
    addObject(wallDownRight);
    collision->addWall(wallDownRight);

    auto wallDownLeft = new Rectangle(glm::vec3(-245, -240, 0), glm::vec2(410, 20),
                                      {2, 69, 4});
    addObject(wallDownLeft);
    collision->addWall(wallDownLeft);

    auto wallRight = new Rectangle(glm::vec3(490, 0, 0), glm::vec2(20, 400),
                              {2, 69, 4});
    addObject(wallRight);
    collision->addWall(wallRight);

    auto wallLeft = new Rectangle(glm::vec3(-490, 0, 0), glm::vec2(20, 400),
                              {2, 69, 4});
    addObject(wallLeft);
    collision->addWall(wallLeft);

    auto table0 = new Rectangle(glm::vec3(0, 0, -1), glm::vec2(1000, 500),
                                {5, 50, 15});
    addObject(table0);

    auto table1 = new Rectangle(glm::vec3(0, 270, 1), glm::vec2(1080, 40),
                               {40, 30, 0});
    addObject(table1);
    auto table2 = new Rectangle(glm::vec3(0, -270, 1), glm::vec2(1080, 40),
                               {40, 30, 0});
    addObject(table2);
    auto table3 = new Rectangle(glm::vec3(520, 0, 1), glm::vec2(40, 500),
                               {40, 30, 0});
    addObject(table3);
    auto table4 = new Rectangle(glm::vec3(-520, 0, 1), glm::vec2(40, 500),
                                {40, 30, 0});
    addObject(table4);



    /*auto obj4 = new GameObject();
    obj4->setTexture(
        "/home/adtema/CLionProjects/Pong/"
        "1674270773_catherineasquithgallery-com-p-serii-fon-tekstura-bumagi-"
        "foto-104.jpg");
    obj4->setPosition({0, 0, -50});
    addObject(obj4);
*/
    addObject(collision);
}
void Scene::on_update() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(),
                  [](GameObject *gameObject) { gameObject->fixedUpdate(); });
    destroyGameObjects();
}
void Scene::destroyGameObject(GameObject *gameObject) {
    if(gameObject){
        m_toDestroyObjects.push(gameObject);
    }
}
void Scene::destroyGameObjects() {
    while (!m_toDestroyObjects.empty()){
        auto gameObject = m_toDestroyObjects.front();
        auto searched =
            std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
        m_toDestroyObjects.pop();
        if (*searched) {
            m_gameObjects.erase(searched);
        }
        delete gameObject;
    }
}
Context *Scene::getContext() { return m_pGameContext; }


