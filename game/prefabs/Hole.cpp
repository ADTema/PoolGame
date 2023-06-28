#include "Hole.h"

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Text.hpp"
#include "../../headers/Log.h"

Hole::Hole(glm::vec3 position, char bonus) {
    if(!font.loadFromFile("/home/adtema/CLionProjects/Pong/Arial/arialmt.ttf")){
        LOG_ERROR("Font on hole not load");
    }
    auto text = new sf::Text(font, "x" + std::to_string(bonus), 18);
    text->setFillColor(sf::Color::White);
    text->setOrigin({-8, -8});

    this->bonus = bonus;
    sf::CircleShape circle(RADIUS);
    sf::RenderTexture texture;
    circle.setOrigin({0,0});
    circle.setFillColor(sf::Color::Black);
    if(!texture.create({2 * RADIUS,2 * RADIUS})){
        LOG_ERROR("Texture on hole not created");
    }
    texture.clear();
    texture.clear(sf::Color::Transparent);
    texture.draw(circle);
    texture.draw(*text);
    texture.display();
    setPosition(position);
    auto *nt = new sf::Texture(texture.getTexture());
    setTexture(nt);
}
void Hole::fixedUpdate() {

}

