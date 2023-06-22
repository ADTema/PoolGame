#ifndef PONG_CONTEXT_H
#define PONG_CONTEXT_H

#pragma once
#include <chrono>
#include <glm/glm.hpp>
#include <string>

#include "Game.h"
#include "Window.h"
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

    bool m_pressedKeys[static_cast<unsigned long>(sf::Keyboard::Key::KeyCount)];


   public:

    Context(){};

    WindowData getWindowData(){return m_mainWidowData;};

    void stopGame();

    void setWindowsData(WindowData win_data);

    [[nodiscard]] bool getRunning() const{return m_running;};

    sf::Event &getEvent() {return m_event;};

    bool isKeyPressed(sf::Keyboard::Key keyCode);

    void setKeyPressed(sf::Keyboard::Key keyCode);
    void setKeyReleased(sf::Keyboard::Key keyCode);
};

#endif  // PONG_CONTEXT_H
