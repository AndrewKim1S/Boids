#include "TextInput.h"
#include <iostream>


// Constructor
TextInput::TextInput(){}

TextInput::TextInput(size_t maxChars){
  size = maxChars;
  rect = sf::RectangleShape((sf::Vector2f(30*2, 40)));
    // 15 pixels length, 20 pixels chars
  hasFocus = false;

  rect.setOutlineThickness(2);
  rect.setFillColor(sf::Color::White);
  rect.setOutlineColor(sf::Color(127,127,127));
  rect.setPosition(this->getPosition());
}

// accessor for text 
const std::string TextInput::getString() const {
  return text;
}

// set position of text input
void TextInput::setPosition(float x, float y){
  rect.setPosition(x, y);
}

// accessor for mouse position and text input
bool TextInput::contains(sf::Vector2f point){
  return rect.getGlobalBounds().contains(point);
}

// Mutator for focus control
void TextInput::setFocus(bool focus){
  hasFocus = focus;
  if(focus){
    rect.setOutlineColor(sf::Color::Blue);
  } else {
    rect.setOutlineColor(sf::Color(127, 127, 127)); // Gray
  }
}

// handle an event
void TextInput::handleInput(sf::Event ev){
  if(!hasFocus || ev.type != sf::Event::TextEntered) {
    return; 
  } if(ev.text.unicode == 8){
    std::cout << "h" << std::endl;
    text = text.substr(0, text.size()-1);
  } else if (text.size() < size){
    text += ev.text.unicode;
  }
}

sf::RectangleShape TextInput::getShape(){
  return rect;
}
