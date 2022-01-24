#include "core/Game.h"

#include "scenes/MainMenu.h"
#include "scenes/Lvl1.h"
#include "scenes/GameOver.h"

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
	game.ConfigureSQL("spaceshooter", "tcp://127.0.0.1:3306", "root", "sqlpassword", true);
	Game::SetGamePadding(32);

	n2dAddColor("background", "201533", 1);
	n2dAddColor("red", "f02b2b", 1);
	n2dAddColor("yellow", "f0cc2b", 1);
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
	n2dAssetsLoadAndAddTexture("explode", "res/explode_anim.png");
	n2dAssetsLoadAndAddTexture("gameOverTitle", "res/gameOverTitle.png");
	n2dAssetsLoadAndAddTexture("bomb", "res/bomb_anim.png");

	MainMenu* mainMenuScene = new MainMenu("mainMenu");
	Lvl1* level1 = new Lvl1("level1");
	GameOver* gameOver = new GameOver("gameOver");

	n2dGameAddScene(mainMenuScene);
	n2dGameAddScene(level1);
	n2dGameAddScene(gameOver);
	
	n2dGameConfigFirstScene(mainMenuScene);

	while (Game::IsRunning())
	{
		game.Tick();
	}

	return Game::s_ExitCode;
}