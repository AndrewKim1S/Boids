#include <iostream>

#include "simulation.h"
#include "Vector.h"

int main (int argc, char** argv){
  srand(static_cast<unsigned>(time(0)));

  simulation sim(1500, 1200);

  while(sim.isClosed()){
    sim.run();
  }

  return 0;
}
