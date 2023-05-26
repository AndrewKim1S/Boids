#include "Application.h"


// Constructor
Application::Application() {

}

// Constructor
Application::Application(int width, int length) {
		// Create window
		window = new sf::RenderWindow(sf::VideoMode(width, length), "Flocking Simulation");
		window->setPosition(sf::Vector2i(300, 75));
		this->width = width;
		this->height = length;

		clock.restart();

		// create quadtree
		Rectangle rootShape;
		rootShape.center = sf::Vector2f(width/2, length/2);
		rootShape.size = sf::Vector2f(width, length);
		root = Quadtree(rootShape, 0);

		state = State::RUN;
		iteration = 0;

		// create boids
		createBoids();

		renderQuadtree = false;

		// Window movement
		zoom = 1;
		view = window->getDefaultView();
		dragging = false;
}

// Deconstructor
Application::~Application() {
		delete window;
}

// main run function to update, render, and poll events
void Application::run() {
		// check state of application
		switch(state) {
				case State::RUN:
						if(clock.getElapsedTime().asMilliseconds() > 50) {
								update();
								render();
								pollEvents();
								clock.restart();
						} else {
								return;
						}
						break;
				case State::FOLLOW:
						if(clock.getElapsedTime().asMilliseconds() > 50) {
								update();
								render();
								pollEvents();
								clock.restart();
						} else {
								return;
						}
						break;

				case State::PAUSE:
						pollEvents();
						break;
				default:
						break;
		}

		
}

// Draw all the boids and quadtree to the window
void Application::render() {

		window->clear(sf::Color(32, 32, 32));

		// draw quadtree
		if(renderQuadtree) {
				root.render(window);
		}
	
		// If we are following a boid, highlight it as well as its friends
		if(state == State::FOLLOW) {
				for(Boid& p : boids) {
						bool match = false;
						for(Boid& b : followNeighbors) {
								if(p.id == b.id) {
										p.highlight();
										sf::Vertex line[] = {
										sf::Vertex(p.position, sf::Color::White),
										sf::Vertex(following->position, sf::Color::White)
										};
										window->draw(line, 2, sf::Lines);
										match = true;
								}
						}
						if(!match){
								p.returnHighlight();
						}
				}
				following->renderVision(window);
				following->highlightSelected();
		}

		// render all boids
		for(Boid& b : boids) {
				b.render(window);
		}

		window->display();
}

// poll events from the user
void Application::pollEvents() {
		// check event 
		while(window->pollEvent(event)) {
				switch(event.type) {
						// close window 
						case sf::Event::Closed:
								window->close();
								break;
						case sf::Event::KeyPressed:
								// close window when escape
								if(event.key.code == sf::Keyboard::Escape) {
										window->close();
								}
								// toggle pause when P
								else if(event.key.code == sf::Keyboard::P) {
										if(state == State::PAUSE) {
												state = State::RUN;
										} 
										else {
												state = State::PAUSE;
										}
								}
								// toggle follow mode when F
								else if(event.key.code == sf::Keyboard::F) {
										if(state == State::FOLLOW) {
												for(Boid& b : boids) { b.returnHighlight(); }
												state = State::RUN;
										} 
										else if(state == State::PAUSE) {
												break;
										}
										// Set following boid 
										else {
												state = State::FOLLOW;
												following = &boids[0];
										}
								}
								// toggle visibility of quadtree when V
								else if(event.key.code == sf::Keyboard::V) {
										renderQuadtree = !renderQuadtree;
								}
						
						// Mouse Button events for screen movement
						case sf::Event::MouseButtonPressed:
								if(event.mouseButton.button == sf::Mouse::Left) {
										dragging = true;
										pos = window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x,
												event.mouseButton.y));
								}
								break;
						case sf::Event::MouseButtonReleased:
								if(event.mouseButton.button == sf::Mouse::Left) {
										dragging = false;
								}
								break;
						case sf::Event::MouseMoved:
								if(!dragging) {
										break;
								}
								newPos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, 
										event.mouseMove.y));
								delta = pos - newPos;

								view.setCenter(view.getCenter() + delta);
								window->setView(view);
								pos = window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x,
										event.mouseMove.y));
								break;
						// window zoom 
						case sf::Event::MouseWheelScrolled:
								if(event.mouseWheelScroll.delta <= -1) {
										zoom = std::min(2.f, zoom + 0.1f);
								} else if(event.mouseWheelScroll.delta >= 1) {
										zoom = std::min(0.5f, zoom - 0.1f);
								}
								view.setSize(window->getDefaultView().getSize());
								view.zoom(zoom);
								window->setView(view);
								break;
						default:
								break;
				}
		}
}

// update the application, quadtree & boids
void Application::update() {

		// clear the quadtree to just root
		root.clear();

		// insert boids into the quadtree
		for(Boid& b : boids) {
				root.insert(b);
		}
		
		// Update the boids
		for(size_t i = 0; i < boids.size(); i++) {
		
				std::vector<Boid> neighbors;
				Circle c;
				c.center = boids[i].position;
				c.radius = boids[i].getVisualRange();
	
				// Find all the neighboring boids
				root.queryBoids(c, neighbors, boids[i]);

				if(i == 0) {
						followNeighbors = neighbors;
				}

				// update all the boid positions
				boids[i].update(neighbors);
		}
		
}

// return the state of the window
bool Application::isRunning() {
		return window->isOpen();
}

// Create boids and place randomnly on screen
void Application::createBoids() {
		for(int i = 0; i < 50; i ++) {
				int x = rand() % width*0.75 + width*0.12;
				int y = rand() % height*0.75 + height*0.12;
				boids.emplace_back(Boid(x, y, i));
		}
}
