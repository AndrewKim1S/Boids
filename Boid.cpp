#include "Boid.h"

// Constructor
Boid::Boid() {

}

// Constructor
Boid::Boid(int x, int y, int id) {
		
		position.x = x;
		position.y = y;
		color = sf::Color(135, 197, 233);
		size = 5;
		visualRange = 120;
		speed = 6;
		
		// Create random initial velocity and acceleration
		velocity = sf::Vector2f(rand()%5-2, rand()%5-2);
		acceleration = sf::Vector2f(rand()%10-5, rand()%10-5);
		this->id = id;
}

// render the boid to the screen
void Boid::render(sf::RenderWindow* window) {
		
		// create shape
		sf::ConvexShape convex;
		convex.setPointCount(3);
		convex.setPoint(0, sf::Vector2f(0, -9));
		convex.setPoint(1, sf::Vector2f(-5, 5));
		convex.setPoint(2, sf::Vector2f(5, 5));
		convex.setFillColor(color);
		convex.setPosition(sf::Vector2f(position.x, position.y));
		convex.setRotation(atan2(velocity.x, -velocity.y) * 180 / 3.14);

		/*
		sf::CircleShape c;
		c.setFillColor(color);
		c.setPosition(sf::Vector2f(position.x-size, position.y-size));
		c.setRadius(size);
		*/
		window->draw(convex);
}

// render the vision field to the screen
void Boid::renderVision(sf::RenderWindow* window) {
		
		// create shape of the field of view
		sf::CircleShape c;
		c.setFillColor(sf::Color(100, 100, 100, 200));
		c.setPosition(sf::Vector2f(position.x-visualRange, position.y-visualRange));
		c.setRadius(visualRange);
		window->draw(c);
}

// update the boid position
void Boid::update(std::vector<Boid>& neighbors) {
		
		if(neighbors.size() > 0 ) {
	
				// Calculate the average position and velocity of neighbors
				sf::Vector2f averagePos;
				sf::Vector2f averageVel;
				for(Boid& b : neighbors) {
						averagePos.x += b.position.x;
						averagePos.y += b.position.y;
						averageVel.x += b.velocity.x;
						averageVel.y += b.velocity.y;
				}
				averagePos.x = averagePos.x / neighbors.size();
				averagePos.y = averagePos.y / neighbors.size();
				averageVel.x = averageVel.x / neighbors.size();
				averageVel.y = averageVel.y / neighbors.size();

				sf::Vector2f steer;
				
				// cohesion 
				steer = cohesion(averagePos);
				acceleration.x += steer.x * cohesionWeight;
				acceleration.y += steer.y * cohesionWeight;

				// alignment
				steer = alignment(averageVel);
				acceleration.x += steer.x * alignmentWeight;
				acceleration.y += steer.y * alignmentWeight;
				
				// seperation
				steer = seperation(averagePos);
				acceleration.x += steer.x * seperationWeight;
				acceleration.y += steer.y * seperationWeight;

		}
	
		// cap maximum accelration 
		acceleration.x = std::min(static_cast<int> (acceleration.x), 20);
		acceleration.y = std::min(static_cast<int> (acceleration.y), 20);

		// Move boid away from walls
		if(position.x < 0) {
				acceleration.x = 30;
		} else if(position.x < 100) {
				acceleration.x += 4;
		} 
		else if(position.x > 1500) {
				acceleration.x = -30;
		} else if(position.x > 1400) {
				acceleration.x += -4;
		}

		if(position.y < 0 ) {
				acceleration.y = 30;
		} else if(position.y < 80) {
				acceleration.y += 4;
		}
		else if(position.y > 900) {
				acceleration.y = -30;
		} else if(position.y > 820) {
				acceleration.y += -4;	
		}
		
		// add acceleration to velocity
		velocity.x += acceleration.x;
		velocity.y += acceleration.y;
		velocity = normalize(velocity);

		// update position
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;

}

// Cohesion - Move towards average position of neighbors
sf::Vector2f Boid::cohesion(sf::Vector2f& averagePos) {
		sf::Vector2f steering;

		steering.x = averagePos.x - position.x;
		steering.y = averagePos.y - position.y;

		steering = normalize(steering);

		steering.x *= speed;
		steering.y *= speed;

		steering.x -= velocity.x;
		steering.y -= velocity.y;
		return steering;
}

// Alignment - Change heading to average heading of neighbors
sf::Vector2f Boid::alignment(sf::Vector2f& averageVel) {
		sf::Vector2f result;

		result.x = averageVel.x;
		result.y = averageVel.y;

		result = normalize(result);

		result.x *= speed;
		result.y *= speed;

		result.x -= velocity.x;
		result.y -= velocity.y;
		
		return result;
}

// Seperation - Move away from average position of neighbors
sf::Vector2f Boid::seperation(sf::Vector2f& averagePos) {
		sf::Vector2f steering;

		steering.x = averagePos.x - position.x;
		steering.y = averagePos.y - position.y;
		steering.x *= -1;
		steering.y *= -1;

		steering = normalize(steering);

		steering.x *= speed;
		steering.y *= speed;

		steering.x -= velocity.x;
		steering.y -= velocity.y;
		
		return steering;
}

// vector normalization
sf::Vector2f Boid::normalize(sf::Vector2f& v) {
		float length = sqrt(v.x * v.x + v.y * v.y);
		return sf::Vector2f(v.x / length, v.y / length);
}

int Boid::getVisualRange() {
		return visualRange;
}

void Boid::highlight() {
		color = sf::Color::Red;
}

void Boid::highlightSelected() {
		color = sf::Color::Green;
}

void Boid::returnHighlight() {
		color = sf::Color(135, 197, 233);
}

bool Boid::equals(Boid b) {
		if(b.id == id) {
				return true;
		}
		return false;
}
