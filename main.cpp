#include <iostream>
#include "simulation.h"

int main (int argc, char** argv){
  simulation sim(1500, 1200);

  while(sim.isClosed()){
    sim.run();
  }

  return 0;
}
