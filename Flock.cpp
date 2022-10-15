#include "Flock.h"


// Constructor 
Flock::Flock(){
  
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
void Flock::addBoid(Boid& b){
  flock.push_back(b);
}

// Have all boid run through flocking behavior
void Flock::flocking(){
  for(int i = 0; i < flock.size(); i++){
    flock[i].run(flock);
  }
}
