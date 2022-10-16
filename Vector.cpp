#include "Vector.h"

// Constructors
Vector::Vector(){
  x = 0;
  y = 0;
}

Vector::Vector(float x, float y){
  this->x = x;
  this->y = y;
}

// Accessors and Mutators
void Vector::setVector(float x, float y){
  this->x = x;
  this->y = y;
}

float Vector::getMagnitude(){
  return sqrt(x*x + y*y);
}

// Operator functions
Vector Vector::operator+ (Vector const &obj){
  return Vector(this->x + obj.x, this->y + obj.y);
}

Vector Vector::operator- (Vector const &obj){
  return Vector(this->x - obj.x, this->y - obj.y);
}

Vector Vector::operator* (Vector const &obj){
  return Vector(this->x * obj.x, this->y * obj.y);
}

Vector Vector::operator/ (Vector const &obj){
  return Vector(this->x / obj.x, this->y / obj.y);
}

// Scalar functions
void Vector::scalarAdd(float x){
  this->x = this->x + x;
  this->y = this->y + x;
}

void Vector::scalarSub(float x){
  this->x = this->x - x;
  this->y = this->y - x;
}

void Vector::scalarMult(float x){
  this->x *= x;
  this->y *= x;
}

void Vector::scalarDiv(float x){
  this->x = this->x / x;
  this->y = this->y / x;
}

// Normalize
void Vector::normalize(){
  float mag = getMagnitude();
  if(mag > 0){
    this->x = this->x/mag;
    this->y = this->y/mag;
  }
}

// to String functioin
std::string Vector::to_string(){
  std::string result = "x: " + std::to_string(this->x);
  result += " y: " + std::to_string(this->y);
  return result;
}

// Dot product
float Vector::dotProduct(Vector const &obj){
  return (this->x * obj.x) + (this->y * obj.y);
}
