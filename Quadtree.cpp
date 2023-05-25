#include "Quadtree.h"

// Constructor
Quadtree::Quadtree() {}

// Constructor
Quadtree::Quadtree(Rectangle s, int l) {
		this->shape.center = s.center;
		this->shape.size = s.size;
		this->level = l;
		topLeft = NULL;
		topRight = NULL;
		botLeft = NULL;
		botRight = NULL;

		rectangle.setSize(s.size);
		rectangle.setPosition(s.center.x - (0.5 * (s.size.x)),
				s.center.y - (0.5 * (s.size.y)));
		rectangle.setFillColor(sf::Color(32, 32, 32));
		rectangle.setOutlineThickness(2);
		rectangle.setOutlineColor(sf::Color::White);

}

// Deconstructor
Quadtree::~Quadtree() {
		delete topLeft;
		delete topRight;
		delete botLeft;
		delete botRight;
}

void Quadtree::insert(Boid& b) {
	
		// Check that the boid is within the quadtree boundaries
		if(b.position.x <= (shape.center.x - (0.5 * (shape.size.x))) ||
				b.position.x >= shape.center.x + (0.5 * (shape.size.x)) ||
				b.position.y <= shape.center.y - (0.5 * (shape.size.y)) ||
				b.position.y >= shape.center.y + (0.5 * (shape.size.y))) {
				return;
		}
		
		// Checking if the quadtree is a leaf
		if(level == MaxLevel) {
				boids.push_back(b);
				return;
		}

		// Checking if there is still space 
		else if(boids.size() < BoidThreshold && topLeft == NULL) {
				boids.push_back(b);
				return;
		}

		// Middle valus of the quadtree
		float verticalMid = shape.center.x;
		float horizontalMid = shape.center.y;

		// Create Quadtree sub-sections
		if(topLeft == NULL && topRight == NULL && botLeft == NULL && botRight == NULL) {
				
				Rectangle rtl;
				rtl.center = sf::Vector2f(verticalMid - (0.25 * (shape.size.x)), 
						horizontalMid - (0.25 * (shape.size.y)));
				rtl.size = sf::Vector2f(0.5 * (shape.size.x), 0.5 * (shape.size.y));
				topLeft = new Quadtree(rtl, level+1);
				
				Rectangle rtr;
				rtr.center = sf::Vector2f(verticalMid + (0.25 * (shape.size.x)),
						horizontalMid - (0.25 * (shape.size.y)));
				rtr.size = sf::Vector2f(0.5 * (shape.size.x), 0.5 * (shape.size.y));
				topRight = new Quadtree(rtr, level+1);
				
				Rectangle rbl;
				rbl.center = sf::Vector2f(verticalMid - (0.25 * (shape.size.x)),
						horizontalMid + (0.25 * (shape.size.y)));
				rbl.size = sf::Vector2f(0.5 * (shape.size.x), 0.5 * (shape.size.y));
				botLeft = new Quadtree(rbl, level+1);
				
				Rectangle rbr;
				rbr.center = sf::Vector2f(verticalMid + (0.25 * (shape.size.x)),
						horizontalMid + (0.25 * (shape.size.y)));
				rbr.size = sf::Vector2f(0.5 * (shape.size.x), 0.5 * (shape.size.y));
				botRight = new Quadtree(rbr, level+1);
				
				// Add all of the boids stored in this level to it's children
				boids.push_back(b);
				for(size_t i = 0; i < boids.size(); i++) {
						// Boid is left 
						if(verticalMid >= boids[i].position.x) {
								if(horizontalMid >= boids[i].position.y) {
										topLeft->insert(boids[i]);
								}
								else {
										botLeft->insert(boids[i]);
								}
						}
						// Boid is right
						else {
								if(horizontalMid >= boids[i].position.y) {
										topRight->insert(boids[i]);
								}
								else {
										botRight->insert(boids[i]);
								}
						}
				}
				
				// Remove all boids on the current level
				boids.clear();
				return;
		}

		// Boid is left 
		if(verticalMid >= b.position.x) {
				if(horizontalMid >= b.position.y) {
						topLeft->insert(b);
				}
				else {
						botLeft->insert(b);
				}
		}
		// Boid is right
		else {
				if(horizontalMid >= b.position.y) {
						topRight->insert(b);
				}
				else {
						botRight->insert(b);
				}
		}
		
}

// Clear the quadtree recursively
void Quadtree::clear() {
		if(topLeft != NULL) {
				topLeft->clear();
		}
		if(topRight != NULL) {
				topRight->clear();
		}
		if(botLeft != NULL) {
				botLeft->clear();
		}
		if(botRight != NULL) {
				botRight->clear();
		}
		topLeft = NULL;
		topRight = NULL;
		botLeft = NULL;
		botRight = NULL;

		boids.clear();
}

// Render the quadtree recursively
void Quadtree::render(sf::RenderWindow* target) {
		target->draw(rectangle);
		if(topLeft != NULL) {
				topLeft->render(target);
		}
		if(topRight != NULL) {
				topRight->render(target);
		}
		if(botLeft != NULL) {
				botLeft->render(target);
		}
		if(botRight != NULL) {
				botRight->render(target);
		}
}

// Query through the quadtree and find neighbors
// https://yal.cc/rectangle-circle-intersection-test/
void Quadtree::queryBoids(Circle& c, std::vector<Boid>& neighbors, Boid& b) {
		// Check that c overlaps with quadtree boundaries
		float Rectx = shape.center.x - (0.5 * shape.size.x);
		float Recty = shape.center.y - (0.5 * shape.size.y);

		float deltaX = c.center.x - 
				std::max(Rectx, std::min(c.center.x, Rectx + shape.size.x));
		float deltaY = c.center.y -
				std::max(Recty, std::min(c.center.y, Recty + shape.size.y));

		// If boundaries do not intersect return
		if((deltaX * deltaX + deltaY * deltaY) > (c.radius * c.radius)) {
				return;
		}

		// If the quadtree is a leaf check through boids
		if(topLeft == NULL) {
				for(size_t i = 0; i < boids.size(); i++) {
						float x = fabs(c.center.x - boids[i].position.x);
						float y = fabs(c.center.y - boids[i].position.y);
						// If the boid is within the range add to neighbors
						if((x * x + y * y) < c.radius * c.radius && !boids[i].equals(b)) {
								neighbors.push_back(boids[i]);
						}
				}
				return;
		} 
		// Else go deeper into tree
		else {
				topLeft->queryBoids(c, neighbors, b);
				topRight->queryBoids(c, neighbors, b);
				botLeft->queryBoids(c, neighbors, b);
				botRight->queryBoids(c, neighbors, b);
		}

}

void Quadtree::printQuadtree() {
		std::cout << "level: " << level << ", " << boids.size() << std::endl;
		if(topLeft != NULL) {
				std::cout << "top left, ";
				topLeft->printQuadtree();
		}
		if(topRight != NULL) {
				std::cout << "top right, ";
				topRight->printQuadtree();
		}
		if(botLeft != NULL) {
				std::cout << "bot left, ";
				botLeft->printQuadtree();
		}
		if(botRight != NULL) {
				std::cout << "bot right, ";
				botRight->printQuadtree();
		}
}
