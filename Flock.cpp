#include "Flock.h"


// Constructor 
Flock::Flock(){
  numBoids = 0; 
}

Flock::Flock(int boids, int w, int h, sf::Color c){
  std::cout << "Flock Created: " << boids <<
    " boids" << std::endl;
  numBoids = 0;
  color = c;
  for(int i = 0; i < boids; i++){
    addBoid(rand() % (w/2) + w/4,
      rand() % (h/2) + h/4);
  }
}

// Accessor for flock size
int Flock::getFlockSize(){
  return flock.size();
}

// Accessor for Boid
Boid Flock::getBoid(int i){
  return flock[i];
}

// Add a Boid
void Flock::addBoid(float x, float y){
  if(numBoids >= maxFlockSize){
    // std::cout << "Max Boid Limit Reached! " 
    // << numBoids << std::endl;
    return;
  }
  numBoids ++;
  Boid b = Boid(x, y, color);

  // This is Testing Purposes only, later implementation will selected using mouse location
  if(numBoids == 3){
    b.setSelected(true);
  }
  flock.push_back(b);

}

// Have all boid run through flocking behavior
void Flock::flocking(){
  for(size_t i = 0; i < flock.size(); i++){
    // We need to find all the boids within its visual range
    Boidpos = flock[i].getPos(); 
    std::vector<Boid> withinRange;
    for(size_t k = 0; k < flock.size(); k++){
      // std::cout << "looping " << 
      if(flock[k].getPos().isWithin(Boidpos, 110)){
        withinRange.push_back(flock[k]);
      }
    }

    // Find center of flocks within range
    center.x = 0;
    center.y = 0;
    avgVel.x = 0;
    avgVel.y = 0;
    for(Boid b : withinRange){
      center + b.getPos();
    }
    // This is the average position. Used in cohesion
    center.scalarDiv(withinRange.size());

    // Rule 1 for Boid is called
    flock[i].cohesion(center);

    flock[i].run();
  }
}

