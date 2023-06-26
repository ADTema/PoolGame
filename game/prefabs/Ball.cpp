#include "Ball.h"

#include "../../headers/GameObject.h"
#include "../../headers/Log.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Text.hpp"
#include "glm/gtx/compatibility.hpp"

#define SCALE 30

Ball::Ball(char number, glm::vec3 position): number(number) {

    sf::Font font;
    font.loadFromFile("/home/adtema/CLionProjects/Pong/Arial/arialmt.ttf");

    LOG_INFO("Player created");
    sf::CircleShape circle(RADIUS);
    sf::RenderTexture texture;
    sf::Text text(font, std::to_string(number),15);
    text.setFillColor(sf::Color::Black);

    texture.create({2 * RADIUS,2 * RADIUS});
    texture.setSmooth(true);
    texture.clear(sf::Color::Transparent);

    circle.setFillColor(sf::Color::White);

    texture.draw(circle);

    circle.setFillColor(colors[number]);

    if(number > 8){
        circle.setRadius(RADIUS-3);
        circle.setOrigin({-3,-3});
    }

    text.setOrigin({-5,-4});
    texture.draw(circle);
    texture.draw(text);
    texture.display();
    setPosition(position);
    auto *nt = new sf::Texture(texture.getTexture());
    setTexture(nt);
}
void Ball::fixedUpdate() {
    GameObject::fixedUpdate();
    auto pos = m_body->GetPosition();
    setPosition({pos.x*SCALE,pos.y*SCALE, getPosition().z});
}
