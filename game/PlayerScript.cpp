#include "PlayerScript.h"

#include "../headers/Context.h"
#include "../headers/GameObject.h"
#include "../headers/Log.h"
#include "SFML/Graphics.hpp"
#include "glm/gtx/compatibility.hpp"

void PlayerScript::start() {

    LOG_INFO("Player created");
    sf::RectangleShape rectangle(sf::Vector2f(256, 256));
    sf::RenderTexture texture;
    rectangle.setFillColor(sf::Color::Red);
    gameObject->setPosition({1, 0, 1});
//    gameObject->setScale({0.1, 0.1, 0.1});
    texture.create({256,256});
    texture.clear();
    texture.draw(rectangle);
    texture.display();
    auto *nt = new sf::Texture(texture.getTexture());
//    gameObject->setTexture("/home/adtema/CLionProjects/Pong/pngwing.com.png");
    gameObject->setTexture(nt);/*
    gameObject->setRotation({0,45,45});*/

    powerRow = new PowerRow();

    powerRow->active = false;
    gameObject->m_pScene->addObject(powerRow);
}
void PlayerScript::update() {

}
void PlayerScript::fixedUpdate() {

    auto context = this->gameObject->getContext();

    if(context->isMouseKeyPressed(sf::Mouse::Button::Left)){
        if(!leftMousePressed){
            powerRow->active = true;
            leftMousePressed = true;
            oldMousePos = context->getMousePosition();
        }
    }
    if(!context->isMouseKeyPressed(sf::Mouse::Button::Left)){
        if(leftMousePressed){
            powerRow->active = false;
            leftMousePressed = false;
            mousePos = context->getMousePosition();
            velocity = glm::normalize(oldMousePos - mousePos) * glm::vec2(1, -1);
            force = glm::length(oldMousePos - mousePos);
        }
    }
    if(force >= 0.001){
        force = glm::lerp<float>(force,0.f,0.3f * friction);
        auto pos = gameObject->getPosition() + glm::vec3(velocity * (force / 10), 0);
        gameObject->setPosition(pos);
    }
}
