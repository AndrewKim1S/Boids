#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class TextInput : public sf::Transformable{
  public:
    TextInput();
    TextInput(size_t maxChars);
    const std::string getString() const;
    void setPosition(float x, float y);
    bool contains(sf::Vector2f point);
    void setFocus(bool focus);
    void handleInput(sf::Event ev);
    sf::RectangleShape getShape();

  private:
    size_t size;
    bool hasFocus;
    
    sf::RectangleShape rect;
    std::string text;
};
