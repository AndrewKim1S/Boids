#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class Vector{

  public:
    // Constructor
    Vector();
    Vector(float x, float y);

    void setVector(float x, float y);
    
    Vector operator+ (Vector const &obj);
    Vector operator- (Vector const &obj);
    Vector operator* (Vector const &obj);
    Vector operator/ (Vector const &obj);

    void scalarAdd(float x);
    void scalarSub(float x);
    void scalarMult(float x);
    void scalarDiv(float x);

    float getMagnitude();
    void normalize();
    std::string to_string();
    float dotProduct(Vector const &obj);
    float distance(Vector const &obj);
    float angle(Vector const &obj);
    bool isWithin(Vector pos, double r);
    bool equals(Vector v);

    float x;
    float y;

};
