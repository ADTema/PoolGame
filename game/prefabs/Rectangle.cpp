#include "Rectangle.h"

#include "../../headers/Log.h"
#include "../../headers/GameObject.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics.hpp"

Rectangle::Rectangle(glm::vec3 position, glm::vec2 size, sf::Color color) {

    LOG_INFO("Rectangle created");
    sf::RectangleShape rectangle(sf::Vector2f(size.x, size.y));
    sf::RenderTexture texture;
    rectangle.setFillColor(color);
    setPosition(position);
    //    gameObject->setScale({0.1, 0.1, 0.1});
    texture.create({static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)});
    texture.clear();
    texture.draw(rectangle);
    texture.display();
    auto *nt = new sf::Texture(texture.getTexture());
    //    gameObject->setTexture("/home/adtema/CLionProjects/Pong/pngwing.com.png");
    setTexture(nt);
}
