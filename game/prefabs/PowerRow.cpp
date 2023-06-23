#include "PowerRow.h"

#include "../../headers/Log.h"

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

PowerRow::PowerRow() {

    LOG_INFO("PowerRow");
    sf::RectangleShape rectangle(sf::Vector2f(30, 3));
    sf::RenderTexture texture;
    rectangle.setFillColor(sf::Color::White);
    texture.create({30, 3});
    texture.clear();
    texture.draw(rectangle);
    texture.display();
    auto *nt = new sf::Texture(texture.getTexture());
    setTexture(nt);
    setPosition({0,0,2});
}
