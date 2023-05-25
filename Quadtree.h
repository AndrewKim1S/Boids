#pragma once


#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Boid.h"
#include "math.h"


// Rectangle Definition
struct Rectangle {
		sf::Vector2f center;
		sf::Vector2f size;
};

// Circle Definition
struct Circle {
		sf::Vector2f center;
		int radius;
};

// constants for quadtree
const int MaxLevel = 5;
const int BoidThreshold = 4;


class Quadtree {

		public:
				Quadtree();
				Quadtree(Rectangle s, int l);
				~Quadtree();

				void insert(Boid& b);
				void clear();
				void render(sf::RenderWindow* target);
				void queryBoids(Circle& c, std::vector<Boid>& neighbors, Boid& b);

				// For testing 
				void printQuadtree();

		private:
				// Children nodes of the quadtree node
				Quadtree* topLeft;
				Quadtree* topRight;
				Quadtree* botLeft;
				Quadtree* botRight;

				std::vector<Boid> boids;

				Rectangle shape;
				sf::RectangleShape rectangle;

				int level;
};
