#ifndef PONG_PLAYERSCRIPT_H
#define PONG_PLAYERSCRIPT_H

#pragma once

#include "../headers/Component.h"
#include "glm/vec3.hpp"

class PlayerScript: public Component  {
   public:
    void start() override;
    void update() override;
    void fixedUpdate() override;

    glm::vec3 position;
};

#endif  // PONG_PLAYERSCRIPT_H
