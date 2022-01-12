#include "logging/logging.h"
#include "graphics/window.h"

#include <iostream>

int main(int argc, char* argv[])
{
	using namespace novazero;
	using namespace graphics;
	using namespace logging;

	LOG("Starting...");

	Window win("Game Window");

	bool running = true;
	while (running) {

		// Handle Events
		SDL_Event event;
		SDL_PollEvent(&event);
		
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;
			break;
		}
		
		// Update

		// Render

		// Clean up

	}

	return 0;
}