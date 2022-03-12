#include "core/Game.h"

#include "scenes/MainMenu.h"
#include "scenes/Play.h"
#include "scenes/groundLevels/Level2.h"
#include "scenes/GameOver.h"

#include "Player.h"

int main(int argc, char* argv[])
{
	using namespace novazero;
	using namespace graphics;
	using namespace logging;
	using namespace core;
	using namespace maths;
	using namespace controllers;
	using namespace spaceshooter;

	// Game Config
	Game game("Space Shooter");
	game.ConfigureIcon("res/ship_01.png");
	game.ConfigureSQL("spaceshooter", "tcp://127.0.0.1:3306", "root", "sqlpassword", true);
	Game::SetGamePadding(32, 64, 32, 32);
	game.ConfigureDebugOverlay(true);
	game.s_InputHandler->ConfigureJoystickDeadzone(8000);
		
	// Textures
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
	n2dAssetsLoadAndAddTexture("clock", "res/clock_anim.png");
	n2dAssetsLoadAndAddTexture("streaks", "res/streaks_count.png");
	n2dAssetsLoadAndAddTexture("kamikaze", "res/ship_04_anim.png");
	n2dAssetsLoadAndAddTexture("pawn1-bullet", "res/bullet_04.png");
	n2dAssetsLoadAndAddTexture("fuel-tank", "res/fuel_tank.png");
	n2dAssetsLoadAndAddTexture("ground-player", "res/space_man_anim.png");

	MainMenu* mainMenu = new MainMenu("mainMenu");
	Play* playScene = new Play("playScene");
	Level2* level2 = new Level2("level2");
	GameOver* gameOver = new GameOver("gameOver");

	n2dGameAddScene(mainMenu);
	n2dGameAddScene(playScene);
	n2dGameAddScene(level2);
	n2dGameAddScene(gameOver);
	
	n2dGameConfigFirstScene(level2);

	while (Game::IsRunning())
	{
		game.Tick();
	}

	return Game::s_ExitCode;
}