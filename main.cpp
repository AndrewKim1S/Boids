#include <iostream>
#include "simulation.h"
#include "Vector.h"

int main (int argc, char** argv){
  simulation sim(1500, 1200);

  while(sim.isClosed()){
    sim.run();
  }

  Vector v1 = Vector(3,4);
  Vector v2 = Vector(5,7);
  std::cout << v1.dotProduct(v2) << std::endl;

  return 0;
}
