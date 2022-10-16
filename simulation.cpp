#include "simulation.h"

// Constructor
simulation::simulation(int w, int h){
  // Window settings 
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  this->width = w;
  this->height = h;

  window = new sf::RenderWindow(sf::VideoMode(width, height, 
    desktop.bitsPerPixel), "Boids Simulation");    
  window->setFramerateLimit(60);
  window->setVerticalSyncEnabled(false);
  window->setPosition(sf::Vector2i(200, 200));
  state = State::MENU;

  // Font settings
  font.loadFromFile("arial.ttf");
  
  // Text settings
  title.setFont(font);
  title.setFillColor(sf::Color::White);
  title.setCharacterSize(80);
  title.setPosition(width/3.15, height/2.5);
  title.setString("Boids Simulation");

  menuInfo.setFont(font);
  menuInfo.setFillColor(sf::Color::White);
  menuInfo.setCharacterSize(30);
  menuInfo.setPosition(width/3, height/2);
  menuInfo.setString("Type number of flocks [1-3] &\n Press enter to continue");
  
  simState.setFont(font);
  simState.setFillColor(sf::Color::White);
  simState.setCharacterSize(16);
  simState.setPosition(width/100, height/100);

  // Text input settings
  menuInput = TextInput(1);
  menuInput.setPosition(width/2.2, height/1.7);
  menuTextEntry.setFont(font);
  menuTextEntry.setFillColor(sf::Color::Black);
  menuTextEntry.setCharacterSize(24);
  menuTextEntry.setPosition(width/2.2+5, height/1.69+5);
  menuTextEntry.setString("");
}

// Deconstructor
simulation::~simulation(){
  delete window;
}

// Accessor window state
bool simulation::isClosed(){
  return window->isOpen();
}

// Run function
void simulation::run(){
  switch(state){
    case State::RUN:
      pollEvents();
      update();
      render();
      break;
    case State::PAUSE:
      pollEvents();
      render();
      break;
    case State::MENU:
      pollEvents();
      displayMenu();
      break;
    default: 
      break;
  }
}

// Poll Events from keyboard to mouse
void simulation::pollEvents(){
  while(window->pollEvent(ev)){
    switch(ev.type){
      case sf::Event::Closed:
        window->close();
        break;
      case sf::Event::KeyPressed:
        if(ev.key.code == sf::Keyboard::Escape){
          window->close();
        }
        else if(ev.key.code == sf::Keyboard::A){
          addBoidToFlock(1);
        }
        else if(ev.key.code == sf::Keyboard::Space){
          if(state == State::PAUSE){
            state = State::RUN;
            simState.setString("Running");
          } else {
            state = State::PAUSE;
            simState.setString("Pause");
          }
        }
        break;
      default:
        break;
    }
  }
}

// Update Game State
void simulation::update(){

}

// Render Simulation Elements
void simulation::render(){
  window->clear(sf::Color::Black);

  window->draw(simState);
  window->display();
}

// Create Flock
void simulation::createFlock(){
  Flock f = Flock(rand() % 5 + 1, width, height,
   sf::Color(rand() % 255, rand() % 255, rand() % 255));
  flocks.push_back(f);
}

// Add Boid to Flock
void simulation::addBoidToFlock(int f){
  float randX = rand() % (width/2) + (width/4);
  float randY = rand() % (height/2) + (height/4);
  std::cout << "keyboard add" << std::endl;
  flocks[0].addBoid(randX, randY);
}

// Display Menu
void simulation::displayMenu(){
  window->clear(sf::Color::Black);
  window->draw(title);
  window->draw(menuInfo);
  
  std::string input = menuInput.getString();

  menuTextEntry.setString(input);
  window->draw(menuInput.getShape());
  window->draw(menuTextEntry);
  window->display();

  while(window->pollEvent(ev)){
    if(ev.type == sf::Event::Closed || 
      ev.key.code == sf::Keyboard::Escape){
      window->close();
    }
    else if(ev.key.code == sf::Keyboard::Enter && input.size() > 0){
      numFlocks = std::stoi(input);
      state = State::RUN;
      simState.setString("Running");
      for(int i = 0; i < numFlocks; i++){
        createFlock();
      }
      break;
    } else if(ev.type == sf::Event::MouseButtonReleased){
      auto pos = sf::Mouse::getPosition(*window);
      menuInput.setFocus(false);
      if(menuInput.contains(sf::Vector2f(pos))){
        menuInput.setFocus(true);
      }
    } else {
      menuInput.handleInput(ev);
    }
  }
}
