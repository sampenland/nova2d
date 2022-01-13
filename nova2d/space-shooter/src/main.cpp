#include "logging/logging.h"
#include "graphics/window.h"
#include "core/Game.h"
#include "maths/Vec2.h"
#include "graphics/Sprite.h"

int main(int argc, char* argv[])
{
	using namespace novazero;
	using namespace graphics;
	using namespace logging;
	using namespace core;
	using namespace maths;

	LOG("Nova Boot v.0.1 : Game Engine started.");

	Game game(Vec2(800, 640), "Space Shooter");
	Sprite player(0, 0, "res/ship_01.png");

	Color blue = game.s_ColorManager->GetColor("blue");

	while (game.IsRunning())
	{
		game.Update();
		player.Update();
		player.Draw();
	}

	return 0;
}