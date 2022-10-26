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

// distance between two vectors
float Vector::distance(Vector const &obj){
  float xdist = this->x - obj.x;
  float ydist = this->y - obj.y;
  return sqrt(xdist*xdist + ydist*ydist);
}

// angle between two vectors
float Vector::angle(Vector const &obj){
  if(this->x == 0 && this->y == 0){
    return 0.0;
  } if( obj.x == 0 && obj.y == 0){
    return 0.0;
  }

  double dot = dotProduct(obj);
  double v1mag = sqrt(x*x + y*y);
  double v2mag = sqrt(obj.x*obj.x + obj.y*obj.y);
  double angle = dot/(v1mag*v2mag);

  if(angle <= -1){
    return 3.1415;
  } else if(angle >= 1){
    return 0.0;
  }
  return acos(angle);
}

bool Vector::isWithin(Vector pos, double r){
  double length = (x - pos.x) * (x - pos.x) + (y - pos.y) * (y - pos.y);
  length = sqrt(length);
  return length < r;
}

bool Vector::equals(Vector v){
  if(v.x == x && v.y == y){ return true; }
  return false;
}
