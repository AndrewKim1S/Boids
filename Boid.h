#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

// Weights 
const double cohesionWeight = 1.6;
const double alignmentWeight = 1.2;
const double seperationWeight = 2.0;

class Boid {
		
		public:
				sf::Vector2f position;
				sf::Vector2f velocity;
				sf::Vector2f acceleration;
				std::vector<Boid> n;

				sf::Color color;
				int id;

				Boid();
				Boid(int x, int y, int id);
				void render(sf::RenderWindow* window);
				void renderVision(sf::RenderWindow* window);
				void update(std::vector<Boid>& neighbors);
				sf::Vector2f cohesion(sf::Vector2f& averagePos);
				sf::Vector2f alignment(sf::Vector2f& averageVel);
				sf::Vector2f seperation(sf::Vector2f& averagePos);
				sf::Vector2f normalize(sf::Vector2f& v);

				int getVisualRange();
				void highlight();
				void highlightSelected();
				void returnHighlight();
				bool equals(Boid b);

		private:
				int size;
				int speed;
				int visualRange;
};
