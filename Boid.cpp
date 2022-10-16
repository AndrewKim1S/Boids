#include "Boid.h"


// Constructor
Boid::Boid(){
  position = Vector(0, 0);
  velocity = Vector(0, 0);
  acceleration = Vector(0, 0);
}

Boid::Boid(float x, float y, sf::Color c){
  position = Vector(x, y);
  velocity = Vector(0, 0);
  acceleration = Vector(0, 0);
  color = c;
}

Boid::~Boid(){}


// Run function
void Boid::run(){
  
}

void Boid::flock(){

}

// Boid Laws 
Vector Boid::seperation(){

}

Vector Boid::alignment(){

}

Vector Boid::cohesion(){

}
