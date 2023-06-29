#ifndef PONG_INPUTTEXT_H
#define PONG_INPUTTEXT_H
#pragma once

#include "../headers/Component.h"


#include <functional>
#include <string>


#include <chrono>
#include <functional>
#include <string>


class InputText: public Component{
    std::function<void(const std::string& string)> m_action;

    std::chrono::steady_clock::time_point now;
    uint32_t lastKey;

   public:
    void start() override;
    void update() override;
    void fixedUpdate() override;
    explicit InputText(std::function<void(const std::string& string)> actionAfterEnter);
};


#endif
