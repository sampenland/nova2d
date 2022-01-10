#include <iostream>

#include "SDL.h"
#include "logging/logging.h"
#include "graphics/window.h"


int main(int argc, char* argv[])
{
	using namespace novazero;
	using namespace logging;
	using namespace graphics;

	LOG("Starting...");

	Window win("Game");

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