#include "logging/logging.h"
#include "graphics/window.h"
#include "core/Game.h"
#include "Player.h"
#include "enemies/Leader.h"

#include "scenes/MainMenu.h"
#include "scenes/GamePlay.h"

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

	Game game(Vec2Int(800, 640), "Space Shooter");
	game.ConfigureIcon("res/ship_01.png");
	Game::SetGamePadding(32);

	game.s_ColorManager->AddColor("background", "201533", 1);
	game.s_ColorManager->AddColor("purple", "252446", 1);
	game.s_ColorManager->AddColor("dark-blue", "203562", 1);
	game.s_ColorManager->AddColor("blue", "1e579c", 1);
	game.s_ColorManager->AddColor("light-blue", "0098db", 1);
	game.s_ColorManager->AddColor("bright-blue", "0ce6f2", 1);
	game.s_ColorManager->AddColor("white", "ffffff", 1);
	game.s_Renderer->SetBackgroundColor(game.s_ColorManager->GetColor("background"));

	game.s_AssetManager->LoadAndAddTexture("player", "res/ship_01_anim.png");
	game.s_AssetManager->LoadAndAddTexture("leader", "res/ship_02.png");
	game.s_AssetManager->LoadAndAddTexture("pawn", "res/ship_03.png");
	game.s_AssetManager->LoadAndAddTexture("player-bullet", "res/bullet_01.png");
	game.s_AssetManager->LoadAndAddTexture("pawn-bullet", "res/bullet_02.png");
	game.s_AssetManager->LoadAndAddTexture("leader-bullet", "res/bullet_03.png");
	game.s_AssetManager->LoadAndAddTexture("title", "res/title.png");

	MainMenu* mainMenuScene = new MainMenu();
	GamePlay* gamePlayScene = new GamePlay();

	game.s_SceneManager->AddScene("mainMenu", mainMenuScene);
	game.s_SceneManager->AddScene("game", gamePlayScene);
	
	game.ConfigureFirstScene("mainMenu");

	while (game.IsRunning())
	{
		game.Tick();
	}

	return 0;
}