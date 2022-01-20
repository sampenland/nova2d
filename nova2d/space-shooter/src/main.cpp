#include "core/Game.h"

#include "scenes/MainMenu.h"
#include "scenes/GamePlay.h"

#include "Player.h"
#include "enemies/Leader.h"

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

	n2dAddColor("background", "201533", 1);
	n2dAddColor("purple", "252446", 1);
	n2dAddColor("dark-blue", "203562", 1);
	n2dAddColor("blue", "1e579c", 1);
	n2dAddColor("light-blue", "0098db", 1);
	n2dAddColor("bright-blue", "0ce6f2", 1);
	n2dAddColor("white", "ffffff", 1);
	
	n2dSetBackgroundColor("background");
	
	n2dAssetsLoadAndAddTexture("player", "res/ship_01_anim.png");
	n2dAssetsLoadAndAddTexture("leader", "res/ship_02.png");
	n2dAssetsLoadAndAddTexture("pawn", "res/ship_03.png");
	n2dAssetsLoadAndAddTexture("player-bullet", "res/bullet_01.png");
	n2dAssetsLoadAndAddTexture("pawn-bullet", "res/bullet_02.png");
	n2dAssetsLoadAndAddTexture("leader-bullet", "res/bullet_03.png");
	n2dAssetsLoadAndAddTexture("title", "res/title.png");

	MainMenu* mainMenuScene = new MainMenu();
	GamePlay* gamePlayScene = new GamePlay();

	n2dGameAddScene("mainMenu", mainMenuScene);
	n2dGameAddScene("game", gamePlayScene);
	
	n2dGameConfigFirstScene("mainMenu");

	while (game.IsRunning())
	{
		game.Tick();
	}

	return 0;
}