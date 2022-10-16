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
    std::cout << "How Many Times " << i << std::endl;
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
    std::cout << "Max Boid Limit Reached! " << numBoids << std::endl;
    return;
  }
  numBoids ++;
  Boid b = Boid(x, y, color);
  std::cout << "Num Boids: " << numBoids << std::endl;
  flock.push_back(b);
}

// Have all boid run through flocking behavior
void Flock::flocking(){
  for(size_t i = 0; i < flock.size(); i++){
    flock[i].run();
  }
}
