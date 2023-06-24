#ifndef PONG_BALL_H
#define PONG_BALL_H

#include "../../headers/GameObject.h"



class Ball: public GameObject{
   public:
    enum {
        RADIUS = 25,
    };
    Ball(char number, glm::vec3 position);

    void fixedUpdate() override;

    char number;
    float friction = .1f;
    float force = 0;

    glm::vec2 velocity{0 ,0};
};

#endif  // PONG_BALL_H
