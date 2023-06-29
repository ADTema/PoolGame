#include "Ball.h"

#include "../../headers/Log.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Text.hpp"

#define SCALE 30

Ball::Ball(char number, glm::vec3 position) : number(number) {

    startPos = position;

    auto *font = new sf::Font();
    if(!font->loadFromFile("/home/adtema/CLionProjects/Pong/Arial/arialmt.ttf")){
        LOG_ERROR("Font on ball not load");
    }

    LOG_INFO("Player created");
    sf::CircleShape circle(RADIUS);
    sf::RenderTexture texture;
    auto  text = new sf::Text(*font, std::to_string(number), 18);
    text->setFillColor(sf::Color::Black);
    if(!texture.create({2 * RADIUS, 2 * RADIUS})){
        LOG_ERROR("Texture on ball not created11");
    }
    texture.setSmooth(true);
    texture.clear(sf::Color::Transparent);
    circle.setFillColor(sf::Color::White);
    texture.draw(circle);
    circle.setFillColor(colors[number]);

    if (number > 8) {
        circle.setRadius(RADIUS - 3);
        circle.setOrigin({-3, -3});
    }
    if (number > 9) {
        text->setOrigin({-5, -4});
    }else {
        text->setOrigin({-9, -4});
    }

    texture.draw(circle);
    if(number != 0){
        texture.draw(*text);
    }

    texture.display();
    setPosition(position);
    auto *nt = new sf::Texture(texture.getTexture());
    setTexture(nt);
}
void Ball::fixedUpdate() {
    GameObject::fixedUpdate();
    auto pos = m_body->GetPosition();
    setPosition({pos.x * SCALE, pos.y * SCALE, getPosition().z});
}
