#include "logging/logging.h"
#include "graphics/window.h"
#include "maths/Vec2.h"
#include "core/Game.h"
#include "Player.h"
#include "Leader.h"

int main(int argc, char* argv[])
{
	using namespace novazero;
	using namespace graphics;
	using namespace logging;
	using namespace core;
	using namespace maths;
	using namespace controllers;
	using namespace spaceshooter;

	LOG("Nova Boot v.0.1 : Game Engine started.");

	Game game(Vec2(800, 640), "Space Shooter");
	Game::SetGamePadding(32);

	game.s_ColorManager->AddColor("background", "201533", 1);
	game.s_ColorManager->AddColor("purple", "252446", 1);
	game.s_ColorManager->AddColor("dark-blue", "203562", 1);
	game.s_ColorManager->AddColor("blue", "1e579c", 1);
	game.s_ColorManager->AddColor("light-blue", "0098db", 1);
	game.s_ColorManager->AddColor("bright-blue", "0ce6f2", 1);
	game.s_ColorManager->AddColor("white", "ffffff", 1);
	game.s_Renderer->SetBackgroundColor(game.s_ColorManager->GetColor("background"));

	game.s_AssetManager->LoadAndAddTexture("player", "res/ship_01.png");
	game.s_AssetManager->LoadAndAddTexture("leader", "res/ship_02.png");
	game.s_AssetManager->LoadAndAddTexture("pawn", "res/ship_03.png");
	game.s_AssetManager->LoadAndAddTexture("player-bullet", "res/bullet_01.png");

	Player player("player", Vec2Int((int)Game::s_Width / 2 - 8, (int)Game::s_Height - 64), Vec2Int(16, 16), 0);
	player.Configure(1);
	player.ConfigureMove(3);
	player.SetMoveBounds(Game::GetGameBounds());

	Leader enemy("leader", Vec2Int((int)Game::s_Width / 2 - 8, 48), Vec2Int(16, 16), 0);
	enemy.SetAliveBounds(Game::GetGameBounds());

	while (game.IsRunning())
	{
		game.Tick();
	}

	return 0;
}