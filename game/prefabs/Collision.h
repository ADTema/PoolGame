#ifndef PONG_COLLISION_H
#define PONG_COLLISION_H

#pragma once

#include "../../headers/GameObject.h"
#include "Ball.h"
#include "Rectangle.h"

class Collision: public GameObject {
   public:
    std::pair<bool, glm::vec3> checkCollision( Ball* ball1,  Ball* ball2);
    static std::pair<bool, glm::vec3> checkCollision( Ball* ball,  Rectangle* wall);

    void fixedUpdate() override;
    void addBall(Ball * ball);
    void addWall(Rectangle * wall);


    std::list<Ball *> m_balls;
    std::list<Rectangle *> m_walls;

};


#endif  // PONG_COLLISION_H
