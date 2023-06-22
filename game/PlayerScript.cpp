#include "PlayerScript.h"

#include "../headers/GameObject.h"
#include "SFML/Graphics.hpp"
#include "../headers/Log.h"

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

    glm::vec3 position = gameObject->getPosition();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        gameObject->setPosition(position + glm::vec3(-moveSpeed, 0.0f, 0.0f));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
         gameObject->setPosition(position + glm::vec3(moveSpeed, 0.0f, 0.0f));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
          gameObject->setPosition(position + glm::vec3(0.0f, moveSpeed, 0.0f));
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
          gameObject->setPosition(position + glm::vec3(0.0f, -moveSpeed, 0.0f));
    }
}
