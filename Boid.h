#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Vector.h"

class Boid{

  public:
    Boid();
    Boid(float x, float y, sf::Color c);
    ~Boid();

    void run();
    void flock();

    // Boid Laws - seperation, alignment, cohesion
    Vector seperation();
    Vector alignment();
    Vector cohesion();

    // complex rules: obstacle avoidance & goal seeking

  private:
    Vector position;
    Vector velocity;
    Vector acceleration;

    float maxSpeed = 4;
    float maxForce = 0.5;

    sf::Color color;
};
