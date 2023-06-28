#ifndef GOLF_TEXT_H
#define GOLF_TEXT_H
#pragma once

#include <SFML/Graphics.hpp>

#include "../GameObject.h"


class Text: public GameObject{

    std::unique_ptr<sf::Text> m_pText;

   public:
    Text();
    explicit Text(const sf::Text& text);
    explicit Text(const std::string& string, unsigned characterSize = 30);

    void update() override;

    [[maybe_unused]] void setText(const sf::Text& text);
    void setText(const std::string& string);
    [[maybe_unused]] void setColor(sf::Color color);
    [[maybe_unused]] void setFont(const sf::Font& font);
    [[maybe_unused]] void setCharacterSize(unsigned size);



   protected:
    void updateTextTexture();
};

#endif