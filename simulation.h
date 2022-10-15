#pragma once

#include "TextInput.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

// Flock settings
#define MaxFlockSize = 15

class simulation{
  
  public:
    simulation(int w, int l);
    ~simulation();
    bool isClosed();
    void run();

  private:
    // Simulation states
    enum State{
      RUN,
      PAUSE,
      MENU
    };

    // Main functions
    void update();
    void render();
    void pollEvents();

    // Manage flocks
    void createFlock();
    void addBoidToFlock();

    // Menu screen
    void displayMenu();
    
    // Flocks
    int numFlocks;
   
    // Window
    sf::RenderWindow* window;
    int width;
    int height;

    // Simulation state
    State state;
    
    // Keyboard and Mouse events
    sf::Event ev;

    // Texts and fonts
    sf::Font font;
    sf::Text title;
    sf::Text menuInfo;
    sf::Text menuTextEntry;
    sf::Text simState;

    TextInput menuInput;
};
