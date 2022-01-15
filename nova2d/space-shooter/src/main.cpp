#include "logging/logging.h"
#include "graphics/window.h"
#include "maths/Vec2.h"
#include "core/Game.h"
#include "controllers/UDRLController.h"

int main(int argc, char* argv[])
{
	using namespace novazero;
	using namespace graphics;
	using namespace logging;
	using namespace core;
	using namespace maths;
	using namespace controllers;

	LOG("Nova Boot v.0.1 : Game Engine started.");

	Game game(Vec2(800, 640), "Space Shooter");
	game.s_ColorManager->AddColor("background", "201533", 1);
	game.s_ColorManager->AddColor("purple", "252446", 1);
	game.s_ColorManager->AddColor("dark-blue", "203562", 1);
	game.s_ColorManager->AddColor("blue", "1e579c", 1);
	game.s_ColorManager->AddColor("light-blue", "0098db", 1);
	game.s_ColorManager->AddColor("bright-blue", "0ce6f2", 1);
	game.s_ColorManager->AddColor("white", "ffffff", 1);
	game.s_Renderer->SetBackgroundColor(game.s_ColorManager->GetColor("background"));

	UDRLController player("res/ship_01.png", Vec2(0, 0), Vec2(16, 16), 0);
	player.ConfigureMove(2, Rect(16, Game::s_Height - 64, Game::s_Width - 32, 64));

	while (game.IsRunning())
	{
		game.Tick();
	}

	return 0;
}