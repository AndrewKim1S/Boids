#pragma once

#include "Boid.h"
#include <vector>


class Flock{

  public:
    Flock();
    int getFlockSize();
    Boid getBoid(int i);
    void addBoid(Boid& b);
    void flocking();

  private:
    std::vector<Boid> flock;

};
