#include "../headers/Scene.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

#include "../../headers/utils.h"
#include "../game/CameraScript.h"
#include "../game/ExitGameScript.h"
#include "../game/InputText.h"
#include "../game/PlayerScript.h"
#include "../game/prefabs/Ball.h"
#include "../game/prefabs/Collision.h"
#include "../headers/Camera.h"
#include "../game/prefabs/Score.h"
#include "../headers/Context.h"
#include "../headers/Log.h"
#include "../headers/templates/Button.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "glm/gtc/type_ptr.hpp"

#define SCALE 30

bool sortGM(GameObject* f, GameObject* s) {
    return f->getPosition().z < s->getPosition().z;
}

void Scene::addObject(GameObject* gameObject) {
    {
        std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
        m_gameObjects.push_back(gameObject);
        m_gameObjects.sort(sortGM);
    }
    gameObject->m_pScene = this;
    gameObject->start();
}

GameObject::~GameObject() { delete m_texture; }

Scene::Scene(float width, float height, Context* context)
    : m_pGameContext(context) {
    m_pCamera = new Camera(width, height);
    context->setCamera(m_pCamera);
    m_pCamera->addComponent(new ExitGameScript());
    addObject(m_pCamera);
    m_pCamera->setPosition({2000, -2000, 0});

    auto collision = new Collision();

    auto hole1 = new Hole(glm::vec3(0, 250, 2), 1);
    addObject(hole1);
    collision->addHole(hole1);
    auto hole2 = new Hole(glm::vec3(490, 240, 2), 2);
    addObject(hole2);
    collision->addHole(hole2);
    auto hole3 = new Hole(glm::vec3(490, -240, 2), 3);
    addObject(hole3);
    collision->addHole(hole3);
    auto hole4 = new Hole(glm::vec3(0, -250, 2), 4);
    addObject(hole4);
    collision->addHole(hole4);
    auto hole5 = new Hole(glm::vec3(-490, -240, 2), 5);
    addObject(hole5);
    collision->addHole(hole5);
    auto hole6 = new Hole(glm::vec3(-490, 240, 2), 6);
    addObject(hole6);
    collision->addHole(hole6);

    auto mainBall = new Ball(0, glm::vec3(100, 0, 5));
    mainBall->addComponent(new PlayerScript());
    addObject(mainBall);
    collision->addBall(mainBall);

    auto ball1 = new Ball(1, glm::vec3(-250, 0, 3));
    addObject(ball1);
    collision->addBall(ball1);

    auto ball2 = new Ball(2, glm::vec3(-302, 0, 3));
    addObject(ball2);
    collision->addBall(ball2);

    auto ball3 = new Ball(3, glm::vec3(-354, 0, 3));
    addObject(ball3);
    collision->addBall(ball3);

    auto ball4 = new Ball(4, glm::vec3(-276, 15, 3));
    addObject(ball4);
    collision->addBall(ball4);

    auto ball5 = new Ball(5, glm::vec3(-276, -15, 3));
    addObject(ball5);
    collision->addBall(ball5);

    auto ball6 = new Ball(6, glm::vec3(-328, -15, 3));
    addObject(ball6);
    collision->addBall(ball6);

    auto ball7 = new Ball(7, glm::vec3(-328, 15, 3));
    addObject(ball7);
    collision->addBall(ball7);

    auto ball8 = new Ball(8, glm::vec3(-302, 30, 3));
    addObject(ball8);
    collision->addBall(ball8);

    auto ball9 = new Ball(9, glm::vec3(-302, -30, 3));
    addObject(ball9);
    collision->addBall(ball9);

    auto ball10 = new Ball(10, glm::vec3(-354, 30, 3));
    addObject(ball10);
    collision->addBall(ball10);

    auto ball11 = new Ball(11, glm::vec3(-354, -30, 3));
    addObject(ball11);
    collision->addBall(ball11);

    auto ball12 = new Ball(12, glm::vec3(-328, -45, 3));
    addObject(ball12);
    collision->addBall(ball12);

    auto ball13 = new Ball(13, glm::vec3(-328, 45, 3));
    addObject(ball13);
    collision->addBall(ball13);

    auto ball14 = new Ball(14, glm::vec3(-354, 60, 3));
    addObject(ball14);
    collision->addBall(ball14);

    auto ball15 = new Ball(15, glm::vec3(-354, -60, 3));
    addObject(ball15);
    collision->addBall(ball15);

    auto sqr =
        new Rectangle(glm::vec3(450, 252, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr->setRotation({0, 0, 45});
    addObject(sqr);
    collision->addWall(sqr);
    auto sqr1 =
        new Rectangle(glm::vec3(502, 201, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr1->setRotation({0, 0, 45});
    addObject(sqr1);
    collision->addWall(sqr1);

    auto sqr2 =
        new Rectangle(glm::vec3(450, -252, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr2->setRotation({0, 0, 45});
    addObject(sqr2);
    collision->addWall(sqr2);
    auto sqr3 =
        new Rectangle(glm::vec3(502, -201, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr3->setRotation({0, 0, 45});
    addObject(sqr3);
    collision->addWall(sqr3);

    auto sqr4 =
        new Rectangle(glm::vec3(-450, 252, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr4->setRotation({0, 0, 45});
    addObject(sqr4);
    collision->addWall(sqr4);
    auto sqr5 =
        new Rectangle(glm::vec3(-502, 201, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr5->setRotation({0, 0, 45});
    addObject(sqr5);
    collision->addWall(sqr5);

    auto sqr6 =
        new Rectangle(glm::vec3(-450, -252, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr6->setRotation({0, 0, 45});
    addObject(sqr6);
    collision->addWall(sqr6);
    auto sqr7 =
        new Rectangle(glm::vec3(-502, -201, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr7->setRotation({0, 0, 45});
    addObject(sqr7);
    collision->addWall(sqr7);

    auto sqr8 =
        new Rectangle(glm::vec3(40, 252, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr8->setRotation({0, 0, 45});
    addObject(sqr8);
    collision->addWall(sqr8);

    auto sqr9 =
        new Rectangle(glm::vec3(-40, 252, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr9->setRotation({0, 0, 45});
    addObject(sqr9);
    collision->addWall(sqr9);

    auto sqr10 =
        new Rectangle(glm::vec3(40, -252, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr10->setRotation({0, 0, 45});
    addObject(sqr10);
    collision->addWall(sqr10);

    auto sqr11 =
        new Rectangle(glm::vec3(-40, -252, 0), glm::vec2(32, 32), {2, 69, 4});

    sqr11->setRotation({0, 0, 45});
    addObject(sqr11);
    collision->addWall(sqr11);

    auto wallTopLeft =
        new Rectangle(glm::vec3(-245, 240, 0), glm::vec2(410, 20), {2, 69, 4});

    addObject(wallTopLeft);
    collision->addWall(wallTopLeft);

    auto wallTopRight =
        new Rectangle(glm::vec3(245, 240, 0), glm::vec2(410, 20), {2, 69, 4});
    addObject(wallTopRight);
    collision->addWall(wallTopRight);

    auto wallDownRight =
        new Rectangle(glm::vec3(245, -240, 0), glm::vec2(410, 20), {2, 69, 4});
    addObject(wallDownRight);
    collision->addWall(wallDownRight);

    auto wallDownLeft =
        new Rectangle(glm::vec3(-245, -240, 0), glm::vec2(410, 20), {2, 69, 4});
    addObject(wallDownLeft);
    collision->addWall(wallDownLeft);

    auto wallRight =
        new Rectangle(glm::vec3(490, 0, 0), glm::vec2(20, 400), {2, 69, 4});
    addObject(wallRight);
    collision->addWall(wallRight);

    auto wallLeft =
        new Rectangle(glm::vec3(-490, 0, 0), glm::vec2(20, 400), {2, 69, 4});
    addObject(wallLeft);
    collision->addWall(wallLeft);

    auto table0 =
        new Rectangle(glm::vec3(0, 0, -1), glm::vec2(1000, 500), {5, 50, 15});
    addObject(table0);

    auto table1 =
        new Rectangle(glm::vec3(0, 270, 1), glm::vec2(1080, 40), {40, 30, 0});
    addObject(table1);
    auto table2 =
        new Rectangle(glm::vec3(0, -270, 1), glm::vec2(1080, 40), {40, 30, 0});
    addObject(table2);
    auto table3 =
        new Rectangle(glm::vec3(520, 0, 1), glm::vec2(40, 500), {40, 30, 0});
    addObject(table3);
    auto table4 =
        new Rectangle(glm::vec3(-520, 0, 1), glm::vec2(40, 500), {40, 30, 0});
    addObject(table4);

    addObject(collision);

    // Menu


  auto textName = new Text();
  textName->setPosition({1450,2300,0});
  textName->active = false;
  addObject(textName);

    auto down = new Rectangle(glm::vec3(-2000, 2200, 0), glm::vec2(300, 100),
                              {100, 100, 100});
    addObject(down);

    auto inputName = new Text("#");
    inputName->setPosition({-2000, 2200, 2});
    addObject(inputName);
    inputName->active = false;
    inputName->addComponent(
        new InputText([textName,this, inputName](const std::string& string) {
            m_playerName = string;
            inputName->active = false;
            m_pCamera->setPosition({2000, -2000, 0});
            file(m_playerName);
            textName->setText(m_playerName);
            textName->active = true;
        }));
    addObject(inputName);

    auto btnMenu = new Button();
    btnMenu->setBackgroundColor(sf::Color::Magenta);
    btnMenu->setSize(glm::vec2(80, 30));
    btnMenu->setText("Меню");
    btnMenu->setCharacterSize(25);
    btnMenu->setTextColor(sf::Color::Black);
    btnMenu->setPosition({560, 325, 2});
    btnMenu->setMouseOverAction([btnMenu] {
        btnMenu->setScale({1.05f, 1.05f, 1.05f});
    });
    btnMenu->setMouseOutAction([btnMenu] {
        btnMenu->setScale({1.f, 1.f, 1.f});
    });
    btnMenu->setMouseClickAction([btnMenu, this] {
        m_pCamera->setPosition({2000, -2000, 0});
    });
    addObject(btnMenu);

    auto btnCon = new Button();
    btnCon->setBackgroundColor(sf::Color::Magenta);
    btnCon->setSize(glm::vec2(300, 100));
    btnCon->setText("Продолжить");
    btnCon->setCharacterSize(35);
    btnCon->setTextColor(sf::Color::Black);
    btnCon->setPosition({2000, 2150, 0});
    btnCon->setMouseOverAction([btnCon] {
        btnCon->setScale({1.05f, 1.05f, 1.05f});
    });
    btnCon->setMouseOutAction([btnCon] { btnCon->setScale({1.f, 1.f, 1.f}); });
    btnCon->setMouseClickAction([btnCon, this] {
        m_pCamera->setPosition({0, 0, 0});
    });
    addObject(btnCon);

    auto btnNew = new Button();
    btnNew->setBackgroundColor(sf::Color::Magenta);
    btnNew->setSize(glm::vec2(300, 100));
    btnNew->setText("Начать заново");
    btnNew->setCharacterSize(35);
    btnNew->setTextColor(sf::Color::Black);
    btnNew->setPosition({2000, 2000, 0});
    btnNew->setMouseOverAction([btnNew] {
        btnNew->setScale({1.05f, 1.05f, 1.05f});
    });
    btnNew->setMouseOutAction([btnNew] { btnNew->setScale({1.f, 1.f, 1.f}); });
    btnNew->setMouseClickAction([btnNew, this] {
        m_pCamera->setPosition({0, 0, 0});
        restartTable();
    });
    addObject(btnNew);

    auto butNewP = new Button();
    butNewP->setBackgroundColor(sf::Color::Magenta);
    butNewP->setSize(glm::vec2(300, 100));
    butNewP->setText("Сохранить");
    butNewP->setCharacterSize(35);
    butNewP->setTextColor(sf::Color::Black);
    butNewP->setPosition({2000, 1850, 0});
    butNewP->setMouseOverAction([butNewP] {
        butNewP->setScale({1.05f, 1.05f, 1.05f});
    });
    butNewP->setMouseOutAction([butNewP] {
        butNewP->setScale({1.f, 1.f, 1.f});
    });
    butNewP->setMouseClickAction([inputName, this] {
        save(m_playerName);
    });
    addObject(butNewP);

    auto btnInfo = new Button();
    btnInfo->setBackgroundColor(sf::Color::Magenta);
    btnInfo->setSize(glm::vec2(300, 100));
    btnInfo->setText("Справка");
    btnInfo->setCharacterSize(35);
    btnInfo->setTextColor(sf::Color::Black);
    btnInfo->setPosition({1600, 1850, 0});
    btnInfo->setMouseOverAction([btnInfo] {
        btnInfo->setScale({1.05f, 1.05f, 1.05f});
    });
    btnInfo->setMouseOutAction([btnInfo] {
        btnInfo->setScale({1.f, 1.f, 1.f});
    });
    btnInfo->setMouseClickAction([inputName, this] {
        openFile("info.txt");
    });
    addObject(btnInfo);

    auto btnScore = new Button();
    btnScore->setBackgroundColor(sf::Color::Magenta);
    btnScore->setSize(glm::vec2(300, 100));
    btnScore->setText("Рекорды");
    btnScore->setCharacterSize(35);
    btnScore->setTextColor(sf::Color::Black);
    btnScore->setPosition({2400, 1850, 0});
    btnScore->setMouseOverAction([btnScore] {
        btnScore->setScale({1.05f, 1.05f, 1.05f});
    });
    btnScore->setMouseOutAction([btnScore] {
        btnScore->setScale({1.f, 1.f, 1.f});
    });
    btnScore->setMouseClickAction([inputName, this] {
        openFile("scores.txt");
    });
    addObject(btnScore);

    auto butContinue = new Button();
    butContinue->setBackgroundColor(sf::Color::Magenta);
    butContinue->setSize(glm::vec2(150, 45));
    butContinue->setText("Продолжить");
    butContinue->setCharacterSize(20);
    butContinue->setTextColor(sf::Color::Black);
    butContinue->setPosition({0, -400, 0});
    butContinue->setMouseOverAction([butContinue] {
        butContinue->setScale({1.05f, 1.05f, 1.05f});
    });
    butContinue->setMouseOutAction([butContinue] {
        butContinue->setScale({1.f, 1.f, 1.f});
    });
    butContinue->setMouseClickAction([inputName, butContinue, this] {
        m_pCamera->setPosition({-2000, -2200, 0});
        inputName->active = true;
        restartTable();
    });
    addObject(butContinue);

    auto butEnd = new Button();
    butEnd->setBackgroundColor(sf::Color::Magenta);
    butEnd->setSize(glm::vec2(150, 45));
    butEnd->setText("Продолжить");
    butEnd->setCharacterSize(20);
    butEnd->setTextColor(sf::Color::Black);
    butEnd->setPosition({-2000, -2300, 0});
    butEnd->setMouseOverAction([butEnd] {
        butEnd->setScale({1.05f, 1.05f, 1.05f});
    });
    butEnd->setMouseOutAction([butEnd] { butEnd->setScale({1.f, 1.f, 1.f}); });
    butEnd->setMouseClickAction([butEnd, this] {
        m_pCamera->setPosition({2000, -2000, 0});
        save(m_playerName);
        restartTable();
    });
    addObject(butEnd);


    screensaver();

    /*auto obj4 = new GameObject();
    obj4->setTexture(
        "/home/adtema/CLionProjects/Pong/"
        "1674270773_catherineasquithgallery-com-p-serii-fon-tekstura-bumagi-"
        "foto-104.jpg");
    obj4->setPosition({0, 0, -50});
    addObject(obj4);
*/
}
void Scene::on_update() {
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(),
                  [](GameObject* gameObject) { gameObject->fixedUpdate(); });
    destroyGameObjects();
}
void Scene::destroyGameObject(GameObject* gameObject) {
    if (gameObject) {
        m_toDestroyObjects.push(gameObject);
    }
}
void Scene::destroyGameObjects() {
    while (!m_toDestroyObjects.empty()) {
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
Context* Scene::getContext() { return m_pGameContext; }

void Scene::screensaver() {
    m_gameObjects_mutex.unlock();
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);

    Camera* m_camera;
    Ball* m_ball;

    for (auto& m_object : m_gameObjects) {
        if (typeid(*m_object) == typeid(Camera)) {
            m_camera = dynamic_cast<Camera*>(m_object);
            m_camera->setPosition({0, 70, 0});
        } else if (typeid(*m_object) == typeid(Ball)) {
            m_ball = dynamic_cast<Ball*>(m_object);
            if (m_ball->number == 0) {
                m_ball->m_body->SetLinearVelocity({-100, 5});
            }
        }else if (typeid(*m_object) == typeid(Score)){
            m_score = dynamic_cast<Score*>(m_object);
        }
    }
}

void Scene::endGame() {
    m_gameObjects_mutex.unlock();
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);

    Camera* m_camera;
    Ball* m_ball;

    for (auto& m_object : m_gameObjects) {
        if (typeid(*m_object) == typeid(Score)) {
            dynamic_cast<Score*>(m_object)->setPosition({-2000, -2000, 10});
        } else if (typeid(*m_object) == typeid(Camera)) {
            m_camera = dynamic_cast<Camera*>(m_object);
            m_camera->setPosition({-2000, 2000, 0});
        }
    }
}

void Scene::restartTable() {
    m_gameObjects_mutex.unlock();
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);

    for (auto& m_object : m_gameObjects) {
        if (typeid(*m_object) == typeid(Ball)) {
            LOG_INFO("Ball " +
                     std::to_string(dynamic_cast<Ball*>(m_object)->number) +
                     " restarted");
            auto startPos = dynamic_cast<Ball*>(m_object)->startPos;
            m_object->setPosition(startPos);
            dynamic_cast<Ball*>(m_object)->m_body->SetTransform(
                {startPos.x / SCALE, startPos.y / SCALE}, 0);
            dynamic_cast<Ball*>(m_object)->m_body->SetLinearVelocity({0, 0});
        } else if (typeid(*m_object) == typeid(Score)) {
            dynamic_cast<Score*>(m_object)->setPosition({0, 320, 10});
            dynamic_cast<Score*>(m_object)->setScore(0);
            LOG_INFO("Score restarted");
        }
    }
}

void Scene::file(std::string name) {
    std::ifstream infile(name + ".json");
    if (!infile.good()) {

        std::ofstream outfile(name + ".json");
        if (outfile.good()) {
            toJson(outfile);
            outfile.close();
        }
    } else {
        if (infile.good()) {
            LOG_INFO("All OK");
        }
        outJson(infile);
        infile.close();
    }
}
void Scene::toJson(std::ofstream& ofstream) {
    nlohmann::json json;
    for (auto& m_object : m_gameObjects) {
        if (typeid(*m_object) == typeid(Ball)) {
            float arr[3];
            glm::vec3::value_type* ptr = const_cast<float*>(
                glm::value_ptr(dynamic_cast<Ball*>(m_object)->getPosition()));
            std::copy(ptr, ptr + 3, arr);
            json.push_back(nlohmann::json::array(
                {   {   {"number", dynamic_cast<Ball*>(m_object)->number},{"position", arr}    }    }
 ));
        }else if(typeid(*m_object) == typeid(Score)){
            json.push_back(nlohmann::json::array({{{"number", 1000},{"score", dynamic_cast<Score*>(m_object)->m_score}}}));
        }
    }
    ofstream << std::setw(4) << json << std::endl;
}
void Scene::outJson(std::ifstream& infile) {
    m_gameObjects_mutex.unlock();
    std::unique_lock<std::mutex> lock(m_gameObjects_mutex);
    LOG_INFO("In outJson");

    nlohmann::json json = nlohmann::json::parse(infile);
    LOG_INFO("In nlohmann::json");


    for (auto& obj : json) {
        for (auto& m_object : m_gameObjects) {
            LOG_INFO("Beh number");
            int number = obj[0]["number"];
            LOG_INFO("number");
            LOG_INFO(number);
            if (typeid(*m_object) == typeid(Ball)) {
                LOG_INFO("Typeid");
                if (dynamic_cast<Ball*>(m_object)->number == int(obj[0]["number"])) {
                    LOG_INFO("123123123");
                    auto position = obj[0]["position"];
                    dynamic_cast<Ball*>(m_object)->m_body->SetTransform(
                        {float(position[0])/SCALE, float(position[1])/SCALE}, 0);
                    dynamic_cast<Ball*>(m_object)->setPosition(
                        {position[0], position[1], position[2]});
                    dynamic_cast<Ball*>(m_object)->m_body->SetLinearVelocity({0,0});
                }
            }else if(typeid(*m_object) == typeid(Score) && number == 1000){
                dynamic_cast<Score*>(m_object)->setScore(obj[0]["score"]);
                m_score =  dynamic_cast<Score*>(m_object);
            }
        }
    }
}
void Scene::save(std::string name) {

    saveScores(name, m_score);
    std::ofstream ofScores;
    ofScores.open("/home/adtema/CLionProjects/Pong/scores.txt");
    for (auto obj :scores){
        ofScores << obj.first + "\t" + std::to_string(obj.second) + "\n";
    }
    ofScores.close();

    std::ofstream infile(name + ".json");
    if (!infile.good()) {

        std::ofstream outfile(name + ".json");
        if (outfile.good()) {
            toJson(outfile);
            outfile.close();
        }
    } else {
        if (infile.good()) {
            LOG_INFO("All OK");
        }
        toJson(infile);
        infile.close();
    }
}
void Scene::openFile(std::string name) {
    std::string filePath = "/home/adtema/CLionProjects/Pong/" + name;
    std::string command = "kate -b " + filePath;
    std::system(command.c_str());
}
void Scene::saveScores(std::string name, Score* m_score) {

    std::ifstream file("/home/adtema/CLionProjects/Pong/scores.txt");
    if (!file) {
        std::cerr << "Не удалось открыть файл\n";
        LOG_ERROR("Не удалось открыть файл");
    }

    std::string str;
    int num;

    while (file >> str >> num) {
        if (str[0] == '#') {
            scores.push_back(std::make_pair(str, num));
        }
    }

    file.close();

    for (const auto &pair : scores) {
        LOG_INFO(pair.first + "%" + std::to_string(pair.second));
    }


    auto finded = std::find_if(scores.begin(), scores.end(), [name](auto score){
        return score.first == name; });
    if(finded != scores.end()){
        if (finded->second < m_score->m_score){
            finded->second = m_score->m_score;
        }
    }else {
        scores.push_back({name, m_score->m_score});
    }
    scores.sort();
}
