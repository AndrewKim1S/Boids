#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Boid.h"
#include "Quadtree.h"

#include <vector>
#include <cassert>

class Application {

		// application states
		enum State {
				RUN,
				PAUSE,
				FOLLOW
		};

		public:
				Application();
				Application(int width, int length);
				~Application();
				void run();
				void render();
				void pollEvents();
				void update();
				bool isRunning();
				
				void createBoids();

		private:
				sf::RenderWindow* window;
				sf::Event event;
				sf::Clock clock;

				// For testing purposes
				// sf::Clock clockTest;

				int width;
				int height;

				std::vector<Boid> boids;

				Boid* following;
				std::vector<Boid> followNeighbors;

				Quadtree root;
				State state;

				// const int timeStep = 25;

				int iteration;

				bool renderQuadtree;

};
