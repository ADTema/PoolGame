#include "PlayerScript.h"

#include "../headers/Context.h"
#include "../headers/GameObject.h"
#include "../headers/Log.h"
#include "SFML/Graphics.hpp"
#include "glm/gtx/compatibility.hpp"
#include "prefabs/Ball.h"

void PlayerScript::start() {

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
            reinterpret_cast<Ball *>(this->gameObject)->velocity = glm::normalize(oldMousePos - mousePos) * glm::vec2(1, -1);
            reinterpret_cast<Ball *>(this->gameObject)->force = glm::length(oldMousePos - mousePos);

            LOG_INFO("Velocity : ({0},{1})\tForce : {2}", reinterpret_cast<Ball *>(this->gameObject)->velocity.x,reinterpret_cast<Ball *>(this->gameObject)->velocity.y,reinterpret_cast<Ball *>(this->gameObject)->force );
        }
    }

}
