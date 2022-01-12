#include "logging/logging.h"
#include "graphics/window.h"
#include "core/Game.h"
#include "maths/Vec2.h"

#include <iostream>

int main(int argc, char* argv[])
{
	using namespace novazero;
	using namespace graphics;
	using namespace logging;
	using namespace core;
	using namespace maths;

	LOG("Starting...");

	Game game(vec2(800, 640), "Space Shooter");

	while (true)
	{
		game.Update();
	}

	return 0;
}