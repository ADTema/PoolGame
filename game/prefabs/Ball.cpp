#include "Ball.h"

#include "../../headers/GameObject.h"
#include "../../headers/Log.h"
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/RenderTexture.hpp"
#include "glm/gtx/compatibility.hpp"



Ball::Ball(char number, glm::vec3 position): number(number) {

    LOG_INFO("Player created");
    sf::CircleShape circle(RADIUS);
    sf::RenderTexture texture;
    circle.setOrigin({0,0});
    circle.setFillColor(sf::Color::Blue);
    texture.create({2 * RADIUS,2 * RADIUS});
    texture.clear();
    texture.clear(sf::Color::Transparent);
    texture.draw(circle);
    texture.display();
    setPosition(position);
    auto *nt = new sf::Texture(texture.getTexture());
    setTexture(nt);

}
void Ball::fixedUpdate() {
    GameObject::fixedUpdate();

    if(force >= 0.3){
        force = glm::lerp<float>(force,0.f,0.3f * friction);
        auto pos = getPosition() + glm::vec3(velocity * (force / 10), 0);
        setPosition(pos);
    }
    else{
        velocity = glm::vec2(0);
    }
}
