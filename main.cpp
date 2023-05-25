#include "Application.h"
#include <iostream>

int main() {
		srand(static_cast<unsigned>(time(0)));

		// Create application
		Application simulation = Application(1500, 900);

		// Continue running application until it is closed
		while(simulation.isRunning()) {
				simulation.run();
		}

		return 0;
}
