#include "Boid.h"


// Constructor
Boid::Boid(){
  position = Vector(0, 0);
  velocity = Vector(0, 0);
  acceleration = Vector(0, 0);

  seperationWeight = 1.0;
  alignmentWeight = 1.0;
  cohesionWeight = 1.0;

  selected = false;
}

Boid::Boid(float x, float y, sf::Color c){
  position = Vector(x, y);
  velocity = Vector(0, 0);
  acceleration = Vector(0, 0);
  color = c;

  // Default weights of Boids algorithm
  seperationWeight = 1.0;
  alignmentWeight = 1.0;
  cohesionWeight = 1.0;

  // Visual Bubble
  visualRange.setRadius(visual);
  visualRange.setPosition(position.x - visual,
    position.y - visual + 0.5*lengthShape);
  visualRange.setFillColor(sf::Color(120, 120, 120, 70));

  // Create Boid triangle shape
  shape.setPointCount(3);
  shape.setPoint(0, sf::Vector2f(0,0));
  shape.setPoint(1, sf::Vector2f(widthShape, lengthShape));
  shape.setPoint(2, sf::Vector2f(-widthShape, lengthShape));
  shape.setFillColor(c);
  shape.setOutlineColor(sf::Color(201,255,229));
  shape.setOutlineThickness(1);
  shape.setPosition(position.x, position.y);

  selected = false;
}

Boid::~Boid(){}


// Run function
void Boid::run(){
  // First Find all of the Boids within its visual range
  velocity = velocity + v1 + v2 + v3;
  position = position + velocity;
  shape.move(velocity.x, velocity.y);
  visualRange.move(velocity.x , velocity.y);
}

void Boid::render(sf::RenderTarget& window){
  window.draw(shape);
  if(selected) { window.draw(visualRange); }
}

// Boid Laws 
void Boid::seperation(){

}

void Boid::alignment(){

}

void Boid::cohesion(Vector center){
  if(!center.equals(position)){
    v1 = (center - position);
    v1.scalarDiv(100);
  }
}


// Accessors & Mutators
Vector Boid::getPos(){
  return position;
}

void Boid::setSelected(bool b){
  selected = b;
}
