#ifndef PONG_PLAYERSCRIPT_H
#define PONG_PLAYERSCRIPT_H

#pragma once

#include "../headers/Component.h"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "prefabs/PowerRow.h"


class PlayerScript: public Component  {
   public:
    void start() override;
    void update() override;
    void fixedUpdate() override;

    bool leftMousePressed = false;

    float radius = 0;
    float friction = .1f;
    float force = 0;

    PowerRow *powerRow = nullptr;

    glm::vec2 velocity{0 ,0};
    glm::vec2 mousePos;
    glm::vec2 oldMousePos;

};

#endif  // PONG_PLAYERSCRIPT_H
