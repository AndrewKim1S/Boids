#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Vector.h"
#include <iostream>

class Boid{

  public:
    Boid();
    Boid(float x, float y, sf::Color c);
    ~Boid();

    void run();
    void render(sf::RenderTarget& window);

    // Boid Laws - seperation, alignment, cohesion
    void seperation();
    void alignment();
    void cohesion(Vector center);

    // complex rules: obstacle avoidance & goal seeking

    // Accessors & Mutators
    Vector getPos();
    void setSelected(bool b);

  private:
    // Movement Vectors
    Vector position;
    Vector velocity;
    Vector acceleration;

    // These are vector offsets from rules
    Vector v1, v2, v3;

    // Maximum movement parameters
    float maxSpeed = 4;
    float maxForce = 0.5;

    // For Drawing Visual
    sf::Color color;
    sf::ConvexShape shape;
    sf::CircleShape visualRange;

    // Weights
    double seperationWeight;
    double alignmentWeight;
    double cohesionWeight;

    // shape constants
    const double widthShape = 7;
    const double lengthShape = 14.5;
    const double visual = 165;

    // Other
    bool selected;
};
