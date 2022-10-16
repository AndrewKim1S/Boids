#include "Boid.h"


// Constructor
Boid::Boid(){
  position = Vector(0, 0);
  velocity = Vector(0, 0);
  acceleration = Vector(0, 0);
}

Boid::Boid(float x, float y){
  position(x, y);
  velocity(0, 0);
  acceleration(0, 0);
}


// Boid Laws 
Vector Boid::seperation(){

}

Vector Boid::alignment(){

}

Vector Boid::acceleration(){

}
