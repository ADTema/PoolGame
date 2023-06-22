#include "PlayerScript.h"

#include "../headers/Context.h"
#include "../headers/GameObject.h"
#include "../headers/Log.h"
#include "SFML/Graphics.hpp"
#include "glm/gtx/compatibility.hpp"

void PlayerScript::start() {

    position = gameObject->getPosition();

    LOG_INFO("Player created");
    sf::RectangleShape rectangle(sf::Vector2f(256, 256));
    sf::RenderTexture texture;
    rectangle.setFillColor(sf::Color::Red);
    gameObject->setPosition({1, 0, 0});
    gameObject->setScale({0.1, 0.1, 0.1});
    texture.clear();
    texture.draw(rectangle);
    texture.display();
    auto *nt = new sf::Texture();
    *nt = texture.getTexture();
    gameObject->setTexture("/home/adtema/CLionProjects/Pong/pngwing.com.png");
    //gameObject->setTexture(nt);
}
void PlayerScript::update() {}
void PlayerScript::fixedUpdate() {
    float moveSpeed = 10.0f;
    float smooth = 0.05f;
    glm::vec3 oldPosition = gameObject->getPosition();

    auto context = this->gameObject->getContext();

        if (context->isKeyPressed(sf::Keyboard::Left))
        {
            position = position + glm::vec3(-moveSpeed, 0.0f, 0.0f);
        }
        if (context->isKeyPressed(sf::Keyboard::Right))
        {
            position = position + glm::vec3(moveSpeed, 0.0f, 0.0f);
        }
        if (context->isKeyPressed(sf::Keyboard::Up))
        {
            position = position + glm::vec3(0.0f, moveSpeed, 0.0f);
        }
        if (context->isKeyPressed(sf::Keyboard::Down))
        {
            position = position + glm::vec3(0.0f, -moveSpeed, 0.0f);
        }
        oldPosition = glm::lerp(oldPosition, position, smooth);
        gameObject->setPosition(oldPosition);
}
