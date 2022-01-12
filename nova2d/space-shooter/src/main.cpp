#include "logging/logging.h"
#include "graphics/window.h"
#include "core/Game.h"
#include "maths/Vec2.h"

int main(int argc, char* argv[])
{
	using namespace novazero;
	using namespace graphics;
	using namespace logging;
	using namespace core;
	using namespace maths;

	LOG("Nova Boot v.0.1 : Game Engine started.");

	Game game(Vec2(800, 640), "Space Shooter");

	while (game.IsRunning())
	{
		game.Update();
	}

	return 0;
}