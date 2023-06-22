#ifndef PONG_CONTEXT_H
#define PONG_CONTEXT_H

#pragma once
#include <chrono>
#include <glm/glm.hpp>
#include <string>

#include "Game.h"
#include "SFML/Window/Event.hpp"

class Context {

    friend int Game::start();

   private:
    struct WindowData
    {
        std::string title;
        unsigned int width{};
        unsigned int height{};
    };

    WindowData m_mainWidowData;
    long deltaTime;

    sf::Event m_event{};

    bool m_running = false;

   public:

    Context(){};

    WindowData getWindowData(){return m_mainWidowData;};

    void stopGame();

    void setWindowsData(WindowData win_data);

    [[nodiscard]] bool getRunning() const{return m_running;};

    sf::Event &getEvent() {return m_event;};

};

#endif  // PONG_CONTEXT_H
