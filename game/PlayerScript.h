#ifndef PONG_PLAYERSCRIPT_H
#define PONG_PLAYERSCRIPT_H

#pragma once

#include "../headers/Component.h"

class PlayerScript: public Component  {
   public:
    void start() override;
    void update() override;
    void fixedUpdate() override;
};

#endif  // PONG_PLAYERSCRIPT_H
