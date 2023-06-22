#include "PlayerScript.h"

#include "../headers/GameObject.h"
#include "SFML/Graphics.hpp"
#include "../headers/Log.h"
#include "../headers/Context.h"

void PlayerScript::start() {
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
    float moveSpeed = 5.0f;

    auto context = this->gameObject->getContext();


        if (context->isKeyPressed(sf::Keyboard::Left))
        {
            glm::vec3 position = gameObject->getPosition();
            gameObject->setPosition(position + glm::vec3(-moveSpeed, 0.0f, 0.0f));
        }
        if (context->isKeyPressed(sf::Keyboard::Right))
        {
            glm::vec3 position = gameObject->getPosition();
            gameObject->setPosition(position + glm::vec3(moveSpeed, 0.0f, 0.0f));
        }
        if (context->isKeyPressed(sf::Keyboard::Up))
        {
            glm::vec3 position = gameObject->getPosition();
            gameObject->setPosition(position + glm::vec3(0.0f, moveSpeed, 0.0f));
        }
        if (context->isKeyPressed(sf::Keyboard::Down))
        {
            glm::vec3 position = gameObject->getPosition();
            gameObject->setPosition(position + glm::vec3(0.0f, -moveSpeed, 0.0f));
        }


}
