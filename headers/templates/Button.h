#ifndef GOLF_BUTTON_H
#define GOLF_BUTTON_H
#pragma once

#include "../GameObject.h"
#include "SFML/Graphics.hpp"

class Button: public GameObject {

    enum Mouse{
        Click,
        Down,
        Up,
        Over,
        Out,
        
        CountActions
    };
    
    std::unique_ptr<sf::Text> m_pText;
    sf::Font m_font;

    glm::vec2 m_size;

    sf::Color m_backgroundColor;

    std::function<void()> m_actionFunctions[CountActions];
    bool m_actions[CountActions]{};

    void updateTextureBackground();
    void updateTextureBackground(sf::Texture *texture);

   public:
    explicit Button(glm::vec2 size = glm::vec2(10), sf::Color color = sf::Color::White);
    explicit Button(sf::Text text, glm::vec2 size = glm::vec2(10), sf::Color color = sf::Color::White);

    [[maybe_unused]] void setText([[maybe_unused]] sf::Text text);
    [[maybe_unused]] void setText(const std::string& string);
    [[maybe_unused]] void setFont(sf::Font font);
    [[maybe_unused]] void setCharacterSize(unsigned int size);
    [[maybe_unused]] void setTextColor(sf::Color color);

   
    [[maybe_unused]] void setMouseClickAction(std::function<void()> action);
    [[maybe_unused]] void setMouseDownAction(std::function<void()> action);
    [[maybe_unused]] void setMouseUpAction(std::function<void()> action);
    [[maybe_unused]] void setMouseOverAction(std::function<void()> action);
    [[maybe_unused]] void setMouseOutAction(std::function<void()> action);


    void setSize(glm::vec2 size);


    [[maybe_unused]] void setBackgroundColor(sf::Color color);
    void setBackground(const sf::Texture& texture);


    glm::vec2 getSize() {return m_size;};

    void update() override;

   private:
    void checkMouseActions();
    void startMouseFunctions();

};

#endif