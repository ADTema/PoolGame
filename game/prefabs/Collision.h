#ifndef PONG_COLLISION_H
#define PONG_COLLISION_H

#pragma once

#include "../../headers/GameObject.h"
#include "../../headers/templates/Text.h"
#include "Ball.h"
#include "Hole.h"
#include "Rectangle.h"
#include "box2d/box2d.h"

#include "Score.h"

class Collision: public GameObject {
   public:
    void start() override;
    void fixedUpdate() override;
    void addBall(Ball * ball);
    void addWall(Rectangle * wall);
    void addHole(Hole * hole);

    std::list<Ball *> m_balls;
    std::list<Rectangle *> m_walls;
    std::list<Hole *> m_hols;

    Score *tScore = nullptr;

    b2World world{{0,0}};

    int score = 0;

};


#endif  // PONG_COLLISION_H
