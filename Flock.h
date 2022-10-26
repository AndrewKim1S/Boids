#pragma once

#include "Boid.h"
#include "Vector.h"
#include <vector>
#include <iostream>


class Flock{

  public:
    Flock();
    Flock(int boids, int w, int h, sf::Color c);

    int getFlockSize();
    Boid getBoid(int i);
    
    void addBoid(float x, float y);
    void flocking();

  private:
    std::vector<Boid> flock;
    Vector center;
    Vector avgVel;
    sf::Color color;

    int maxFlockSize = 15;
    int numBoids;

    Vector Boidpos;
};
