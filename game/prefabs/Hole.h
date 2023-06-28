#ifndef PONG_HOLE_H
#define PONG_HOLE_H

#include "../../headers/GameObject.h"

#include "SFML/Graphics/Font.hpp"

class Hole: public GameObject{
   public:
    enum {
        RADIUS = 20,
    };
    Hole(glm::vec3 position, char bonus);

    void fixedUpdate() override;

    char bonus = 1;

    sf::Font font;
};


#endif  // PONG_HOLE_H
